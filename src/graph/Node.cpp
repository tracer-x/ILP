/*
 * Node.cpp
 *
 *  Created on: 8 Nov 2019
 *      Author: xuanlinhha
 */

#include "Node.h"

Node::Node() : id(-1), bb(nullptr) {}

Node::Node(int _id, BasicBlock *_bb) {
  id = _id;
  bb = _bb;
}

Node::~Node() {}

string Node::genFuncCallConsts() {
  string prefix = NameUtil::getFuncName(bb->getParent()) + "_BB";
  stringstream ss;
  for (Instruction &i : bb->getInstList()) {
    if (i.getOpcode() == Instruction::Call) {
      Function *f = cast<CallInst>(i).getCalledFunction();
      if (f && !f->empty()) {
        ss << prefix << id << " = ";
        ss << NameUtil::getFuncName(f) << "_BB0;\n";
      }
    }
  }
  return ss.str();
}
