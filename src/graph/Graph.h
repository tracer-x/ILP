/*
 * Graph.h
 *
 *  Created on: 8 Nov 2019
 *      Author: xuanlinhha
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include "Node.h"
#include <sstream>

using namespace std;
using namespace llvm;

class Graph {
public:
  Graph();
  virtual ~Graph();
  string functionName;
  vector<shared_ptr<Node>> nodes;
  void init(Function* f);
  string genConsts();
  void print();
};

#endif /* SRC_GRAPH_GRAPH_H_ */
