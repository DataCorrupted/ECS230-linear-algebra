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
  usize n = atoi(argv[1]);
  Matrix b = matrix_new(n);
  Matrix c = matrix_new(n);

  srand(time(NULL));
  matrix_rand(b);
  matrix_display(b);

  matrix_rand(c);
  matrix_display(c);

  Matrix a = matrix_new(n);
  I J K { MATRIX_MUL(a, b, c); }
  matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  I K J { MATRIX_MUL(a, b, c); }
  matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  J I K { MATRIX_MUL(a, b, c); }
  matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  J K I { MATRIX_MUL(a, b, c); }
  matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  K I J { MATRIX_MUL(a, b, c); }
  matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  K J I { MATRIX_MUL(a, b, c); }
  matrix_display(a);
  matrix_drop(a);

  matrix_drop(b);
  matrix_drop(c);
  return 0;
  return 0;
}