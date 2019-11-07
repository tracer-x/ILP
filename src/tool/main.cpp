#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

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
  //errs() << "Function & BB:\n";
  for (Function &f : mainModule->getFunctionList()) {
    stringstream ss;
    ss << "max:";
    int i = 0;
    for (BasicBlock &bb : f) {
      ss  << "*" << f.getName().str() << "_" << "BB" << ++i;
      if (&f.back() != &bb) {
        ss << "+";
      }
    }
    errs() << ss.str() << "+";
  }
  errs() << ";\n";
  
  //....
  
  errs() << "\n\n";
  for (Function &f : mainModule->getFunctionList()) {
    stringstream ss;
    ss << "int ";
    int i = 0;
    for (BasicBlock &bb : f) {
      ss << f.getName().str() << "_" << "BB" << ++i;
      if (&f.back() != &bb) {
        ss << ",";
      }
    }
    errs() << ss.str() << ",";
  }
  errs() << ";\n";

  return 0;
}
