#include "common.h"
#include "stdio.h"
#include "stdlib.h"

/// See the documentation [here](http://www.netlib.org/clapack/cblas/dgemm.c)
/// See example usage
/// [here](https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbcpx01/atlasexample1.htm)
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
  usize n = atoi(argv[1]);
  int N = n;

  MATRIX_NEW_ABC;
  srand(time(NULL));
  matrix_rand(a);
  matrix_rand(b);

  char transa = 'N', transb = 'N';
  Real alpha = 1.0, beta = 0.0;

  usize begin = readTSC();
  dgemm_(&transa, &transb, &N, &N, &N, &alpha, a.ptr, &N, b.ptr, &N, &beta,
         c.ptr, &N);
  usize end = readTSC();

  matrix_display(a);

  GET_GFLOPS;
  INFO("%s Clocks passed: %ld\n", "dgemm", clocks);
  INFO("%s Time passed: %lf\n", "dgemm", seconds);
  INFO("%s Gflops: %lf\n", "dgemm", gflops);

  MATRIX_DROP_ABC;
  return 0;
}
