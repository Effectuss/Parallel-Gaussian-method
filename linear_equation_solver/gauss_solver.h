#ifndef _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_
#define _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_

#include <vector>
#include <thread>
#include <mutex>

#include "system_of_linear_equations.h"

class GaussSolver {
 public:
  virtual ~GaussSolver() = 0;

  static std::vector<double> SolveUsualGauss(SystemOfLinearEquations system);
  static std::vector<double> SolveParallelGauss(SystemOfLinearEquations system);

 private:
  static int FindMaxRow(const SystemOfLinearEquations::Matrix& matrix, int k,
                        int equations);
  static void SwapRows(SystemOfLinearEquations::Matrix& matrix, int k,
                       int max_row);
  static void ReduceToTriangular(SystemOfLinearEquations::Matrix& matrix, int k,
                                 int equations, int variables);
  static void SolveEquations(const SystemOfLinearEquations::Matrix& matrix,
                             int variables, std::vector<double>& result);

  static constexpr double kEPS = 1e-6;
};
#endif  // _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_