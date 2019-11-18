/*
 * NameUtil.h
 *
 *  Created on: 18 Nov 2019
 *      Author: xuanlinhha
 */

#ifndef SRC_UTIL_NAMEUTIL_H_
#define SRC_UTIL_NAMEUTIL_H_

#include <llvm/IR/Function.h>
#include <string>

using namespace std;
using namespace llvm;

class NameUtil {
public:
  NameUtil();
  virtual ~NameUtil();
  static string EXTRA;
  static string getFuncName(Function *f);
};

#endif /* SRC_UTIL_NAMEUTIL_H_ */
