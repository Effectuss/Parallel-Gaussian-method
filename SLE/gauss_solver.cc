#include "gauss_solver.h"

#include "SLE.h"
std::vector<double> GaussSolver::SolveParallelGauss(SLE system) const {
  std::vector<double> result;
  system.GetCoefficientMatrix();
  return result;
}

std::vector<double> GaussSolver::SolveSerialGauss(SLE system) const {
  int equations = system.GetAmountOfEquations();
  int variables = system.GetAmountOfVariable();
  SLE::Matrix matrix = system.GetAugmentedMatrix();
  std::vector<double> result(variables);
  for (int k = 0; k < equations; ++k) {
    int max_row = FindMaxRow(matrix, k, equations);
    SwapRows(matrix, k, max_row);
    ReduceToTriangular(matrix, k, equations, variables);
  }

  SolveEquations(matrix, variables, result);

  return result;
}

int GaussSolver::FindMaxRow(const SLE::Matrix &matrix, int k, int equations) {
  double max_value = fabs(matrix[k][k]);
  int max_row = k;
  for (int i = k + 1; i < equations; ++i) {
    if (fabs(matrix[i][k] - max_value) > kEPS) {
      max_value = fabs(matrix[i][k]);
      max_row = i;
    }
  }
  return max_row;
}

void GaussSolver::SwapRows(SLE::Matrix &matrix, int k, int max_row) {
  if (max_row != k) {
    std::swap(matrix[k], matrix[max_row]);
  }
}

void GaussSolver::ReduceToTriangular(SLE::Matrix &matrix, int k, int equations,
                                     int variables) {
  for (int i = k + 1; i < equations; ++i) {
    double coeff = (-matrix[i][k]) / matrix[k][k];
    for (int j = k + 1; j <= variables; ++j) {
      matrix[i][j] += coeff * matrix[k][j];
    }
  }
}

void GaussSolver::SolveEquations(const SLE::Matrix &matrix, int variables,
                                 std::vector<double> &result) {
  for (int i = variables - 1; i >= 0; --i) {
    result[i] = matrix[i][variables];
    for (int j = i + 1; j < variables; ++j) {
      result[i] -= matrix[i][j] * result[j];
    }
    result[i] /= matrix[i][i];
  }
}
