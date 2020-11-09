#include "stdio.h"
#include "stdlib.h"
int main(int argc, char** argv) {
  if (argc >= 2) {
    fprintf(stderr, "mul_loop running with argv[0]: %s\n", argv[1]);
  }
  return 0;
}