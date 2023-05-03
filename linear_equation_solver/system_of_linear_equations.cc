#include "system_of_linear_equations.h"

void SystemOfLinearEquations::ReadAugmentedMatrixFromFile() {}

void SystemOfLinearEquations::ReadAugmentedMatrixFromConsole() {
  ReadIndexForAugmentedMatrix();
  augmented_matrix_ = std::move(Matrix(
      rows_augmented_matrix_, std::vector<double>(cols_augmented_matrix_)));
  for (int i = 0, coefficient_x = 1; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      if (coefficient_x != cols_augmented_matrix_) {
        std::cout << "Coefficient x" << coefficient_x << " = ";
      } else {
        std::cout << "Result = ";
      }
      double tmp;
      std::cin >> tmp;
      if (std::cin.fail()) {
        ClearAndIgnoreCin();
        --j;
      } else {
        augmented_matrix_[i][j] = tmp;
        ++coefficient_x;
      }
    }
    coefficient_x = 1;
  }
  CreateCoefficientMantrixAndVectorOfConstants();
  PrintSystemOfLinearEquations();
}

void SystemOfLinearEquations::GenerateAugmentedMatrix() {}

void SystemOfLinearEquations::PrintSystemOfLinearEquations() {
  for (int i = 0; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      if (j == cols_augmented_matrix_ - 2) {
        std::cout << augmented_matrix_[i][j] << "|";
      } else {
        std::cout << augmented_matrix_[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}

void SystemOfLinearEquations::CreateCoefficientMantrixAndVectorOfConstants() {
  if (vector_of_constants_.empty() && coefficient_matrix_.empty()) {
    return;
  } else {
    coefficient_matrix_.resize(rows_augmented_matrix_);
    for (int i = 0; i < rows_augmented_matrix_; ++i) {
      for (int j = 0; j < cols_augmented_matrix_; ++j) {
        if (j != cols_augmented_matrix_ - 1) {
          coefficient_matrix_[i].push_back(augmented_matrix_[i][j]);
        } else {
          vector_of_constants_.push_back(augmented_matrix_[i][j]);
        }
      }
    }
  }
}

void SystemOfLinearEquations::ClearAndIgnoreCin() {
  std::cout << "\u001b[41;1mWRONG INPUT! TRUE AGAIN!\u001b[0m\n> ";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void SystemOfLinearEquations::ReadIndexForAugmentedMatrix() {
  std::cout << "\u001b[42;1mENTER AUGMENTED MATRIX DIMENSION: \u001b[0m\n> ";
  bool valid_input = false;
  do {
    std::cin >> rows_augmented_matrix_ >> cols_augmented_matrix_;
    if (std::cin.peek() != '\n') {
      ClearAndIgnoreCin();
    } else if (rows_augmented_matrix_ <= 0 || cols_augmented_matrix_ <= 0) {
      ClearAndIgnoreCin();
    } else {
      valid_input = true;
    }
  } while (!valid_input);
}

SystemOfLinearEquations::SystemOfLinearEquations(int amount_variable,
                                                 int amount_equations)
    : rows_augmented_matrix_{amount_equations},
      cols_augmented_matrix_{amount_variable + 1} {
  augmented_matrix_ = std::move(Matrix(
      rows_augmented_matrix_, std::vector<double>(cols_augmented_matrix_)));
}
