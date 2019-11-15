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

#include <graph/Graph.h>

using namespace std;
using namespace llvm;

cl::opt<string> InputFile(cl::Positional, cl::desc("<bc file>"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "A simple LLVM symbolic simulator");
  // prepare module
  LLVMContext Context;
  SMDiagnostic Err;
  if (InputFile.empty()) {
    InputFile = "../test/test.bc";
  }
  unique_ptr<Module> mainModule = parseIRFile(InputFile, Err, Context);

  // init graphs
  vector<shared_ptr<Graph>> graphs;
  for (Function &f : mainModule->getFunctionList()) {
    if (!f.getBasicBlockList().empty()) {
      shared_ptr<Graph> g = std::make_shared<Graph>();
      g->init(&f);
      graphs.push_back(std::move(g));
    }
  }

  // print
  // max
  stringstream ss;
  ss << "max: ";
  for (unsigned i = 0; i < graphs.size(); ++i) {
    ss << graphs[i]->genSum();
    if (i == graphs.size() - 1) {
      ss << ";\n";
    } else {
      ss << " + ";
    }
  }
  errs() << ss.str();
  errs() << "-----------\n";

  // constraints
  for (unsigned i = 0; i < graphs.size(); ++i) {
    errs() << graphs[i]->genConsts();
  }
  errs() << "-----------\n";

  // function call
  for (unsigned i = 0; i < graphs.size(); ++i) {
    errs() << graphs[i]->genFuncCall();
  }
  errs() << "-----------\n";

  return 0;
}
