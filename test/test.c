//#include <klee/klee.h>
int wcet = 0;
int B;
int main() {
  int c, d, x, y, z, flag;
  if (c) {
    flag = 1;
  } else {
    flag = 0;
  }
  x = 2;
  if (d) {
    y = 4;
  } else {
    y = 5;
  }
  if (flag) {

    z = y + x;
  } else {
    z = x + 1;
  }

  return 0;
}
