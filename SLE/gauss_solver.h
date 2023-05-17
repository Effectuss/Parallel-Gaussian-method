#ifndef _SLE_GAUSS_SOLVER_H_
#define _SLE_GAUSS_SOLVER_H_

#include <pthread.h>

#include <mutex>
#include <thread>
#include <vector>

class SLE;

class GaussSolver {
 public:
  enum TypeOfGaussAlgo { kParallel, kSerial };

  std::vector<double> SolveSerialGauss(SLE system) const;
  std::vector<double> SolveParallelGauss(SLE system) const;

 private:
  using Matrix = std::vector<std::vector<double> >;

  static int FindMaxRow(const Matrix& matrix, int k, int equations);
  static void SwapRows(Matrix& matrix, int k, int max_row);
  static void ReduceToTriangular(Matrix& matrix, int k, int equations,
                                 int variables);
  static void SolveEquations(const Matrix& matrix, int variables,
                             std::vector<double>& result);

  static constexpr double kEPS = 1e-6;
};
#endif  // _SLE_GAUSS_SOLVER_H_