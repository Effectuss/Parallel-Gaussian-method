#ifndef _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_
#define _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_

#include <vector>

#include "system_of_linear_equations.h"

class GaussSolver {
 public:
  virtual ~GaussSolver() = 0;
  // this method work only with compatible system
  static std::vector<double> SolveUsualGauss(SystemOfLinearEquations system);
  // this method work only with compatible system
  static std::vector<double> SolveParallelGauss(SystemOfLinearEquations system);

 private:
  static constexpr double kEPS = 1e-6;
};
#endif  // _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_