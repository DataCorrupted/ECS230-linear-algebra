#include <stdio.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

typedef size_t usize;
#define INFO(format, ...) fprintf(stderr, format, __VA_ARGS__);
#define I for (usize i = 0; i < n; i++)
#define J for (usize j = 0; j < n; j++)

static usize n;

bool vec_diff(VectorXd a, VectorXd b) {
  I {
    if (abs(a(i) - b(i)) >= 1e-6) {
      return true;
    }
  }
  return false;
}

VectorXd normalize(VectorXd a) {
  double sum = 0;
  I { sum += a(i); }
  return a / sum;
}

/// Power iteration.
VectorXd get_eigenvec(MatrixXd a) {
  VectorXd prev(n);
  VectorXd curr(n);
  I {
    curr(i) = 1;
    prev(i) = 0.0;
  }
  curr = normalize(curr);
  usize iter_cnt = 0;
  while (vec_diff(prev, curr)) {
    std::cout << "Iter: " << iter_cnt << "\n";
    std::cout << "Curr: \n" << curr << "\n";
    iter_cnt++;
    prev = curr;
    curr = normalize(a * prev);
  }
  std::cout << "Iterations: " << iter_cnt << ". Final: \n" << curr << "\n";
  return curr;
}

/// Power iteration.
VectorXd get_eigenvec_shifted(MatrixXd a, double alpha) {
  I { a(i, i) -= alpha; }

  VectorXd x(n);
  VectorXd diff(n);
  I {
    x(i) = 1;
    diff(i) = 1;
  }
  x = x.normalized();
  usize iter_cnt = 0;
  while (diff.squaredNorm() >= 1e-6) {
    std::cout << "Iter: " << iter_cnt << "\n";
    std::cout << "Curr: \n" << x << "\n";
    iter_cnt++;
    VectorXd y = a * x;
    double mu = x.transpose() * y;
    diff = y - mu * x;
    x = (y - alpha * x).normalized();
  }
  x = normalize(x);
  std::cout << "Iterations: " << iter_cnt << ". Final: \n" << x << "\n";
  return x;
}

int main() {
  std::cin >> n;
  MatrixXd a(n, n);
  J {
    usize nj;
    std::cin >> nj;
    for (usize nji = 0; nji < nj; nji++) {
      usize i;
      std::cin >> i;
      a(i, j) = 1.0 / nj;
    }
  }
  std::cout << "I got matrix A: \n" << a << "\n";

  // get_eigenvec(a);
  get_eigenvec_shifted(a, -0.25);
  return 0;
}