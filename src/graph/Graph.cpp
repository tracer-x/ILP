/*
 * Graph.cpp
 *
 *  Created on: 8 Nov 2019
 *      Author: xuanlinhha
 */

#include "Graph.h"

Graph::Graph() {}

Graph::~Graph() {}

void Graph::init(Function *f) {
  functionName = f->getName().str();
  int order = 0;

  // nodes
  map<BasicBlock *, int> bb2id;
  for (BasicBlock &bb : *f) {
    nodes.push_back(std::make_shared<Node>(order, &bb));
    bb2id[&bb] = order;
    ++order;
  }

  //  errs() << "nodes.size() = " << nodes.size() << "\n";
  //  for (unsigned i = 0; i < nodes.size(); ++i) {
  //    errs() << "BB" << nodes[i]->id << "\n";
  //    nodes[i]->bb->print(errs(), true);
  //  }

  // edges
  for (unsigned i = 0; i < nodes.size(); ++i) {
    Instruction *t = nodes[i]->bb->getTerminator();
    if (t->getOpcode() == Instruction::Br) {
      auto br = cast<BranchInst>(t);
      if (br->isConditional()) {
        shared_ptr<Node> child0 = nodes[bb2id[br->getSuccessor(0)]];
        nodes[i]->children.push_back(std::move(child0));
        shared_ptr<Node> child1 = nodes[bb2id[br->getSuccessor(1)]];
        nodes[i]->children.push_back(std::move(child1));
      } else {
        shared_ptr<Node> child0 = nodes[bb2id[br->getSuccessor(0)]];
        nodes[i]->children.push_back(std::move(child0));
      }
    }
  }
}

string Graph::genSum() {
  string prefix = functionName + "_BB";
  stringstream ss;
  for (unsigned i = 0; i < nodes.size(); ++i) {
    ss << nodes[i]->bb->size() << "*" << prefix << nodes[i]->id;
    if (i < nodes.size() - 1) {
      ss << " + ";
    }
  }
  return ss.str();
}

string Graph::genConsts() {
  string prefix = functionName + "_BB";
  stringstream ss;

  // check children
  for (unsigned i = 0; i < nodes.size(); ++i) {
    if (nodes[i]->children.size() == 2) {
      ss << prefix << nodes[i]->id << " = ";
      ss << prefix << nodes[i]->children[0]->id << " + ";
      ss << prefix << nodes[i]->children[1]->id << ";\n";
    }
  }

  // check parent
  vector<vector<shared_ptr<Node>>> parents;
  for (unsigned i = 0; i < nodes.size(); ++i) {
    vector<shared_ptr<Node>> parent;
    for (unsigned j = 0; j < nodes.size(); ++j) {
      // if exist in children
      if (std::find(nodes[j]->children.begin(), nodes[j]->children.end(),
                    nodes[i]) != nodes[j]->children.end()) {
        parent.push_back(nodes[j]);
      }
    }
    parents.push_back(parent);
  }
  for (unsigned i = 0; i < parents.size(); ++i) {
    if (parents[i].size() > 1) {
      ss << prefix << nodes[i]->id << " = ";
      for (unsigned j = 0; j < parents[i].size(); ++j) {
        ss << prefix << parents[i][j]->id;
        if (j < parents[i].size() - 1) {
          ss << " + ";
        } else {
          ss << ";\n";
        }
      }
    }
  }

  return ss.str();
}

string Graph::genFuncCall() {
  stringstream ss;
  for (unsigned i = 0; i < nodes.size(); ++i) {
    string tmp = nodes[i]->genFuncCallConsts();
    if (!tmp.empty()) {
      ss << tmp;
    }
  }
  return ss.str();
}

void Graph::print() {
  string prefix = functionName + "_BB";
  for (unsigned i = 0; i < nodes.size(); ++i) {
    errs() << prefix << nodes[i]->id << ": ";
    for (unsigned j = 0; j < nodes[i]->children.size(); ++j) {
      errs() << prefix << nodes[i]->children[j]->id << "; ";
    }
    errs() << "\n";
  }
}
