#include "common.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef OPT_LEVEL
#define OPT_LEVEL "Opt level not specified."
#endif

int main(int argc, char** argv) {
  if (argc >= 2) {
    fprintf(stderr,
            "mul_loop running with optimization level: %s, argv[0]: %s\n",
            OPT_LEVEL, argv[1]);
  } else {
    fprintf(stderr, "Please specify matrix size n.");
    abort();
  }
  const usize n = atoi(argv[1]);

  MATRIX_MUL_ORDER(I, J, K, "IJK");
  MATRIX_MUL_ORDER(I, K, J, "IKJ");
  MATRIX_MUL_ORDER(J, I, K, "JIK");
  MATRIX_MUL_ORDER(J, K, I, "JKI");
  MATRIX_MUL_ORDER(K, I, J, "KIJ");
  MATRIX_MUL_ORDER(K, J, I, "KJI");

  return 0;
}