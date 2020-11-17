#include "common.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char** argv) {
  if (argc >= 2) {
    fprintf(stderr, "mul running with argv[0]: %s\n", argv[1]);
  } else {
    fprintf(stderr, "Please specify matrix size n.");
    abort();
  }
  const usize n = atoi(argv[1]);

  MATRIX_MUL_ORDER(I, J, K, "IJK");

  return 0;
}