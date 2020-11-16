#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef size_t usize;
typedef double Real;

typedef struct {
  Real* val;
  usize n;
} Matrix;

#define I for (usize i = 0; i < n; i++)
#define J for (usize j = 0; j < n; j++)
#define K for (usize k = 0; k < n; k++)

Matrix matrix_new(usize n) {
  Matrix matrix;
  matrix.n = n;
  matrix.val = (Real*)malloc(sizeof(Real) * n * n);

  return matrix;
}
Matrix matrix_rand(Matrix matrix) {
  usize n = matrix.n;
  for (usize i = 0; i < n * n; i++) {
    matrix.val[i] = (Real)rand() / RAND_MAX * 2.0 - 1.0;
  }
}

#define MATRIX_GET(m, i, j) (m.val + i * m.n + j)
#define MATRIX_MUL(a, b, c) \
  *MATRIX_GET(a, i, j) = *MATRIX_GET(b, i, k) * *MATRIX_GET(c, k, j)

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

/// Do some dummy operations to speed up CPU first
void speed_up_frequenct(usize n) {
  Matrix b = matrix_new(n);
  Matrix c = matrix_new(n);

  srand(time(NULL));
  matrix_rand(b);
  matrix_rand(c);

  Matrix a;
  a = matrix_new(n);
  I J K { MATRIX_MUL(a, b, c); }
  matrix_drop(a);
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
