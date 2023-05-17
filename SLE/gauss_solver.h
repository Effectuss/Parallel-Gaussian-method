#ifndef _SLE_GAUSS_SOLVER_H_
#define _SLE_GAUSS_SOLVER_H_

#include <pthread.h>

#include <mutex>
#include <thread>
#include <vector>

#include "system_of_linear_equations.h"

class GaussSolver {
 public:
  enum TypeOfGaussAlgo { kParallel, kSerial };

  std::vector<double> SolveSerialGauss(SLE system) const;
  std::vector<double> SolveParallelGauss(SLE system) const;

 private:
  static int FindMaxRow(const SLE::Matrix& matrix, int k, int equations);
  static void SwapRows(SLE::Matrix& matrix, int k, int max_row);
  static void ReduceToTriangular(SLE::Matrix& matrix, int k, int equations,
                                 int variables);
  static void SolveEquations(const SLE::Matrix& matrix, int variables,
                             std::vector<double>& result);

  static constexpr double kEPS = 1e-6;
};
#endif  // _SLE_GAUSS_SOLVER_H_