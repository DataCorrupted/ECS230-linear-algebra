#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef size_t usize;
typedef double Real;

typedef struct {
  Real* ptr;
  usize n;
} Matrix;

#define I for (usize i = 0; i < n; i++)
#define J for (usize j = 0; j < n; j++)
#define K for (usize k = 0; k < n; k++)

Matrix matrix_new(const usize n) {
  Matrix matrix;
  matrix.n = n;
  matrix.ptr = (Real*)malloc(sizeof(Real) * n * n);
  return matrix;
}

#define MATRIX_GET(m, i, j) (m.ptr + i * m.n + j)
#define MATRIX_MUL(a, b, c) \
  *MATRIX_GET(a, i, j) = *MATRIX_GET(b, i, k) * *MATRIX_GET(c, k, j)

void matrix_rand(Matrix matrix) {
  usize n = matrix.n;
  I J { *MATRIX_GET(matrix, i, j) = (Real)rand() / RAND_MAX * 2.0 - 1.0; }
}

void matrix_display(const Matrix matrix) {
  usize n = matrix.n;
  fprintf(stdout, "\n");
  I {
    fprintf(stdout, "|");
    J { fprintf(stdout, " %5.2f", matrix.ptr[i * matrix.n + j]); }
    fprintf(stdout, " |\n");
  }
}

void matrix_drop(Matrix matrix) { free(matrix.ptr); }

long long readTSC(void);
#define MATRIX_MUL_ORDER(Outter, Middle, Inner, order)               \
  {                                                                  \
    Matrix a = matrix_new(n);                                        \
    Matrix b = matrix_new(n);                                        \
    Matrix c = matrix_new(n);                                        \
    srand(time(NULL));                                               \
    matrix_rand(b);                                                  \
    matrix_rand(c);                                                  \
    usize begin = readTSC();                                         \
    Outter Middle Inner { MATRIX_MUL(a, b, c); }                     \
    usize end = readTSC();                                           \
    matrix_display(a);                                               \
    usize clocks = end - begin;                                      \
    /* Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz */                 \
    double gflops = (2 * n * n * n * 1e-9) / (clocks * 1e-6 / 2101); \
    fprintf(stderr, "%s Clocks passed: %ld\n", order, clocks);       \
    fprintf(stderr, "%s Gflops: %lf\n", order, gflops);              \
    matrix_drop(a);                                                  \
    matrix_drop(b);                                                  \
    matrix_drop(c);                                                  \
  }

/// Provided in HW2. Copy and pasted it here.
long long readTSC(void) {
  /* read the time stamp counter on Intel x86 chips */
  union {
    long long complete;
    unsigned int part[2];
  } ticks;
  __asm__("rdtsc; mov %%eax,%0;mov %%edx,%1"
          : "=mr"(ticks.part[0]), "=mr"(ticks.part[1])
          : /* no inputs */
          : "eax", "edx");
  return ticks.complete;
}
