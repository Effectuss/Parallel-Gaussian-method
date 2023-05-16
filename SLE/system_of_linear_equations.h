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
#include "generator_SLE.h"
#include "printer_SLE.h"
#include "reader_SLE.h"

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
  std::vector<double>& GetResultSLE(
      GaussSolver::TypeOfGaussAlgo type_of_algo) const;

  bool IsLinearSystemCompatible() const;
  void SolveSLEGauss(GaussSolver::TypeOfGaussAlgo type_algo,
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

  int rows_augmented_matrix_ = 0;
  int cols_augmented_matrix_ = 0;
  Matrix augmented_matrix_{};
  Matrix coefficient_matrix_{};
  std::vector<double> vector_of_constants_{};
  GaussSolver gauss_solver_;

  std::vector<double> res_serial_algo_;
  std::vector<double> res_parallel_algo_;
};

#endif  // _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_