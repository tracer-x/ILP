#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include <llvm/Analysis/LoopInfo.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <graph/Graph.h>
#include <util/NameUtil.h>

using namespace std;
using namespace llvm;

cl::opt<string> InputFile(cl::Positional, cl::desc("<bc file>"));
cl::opt<string> OutputFile(cl::Positional, cl::desc("<output file>"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "A simple LLVM symbolic simulator");
  // prepare module
  LLVMContext Context;
  SMDiagnostic Err;

  // input & output
  if (InputFile.empty()) {
    InputFile = "../test/test.bc";
  }
  raw_ostream *out = &errs();
  if (!OutputFile.empty()) {
    std::error_code EC;
    out = new raw_fd_ostream(OutputFile, EC, sys::fs::F_None);
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
  ss.str("");
  ss << "max: ";
  for (unsigned i = 0; i < graphs.size(); ++i) {
    ss << graphs[i]->genSum();
    if (i == graphs.size() - 1) {
      ss << ";\n";
    } else {
      ss << " + ";
    }
  }
  *out << ss.str();

  // constraints
  *out << "main_BB0 = 1;\n";
  for (unsigned i = 0; i < graphs.size(); ++i) {
    *out << graphs[i]->genConsts();
  }

  // function call
  for (unsigned i = 0; i < graphs.size(); ++i) {
    *out << graphs[i]->genFuncCall();
  }

  // loop head
  ss.str("");
  for (unsigned i = 0; i < graphs.size(); ++i) {
    shared_ptr<Graph> g = graphs[i];
    string pre = NameUtil::getFuncName(g->func) + "_BB";

    DominatorTree dt = DominatorTree();
    dt.recalculate(*g->func);
    LoopInfoBase<BasicBlock, Loop> *loopInfo =
        new LoopInfoBase<BasicBlock, Loop>();
    loopInfo->releaseMemory();
    loopInfo->analyze(dt);

    for (unsigned j = 0; j < g->nodes.size(); ++j) {
      if (loopInfo->isLoopHeader(g->nodes[j]->bb)) {
        //        g->nodes[j]->bb->print(errs());
        //        *out << "\n";
        ss << pre << g->nodes[j]->id << " <= 3;\n";
      }
    }
  }
  *out << ss.str();

  // declare
  ss.str("");
  ss << "int ";
  for (unsigned i = 0; i < graphs.size(); ++i) {
    shared_ptr<Graph> g = graphs[i];
    string pre = NameUtil::getFuncName(g->func) + "_BB";
    for (unsigned j = 0; j < g->nodes.size(); ++j) {
      ss << pre << g->nodes[j]->id;
      if (j < g->nodes.size() - 1) {
        ss << ", ";
      }
    }
    if (i == graphs.size() - 1) {
      ss << ";\n";
    } else {
      ss << ", ";
    }
  }
  *out << ss.str();

  if (out != &errs()) {
    out->flush();
  }
  return 0;
}
