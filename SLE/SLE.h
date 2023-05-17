#ifndef _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_
#define _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "gauss_solver.h"

class SLE {
 public:
  using Matrix = std::vector<std::vector<double> >;

  SLE() = default;
  SLE(const Matrix& coefficient_matrix,
      const std::vector<double>& vector_constants);
  SLE(const SLE& other_system) = default;
  SLE(SLE&& other_system) = default;
  SLE& operator=(const SLE& other_system) = default;
  SLE& operator=(SLE&& other_system) = default;
  ~SLE() = default;

  const double& operator()(int rows, int cols) const;

  const Matrix& GetAugmentedMatrix() const;
  const Matrix& GetCoefficientMatrix() const;
  const std::vector<double>& GetVectorOfConstants() const;
  int GetAmountOfEquations() const;
  int GetAmountOfVariable() const;
  const std::vector<double> GetParallelResultSLE() const;
  const std::vector<double> GetSerialResultSLE() const;

  bool IsLinearSystemCompatible() const;
  std::vector<double> SolveSLEGauss(GaussSolver::TypeOfGaussAlgo type_algo,
                                    int execution_count);

 private:
  int FindRankOfMatrix(Matrix matrix) const;
  int FindPivotRow(const Matrix& matrix, const int j, const int start_row,
                   const int end_row) const;
  void SwapRows(Matrix& matrix, const int row1, const int row2) const;
  void EliminateSubsequentRows(Matrix& matrix, const int rank,
                               const int col) const;

  bool IsEmptySystem() const;
  void ResizeAugmentedMatrix();
  void CreateAugmentedMatrix();

  static constexpr double kEPS = 1e-6;

  Matrix coefficient_matrix_{};
  std::vector<double> vector_of_constants_{};
  int rows_augmented_matrix_{};
  int cols_augmented_matrix_{};
  Matrix augmented_matrix_{};
  GaussSolver gauss_solver_;
};

#endif  // _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_