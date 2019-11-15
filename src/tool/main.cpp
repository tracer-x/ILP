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

cl::opt<string> InputFile(cl::Positional, cl::desc("<bc file>"), cl::init("-"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "A simple LLVM symbolic simulator");
  // prepare module
  LLVMContext Context;
  SMDiagnostic Err;
  if (InputFile == "") {
    InputFile = "../test/test.bc";
  }
  unique_ptr<Module> mainModule = parseIRFile(InputFile, Err, Context);

  for (Function &f : mainModule->getFunctionList()) {
    if (!f.getBasicBlockList().empty()) {
      unique_ptr<Graph> g = std::make_unique<Graph>();
      g->init(&f);
      g->print();
      errs() << "Constraints: \n";
      errs() << g->genConsts() << "\n";
    }
  }

  return 0;
}
