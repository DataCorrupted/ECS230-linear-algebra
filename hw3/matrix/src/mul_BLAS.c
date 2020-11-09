#include "stdio.h"
#include "stdlib.h"

double ddot_(int *n, double *x, int *incx, double *y, int *incy);

int main(int argc, char **argv) {
  if (argc >= 2) {
    fprintf(stderr, "mul_BLAS running with argv[0]: %s\n", argv[1]);
  }
  return 0;
}
