/*
 * Node.h
 *
 *  Created on: 8 Nov 2019
 *      Author: xuanlinhha
 */

#ifndef SRC_TOOL_NODE_H_
#define SRC_TOOL_NODE_H_

#include <llvm/IR/Instructions.h>
#include <memory>
#include <sstream>
#include <util/NameUtil.h>
#include <vector>

using namespace std;
using namespace llvm;

class Node {
public:
  Node();
  Node(int _id, BasicBlock *_bb);
  virtual ~Node();
  int id;
  BasicBlock *bb;
  vector<shared_ptr<Node>> children;
  string genFuncCallConsts();
};

#endif /* SRC_TOOL_NODE_H_ */
