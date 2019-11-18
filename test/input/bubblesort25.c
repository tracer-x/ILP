

int main() {

  int i, j, a[25], tmp;
  int b1, b2, b3, b4, b5, b6, b7, b8;

  int v1, v2;
  if (b1 > 0)
    a[0] = v1;
  else
    a[0] = v2;
  if (b2 > 0)
    a[1] = v1;
  else
    a[1] = v2;
  if (b3 > 0)
    a[2] = v1;
  else
    a[2] = v2;
  if (b4 > 0)
    a[3] = v1;
  else
    a[3] = v2;
  if (b5 > 0)
    a[4] = v1;
  else
    a[4] = v2;
  if (b6 > 0)
    a[5] = v1;
  else
    a[5] = v2;
  if (b7 > 0)
    a[6] = v1;
  else
    a[6] = v2;
  if (b1 > 0)
    a[7] = v1;
  else
    a[7] = v2;

  i = 0;
  while (i < 8 - 1) {
    j = 0;
    while (j < 8 - 1 - i) {

      if (a[j] > a[j + 1]) {

        tmp = a[j + 1];

        a[j + 1] = a[j];

        a[j] = tmp;
      }
      j++;
    }
    i++;
  }
}
