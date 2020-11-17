#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef size_t usize;
typedef double Real;
#define INFO(format, ...) fprintf(stderr, format, __VA_ARGS__);
#define I for (usize i = 0; i < n; i++)
#define J for (usize j = 0; j < n; j++)
#define K for (usize k = 0; k < n; k++)

/* Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz */
/* Intel(R) Core(TM) i7-4790 CPU @ 3.60GHz */
#define CPU_MAX_MHZ 3600
#define GET_GFLOPS            \
  usize clocks = end - begin; \
  long double gflops = 2 * n * n * n * 1e-3 * CPU_MAX_MHZ / clocks;

typedef struct {
  Real* ptr;
  usize n;
} Matrix;

Matrix matrix_new(const usize n) {
  Matrix matrix;
  matrix.n = n;
  matrix.ptr = (Real*)malloc(sizeof(Real) * n * n);
  return matrix;
}
#define MATRIX_GET(m, i, j) (m.ptr + i * m.n + j)
#define MATRIX_MUL(a, b, c) \
  *MATRIX_GET(a, i, j) += *MATRIX_GET(b, i, k) * *MATRIX_GET(c, k, j)

void matrix_rand(Matrix matrix) {
  usize n = matrix.n;
  I J { *MATRIX_GET(matrix, i, j) = (Real)rand() / RAND_MAX; }
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

#define MATRIX_NEW_ABC      \
  Matrix a = matrix_new(n); \
  Matrix b = matrix_new(n); \
  Matrix c = matrix_new(n);
#define MATRIX_DROP_ABC \
  matrix_drop(a);       \
  matrix_drop(b);       \
  matrix_drop(c);
long long readTSC(void);
#define MATRIX_MUL_ORDER(Outter, Middle, Inner, order) \
  {                                                    \
    MATRIX_NEW_ABC;                                    \
    srand(time(NULL));                                 \
    matrix_rand(b);                                    \
    matrix_rand(c);                                    \
    usize begin = readTSC();                           \
    Outter Middle Inner { MATRIX_MUL(a, b, c); }       \
    usize end = readTSC();                             \
    matrix_display(a);                                 \
    GET_GFLOPS;                                        \
    INFO("%s Clocks passed: %ld\n", order, clocks);    \
    INFO("%s Gflops: %Lf\n", order, gflops);           \
    MATRIX_DROP_ABC;                                   \
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
