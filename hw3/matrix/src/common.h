#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef size_t usize;

typedef struct {
  double* val;
  usize n;
} Matrix;

#define I for (usize i = 0; i < n; i++)
#define J for (usize j = 0; j < n; j++)
#define K for (usize k = 0; k < n; k++)
#define MATRIX_MUL(a, b, c)            \
  double* p = matrix_get_mut(a, i, j); \
  *p += *matrix_get(b, i, k) * *matrix_get(c, k, j)

Matrix matrix_new(usize n) {
  Matrix matrix;
  matrix.n = n;
  matrix.val = (double*)malloc(sizeof(double) * n * n);

  return matrix;
}
Matrix matrix_rand(Matrix matrix) {
  usize n = matrix.n;
  for (usize i = 0; i < n * n; i++) {
    matrix.val[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
  }
}
__attribute__((always_inline)) inline const double* matrix_get(Matrix matrix,
                                                               usize i,
                                                               usize j) {
  return matrix.val + i * matrix.n + j;
}
__attribute__((always_inline)) inline double* matrix_get_mut(Matrix matrix,
                                                             usize i, usize j) {
  return matrix.val + i * matrix.n + j;
}
void matrix_display(Matrix matrix) {
  usize n = matrix.n;
  fprintf(stderr, "\n");
  I {
    fprintf(stderr, "|");
    J { fprintf(stderr, " %5.2f", matrix.val[i * matrix.n + j]); }
    fprintf(stderr, " |\n");
  }
}

void matrix_drop(Matrix matrix) { free(matrix.val); }

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