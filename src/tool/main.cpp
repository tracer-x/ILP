#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace llvm;

cl::opt<string> InputFile(cl::Positional, cl::desc("<bc file>"), cl::init("-"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "A simple LLVM symbolic simulator");
  // prepare module
  LLVMContext Context;
  SMDiagnostic Err;
  if (InputFile == "") {
    InputFile = "../test/test.bc";
  }
  unique_ptr<Module> mainModule = parseIRFile("../test/test.bc", Err, Context);

  map<BasicBlock *, int> m;
  int i = 0;
  for (Function &f : mainModule->getFunctionList()) {
    if (!f.getBasicBlockList().empty()) {
      int i = 0;
      for (BasicBlock &bb : f) {
        m[&bb] = ++i;
      }
    }
  }

  vector<BasicBlock *> bbs;
  for (Function &f : mainModule->getFunctionList()) {
    if (!f.getBasicBlockList().empty()) {
      int i = 0;
      for (BasicBlock &bb : f) {
        bbs.push_back(&bb);
      }
    }
  }

  errs() << "Size=" << bbs.size() << "\n";

  //
  stringstream ss;
  ss.str("\n");
  ss << "max: ";
  i = 0;
  while (i < bbs.size()) {
    if (bbs[i]->size() > 1) {
      ss << bbs[i]->size() << "*";
    }
    ss << bbs[i]->getParent()->getName().str() << "_BB";
    ss << ++i;
    if (i == bbs.size()) {
      ss << ";\n";
    } else {
      ss << " + ";
    }
  }
  errs() << ss.str();

  //
  ss.str("\n");
  i = 0;
  while (i < bbs.size()) {
    Instruction *t = bbs[i]->getTerminator();

    if (t->getOpcode() == Instruction::Br) {
      auto br = cast<BranchInst>(t);

      if (br->isConditional()) {
        //        br->print(errs(), true);
        //        errs() << "\n";
        //        errs() << m[br->getSuccessor(0)] << "\n";
        //        errs() << m[br->getSuccessor(1)] << "\n";
        ss << bbs[i]->getParent()->getName().str() << "_BB" << (i + 1) << " = ";
        BasicBlock *b0 = br->getSuccessor(0);
        ss << b0->getParent()->getName().str() << "_BB" << m[b0] << " + ";
        BasicBlock *b1 = br->getSuccessor(1);
        ss << b1->getParent()->getName().str() << "_BB" << m[b1] << ";\n";
      } else {
        ss << bbs[i]->getParent()->getName().str() << "_BB" << (i + 1) << " = ";
        BasicBlock *b1 = br->getSuccessor(0);
        ss << b1->getParent()->getName().str() << "_BB" << m[b1] << ";\n";
      }
    }
    ++i;
  }
  errs() << ss.str();

  //
  ss.str("\n");
  ss << "int ";
  i = 0;
  while (i < bbs.size()) {
    ss << bbs[i]->getParent()->getName().str() << "_BB";
    ss << ++i;
    if (i == bbs.size()) {
      ss << ";\n";
    } else {
      ss << ", ";
    }
  }
  errs() << ss.str();

  return 0;
}
