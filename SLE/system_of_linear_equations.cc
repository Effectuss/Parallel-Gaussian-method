#include "system_of_linear_equations.h"

int SLE::FindRankOfMatrix(Matrix matrix) {
  int rows = matrix.size();
  int cols = matrix.at(0).size();
  int rank = 0;

  for (int j = 0; j < cols; ++j) {
    int pivot_row = -1;
    // Find the row with the modulo maximum element in column j
    double max_value = 0.0;
    for (int i = rank; i < rows; ++i) {
      double abs_value = fabs(matrix[i][j]);
      if (fabs(abs_value - max_value) > kEPS) {
        max_value = abs_value;
        pivot_row = i;
      }
    }

    if (pivot_row == -1 || max_value < kEPS) {
      // If all elements below the `rank` line in the column are zero,
      // move on to the next column.
      continue;
    }

    std::swap(matrix[rank], matrix[pivot_row]);

    // Reduce all subsequent lines below the `rank` line
    double pivot_value = matrix[rank][j];
    for (int i = rank + 1; i < rows; ++i) {
      double coeff = (-matrix[i][j]) / pivot_value;
      matrix[i][j] = 0.0;

      for (int k = j + 1; k < cols; ++k) {
        matrix[i][k] += coeff * matrix[rank][k];
      }
    }

    ++rank;
  }

  return rank;
}

bool SLE::IsLinearSystemCompatible() const {
  if (!IsEmptySystem()) {
    int amount_variable = augmented_matrix_.at(0).size() - 1;
    int amount_equations = augmented_matrix_.size();
    return !(amount_equations < amount_variable) &&
           SLE::FindRankOfMatrix(augmented_matrix_) ==
               SLE::FindRankOfMatrix(coefficient_matrix_);
  }
  return false;
}

const SLE::Matrix& SLE::GetAugmentedMatrix() const { return augmented_matrix_; }

const SLE::Matrix& SLE::GetCoefficientMatrix() const {
  return coefficient_matrix_;
}

const std::vector<double>& SLE::GetVectorOfConstants() const {
  return vector_of_constants_;
}

int SLE::GetAmountOfEquations() const { return rows_augmented_matrix_; }

int SLE::GetAmountOfVariable() const { return cols_augmented_matrix_ - 1; }

bool SLE::IsEmptySystem() const { return augmented_matrix_.empty(); }

void SLE::ResizeAugmentedMatrix() {
  augmented_matrix_ = std::move(Matrix(
      rows_augmented_matrix_, std::vector<double>(cols_augmented_matrix_)));
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

const double& SLE::operator()(int rows, int cols) const {
  if (rows >= rows_augmented_matrix_ || cols >= cols_augmented_matrix_) {
    throw std::out_of_range("Out of range!");
  }
  return augmented_matrix_.at(rows).at(cols);
}

SLE::SLE(const Matrix& coefficient_matrix,
         const std::vector<double>& vector_constants)
    : coefficient_matrix_{coefficient_matrix},
      vector_of_constants_{vector_constants},
      rows_augmented_matrix_{coefficient_matrix.size()},
      cols_augmented_matrix_{coefficient_matrix.size() + 1} {
  ResizeAugmentedMatrix();
  CreateAugmentedMatrix();
}
