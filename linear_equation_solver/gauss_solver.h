#ifndef _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_
#define _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_

#include <vector>

class GaussSolver {
 public:
  using Matrix = std::vector<std::vector<double>>;

  // this method work only with compatible system
  static std::vector<double> SolveUsualGauss(Matrix system);
  // this method work only with compatible system
  static std::vector<double> SolveParallelGauss(Matrix system);

 private:
  static constexpr double kEPS = 1e-6;
};
#endif  // _LINEAR_EQUATION_SOLVER_GAUSS_SOLVER_H_