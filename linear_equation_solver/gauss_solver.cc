#include "gauss_solver.h"

GaussSolver::~GaussSolver() {}

std::vector<double> GaussSolver::SolveUsualGauss(
    SystemOfLinearEquations system) {
  std::vector<double> result;
  int equations = system.GetAmountOfEquations();
  int variables = system.GetAmountOfVariable();

  return result;
}

std::vector<double> GaussSolver::SolveParallelGauss(
    SystemOfLinearEquations system) {
  std::vector<double> result;
  //   system.at(1);
  return result;
}
