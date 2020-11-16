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
  usize n = atoi(argv[1]);
  Matrix b = matrix_new(n);
  Matrix c = matrix_new(n);

  srand(time(NULL));
  matrix_rand(b);
  // matrix_display(b);

  matrix_rand(c);
  // matrix_display(c);

  Matrix a;
  usize begin, end, clocks;
  double gflops;

  a = matrix_new(n);
  begin = readTSC();
  I J K { MATRIX_MUL(a, b, c); }
  end = readTSC();
  clocks = end - begin;
  // Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
  gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101);
  printf("Clocks passed: %ld\n", clocks);
  printf("Gflops: %lf\n", gflops);

  // matrix_display(a);
  matrix_drop(a);

  matrix_drop(b);
  matrix_drop(c);
  return 0;
}