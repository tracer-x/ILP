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
#include <vector>

using namespace std;
using namespace llvm;

class Node {
public:
  Node();
  virtual ~Node();
  int id;
  BasicBlock *b;
  vector<shared_ptr<Node>> children;
};

#endif /* SRC_TOOL_NODE_H_ */
