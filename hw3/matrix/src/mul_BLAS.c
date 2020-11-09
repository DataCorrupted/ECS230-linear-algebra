#include "stdio.h"
int main(int argc, char** argv) {
  if (argc >= 2) {
    fprintf(stderr, "mul_BLAS running with argv[0]: %s\n", argv[1]);
  }
  return 0;
}