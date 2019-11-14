/*
 * Node.cpp
 *
 *  Created on: 8 Nov 2019
 *      Author: xuanlinhha
 */

#include "Node.h"

Node::Node() : id(-1), bb(nullptr) {}

Node::Node(int _id, BasicBlock *_bb){
	id=_id;
	bb=_bb;
}

Node::~Node() {}
