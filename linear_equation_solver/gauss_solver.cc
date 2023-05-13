#include "gauss_solver.h"

GaussSolver::~GaussSolver() {}

std::vector<double> GaussSolver::SolveUsualGauss(
    SystemOfLinearEquations system) {
  int equations = system.GetAmountOfEquations();
  int variables = system.GetAmountOfVariable();
  Matrix matrix = system.GetAugmentedMatrix();
  std::vector<double> result(variables);
  for (int k = 0; k < equations; ++k) {
    double max_value = fabs(matrix[k][k]);
    int max_row = k;
    for (int i = k + 1; i < equations; ++i) {
      if (fabs(matrix[i][k] - max_value) > kEPS) {
        max_value = fabs(matrix[i][k]);
        max_row = i;
      }
    }

    if (max_row != k) {
      std::swap(matrix[k], matrix[max_row]);
    }

    for (int i = k + 1; i < equations; ++i) {
      double coeff = matrix[i][k] / matrix[k][k];
      for (int j = k + 1; j <= variables; ++j) {
        matrix[i][j] -= coeff * matrix[k][j];
      }
    }

    for (int i = variables - 1; i >= 0; --i) {
      result[i] = matrix[i][variables];
      for (int j = i + 1; j < variables; ++j) {
        result[i] -= matrix[i][j] * result[j];
      }
      result[i] /= matrix[i][i];
    }
  }

  return result;
}

std::vector<double> GaussSolver::SolveParallelGauss(
    SystemOfLinearEquations system) {
  std::vector<double> result;
  system.GetCoefficientMatrix();
  return result;
}
