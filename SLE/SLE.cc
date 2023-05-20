#include "SLE.h"

int SLE::FindRankOfMatrix(Matrix matrix) const {
  int rows = matrix.size();
  int cols = matrix.at(0).size();
  int rank = 0;

  for (int j = 0; j < cols; ++j) {
    int pivot_row = FindPivotRow(matrix, j, rank, rows - 1);
    if (pivot_row == -1) {
      continue;
    }

    SwapRows(matrix, rank, pivot_row);
    EliminateSubsequentRows(matrix, rank, j);

    ++rank;
  }

  return rank;
}

int SLE::FindPivotRow(const SLE::Matrix &matrix, const int j,
                      const int start_row, const int end_row) const {
  int pivot_row = -1;
  double max_value = 0.0;
  const double kEPS = 1e-9;

  for (int i = start_row; i <= end_row; ++i) {
    double abs_value = fabs(matrix[i][j]);
    if (fabs(abs_value - max_value) > kEPS) {
      max_value = abs_value;
      pivot_row = i;
    }
  }

  return pivot_row;
}

void SLE::SwapRows(SLE::Matrix &matrix, const int row1, const int row2) const {
  std::swap(matrix[row1], matrix[row2]);
}

void SLE::EliminateSubsequentRows(Matrix &matrix, const int rank,
                                  const int col) const {
  int rows = matrix.size();
  int cols = matrix.at(0).size();

  double pivot_value = matrix[rank][col];
  for (int i = rank + 1; i < rows; ++i) {
    double coeff = (-matrix[i][col]) / pivot_value;
    matrix[i][col] = 0.0;

    for (int k = col + 1; k < cols; ++k) {
      matrix[i][k] += coeff * matrix[rank][k];
    }
  }
}

bool SLE::IsLinearSystemCompatible() const {
  if (!IsEmptySystem()) {
    int amount_variable = augmented_matrix_.at(0).size() - 1;
    int amount_equations = augmented_matrix_.size();
    return !(amount_equations < amount_variable) &&
           FindRankOfMatrix(augmented_matrix_) ==
               FindRankOfMatrix(coefficient_matrix_);
  }
  return false;
}

std::vector<double> SLE::SolveSLEGauss(GaussSolver::TypeOfGaussAlgo type_algo,
                                       int execution_count) {
  if (!IsLinearSystemCompatible()) {
    throw std::logic_error("The system cant be solve");
  }
  if (execution_count > 100000 || execution_count <= 0) {
    throw std::invalid_argument(
        "The number of executions must be between 1 and 100000");
  }
  if (IsEmptySystem()) {
    throw std::logic_error("The system is empty!");
  }
  std::vector<double> result;
  int max_thread = std::thread::hardware_concurrency();
  while (execution_count--) {
    if (type_algo == GaussSolver::TypeOfGaussAlgo::kParallel) {
      result = gauss_solver_.SolveParallelGauss(*this, max_thread);
    } else if (type_algo == GaussSolver::TypeOfGaussAlgo::kSerial) {
      result = gauss_solver_.SolveSerialGauss(*this);
    }
  }
  return result;
}

const SLE::Matrix &SLE::GetAugmentedMatrix() const { return augmented_matrix_; }

const SLE::Matrix &SLE::GetCoefficientMatrix() const {
  return coefficient_matrix_;
}

const std::vector<double> &SLE::GetVectorOfConstants() const {
  return vector_of_constants_;
}

int SLE::GetAmountOfEquations() const { return rows_augmented_matrix_; }

int SLE::GetAmountOfVariable() const { return cols_augmented_matrix_ - 1; }

const std::vector<double> SLE::GetParallelResultSLE() const {
  if (!IsLinearSystemCompatible()) {
    throw std::logic_error("The system cant be solve");
  }
  std::vector<double> result;
  int max_thread = std::thread::hardware_concurrency();
  result = gauss_solver_.SolveParallelGauss(*this, max_thread);
  return result;
}

const std::vector<double> SLE::GetSerialResultSLE() const {
  if (!IsLinearSystemCompatible()) {
    throw std::logic_error("The system cant be solve");
  }
  std::vector<double> result;
  result = gauss_solver_.SolveSerialGauss(*this);
  return result;
}

bool SLE::IsEmptySystem() const { return augmented_matrix_.empty(); }

void SLE::ResizeAugmentedMatrix() {
  augmented_matrix_ = Matrix(rows_augmented_matrix_,
                             std::vector<double>(cols_augmented_matrix_));
}

void SLE::CreateAugmentedMatrix() {
  for (int i = 0; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      if (j != cols_augmented_matrix_ - 1) {
        augmented_matrix_[i][j] = coefficient_matrix_[i][j];
      } else {
        augmented_matrix_[i][j] = vector_of_constants_[i];
      }
    }
  }
}

const double &SLE::operator()(int rows, int cols) const {
  if (rows >= rows_augmented_matrix_ || cols >= cols_augmented_matrix_ ||
      cols < 0 || rows < 0) {
    throw std::out_of_range("Out of range!");
  }
  return augmented_matrix_.at(rows).at(cols);
}

SLE::SLE(const Matrix &coefficient_matrix,
         const std::vector<double> &vector_constants)
    : coefficient_matrix_{coefficient_matrix},
      vector_of_constants_{vector_constants},
      rows_augmented_matrix_{(int)coefficient_matrix.size()},
      cols_augmented_matrix_{(int)coefficient_matrix.size() + 1} {
  ResizeAugmentedMatrix();
  CreateAugmentedMatrix();
}
