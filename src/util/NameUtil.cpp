/*
 * NameUtil.cpp
 *
 *  Created on: 18 Nov 2019
 *      Author: xuanlinhha
 */

#include "NameUtil.h"

string NameUtil::EXTRA = "USC";

NameUtil::NameUtil() {}

NameUtil::~NameUtil() {}

string NameUtil::getFuncName(Function *f) {
  if (!f->getName().empty() && f->getName().front() != '_') {
    return f->getName().str();
  } else {
    return EXTRA + f->getName().str();
  }
}
