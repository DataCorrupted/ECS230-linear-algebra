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
  matrix_rand(c);

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
  printf("IJK Clocks passed: %ld\n", clocks);
  printf("IJK Gflops: %lf\n", gflops);
  // matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  begin = readTSC();
  I K J { MATRIX_MUL(a, b, c); }
  end = readTSC();
  clocks = end - begin;
  // Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
  gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101);
  printf("IKJ Clocks passed: %ld\n", clocks);
  printf("IKJ Gflops: %lf\n", gflops);
  // matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  begin = readTSC();
  J I K { MATRIX_MUL(a, b, c); }
  end = readTSC();
  clocks = end - begin;
  // Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
  gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101);
  printf("JIK Clocks passed: %ld\n", clocks);
  printf("JIK Gflops: %lf\n", gflops);
  // matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  begin = readTSC();
  J K I { MATRIX_MUL(a, b, c); }
  end = readTSC();
  clocks = end - begin;
  // Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
  gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101);
  printf("JKI Clocks passed: %ld\n", clocks);
  printf("JKI Gflops: %lf\n", gflops);
  // matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  begin = readTSC();
  K I J { MATRIX_MUL(a, b, c); }
  end = readTSC();
  clocks = end - begin;
  // Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
  gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101);
  printf("KIJ Clocks passed: %ld\n", clocks);
  printf("KIJ Gflops: %lf\n", gflops);
  // matrix_display(a);
  matrix_drop(a);

  a = matrix_new(n);
  begin = readTSC();
  K J I { MATRIX_MUL(a, b, c); }
  end = readTSC();
  clocks = end - begin;
  // Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
  gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101);
  printf("KJI Clocks passed: %ld\n", clocks);
  printf("KJI Gflops: %lf\n", gflops);
  // matrix_display(a);
  matrix_drop(a);

  matrix_drop(b);
  matrix_drop(c);
  return 0;
}