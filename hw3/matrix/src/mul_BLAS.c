#include "common.h"
#include "stdio.h"
#include "stdlib.h"

/// See the documentation [here](http://www.netlib.org/clapack/cblas/dgemm.c)
int dgemm_(char *transa, char *transb, int *m, int *n, int *k, double *alpha,
           double *A, int *lda, double *B, int *ldb, double *beta, double *,
           int *ldc);

int main(int argc, char **argv) {
  if (argc >= 2) {
    fprintf(stderr, "mul_BLAS running with argv[0]: %s\n", argv[1]);
  } else {
    fprintf(stderr, "Please specify matrix size n.");
    abort();
  }
  int n = atoi(argv[1]);

  Matrix a = matrix_new(n);
  Matrix b = matrix_new(n);
  Matrix c = matrix_new(n);
  srand(time(NULL));
  matrix_rand(b);
  matrix_rand(c);
  matrix_display(b);
  matrix_display(c);

  char transa = 'N', transb = 'N';
  Real alpha = 1.0, beta = 0.0;
  dgemm_(&transa, &transb, &n, &n, &n, &alpha, b.ptr, &n, c.ptr, &n, a.ptr,
         &beta, &n);
  matrix_display(a);

  matrix_drop(a);
  matrix_drop(b);
  matrix_drop(c);

  return 0;
}
