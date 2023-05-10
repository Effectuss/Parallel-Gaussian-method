#include "system_of_linear_equations.h"

void SystemOfLinearEquations::ReadAugmentedMatrixFromFile(
    const std::string& file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::logic_error("THE FILE DOESNT'T EXIST!");
  } else {
    ReadIndexForAugmentedMatrixFromFile(file);
    ResizeAugmentedMatrix();
    FillMatrixFromFile(file);
  }
  CreateCoefficientMantrixAndVectorOfConstants();
}

void SystemOfLinearEquations::ReadAugmentedMatrixFromConsole() {
  ReadIndexForAugmentedMatrixFromConsole();
  ResizeAugmentedMatrix();
  for (int i = 0, coefficient_x = 1; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      if (coefficient_x != cols_augmented_matrix_) {
        std::cout << "\033[39m\033[1;29mCoefficient x" << coefficient_x
                  << " = ";
      } else {
        std::cout << "\033[39m\033[1;29mResult = ";
      }
      std::cin >> augmented_matrix_[i][j];
      if (std::cin.peek() != '\n') {
        ClearAndIgnoreCin();
        --j;
      } else {
        ++coefficient_x;
      }
    }
    coefficient_x = 1;
  }
  CreateCoefficientMantrixAndVectorOfConstants();
}

void SystemOfLinearEquations::GenerateAugmentedMatrix() {
  ReadIndexForAugmentedMatrixFromConsole();
  ResizeAugmentedMatrix();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
  for (int i = 0; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      augmented_matrix_[i][j] = dis(gen);
    }
  }
  CreateCoefficientMantrixAndVectorOfConstants();
}

void SystemOfLinearEquations::PrintSystemOfLinearEquations() {
  std::cout << "\n\u001b[42;1mTHE CURRENT AUGMENTED MATRIX: \u001b[0m\n";
  for (int i = 0; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      if (j == cols_augmented_matrix_ - 2) {
        std::cout << augmented_matrix_[i][j] << " | ";
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
  std::cout << "\u001b[41;1mWRONG INPUT! TRUE AGAIN!\u001b[0m\n";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void SystemOfLinearEquations::ReadIndexForAugmentedMatrixFromConsole() {
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

void SystemOfLinearEquations::ResizeAugmentedMatrix() {
  augmented_matrix_ = std::move(Matrix(
      rows_augmented_matrix_, std::vector<double>(cols_augmented_matrix_)));
}

void SystemOfLinearEquations::ReadIndexForAugmentedMatrixFromFile(
    std::ifstream& file) {
  file >> rows_augmented_matrix_ >> cols_augmented_matrix_;
  if (file.peek() != '\n' || rows_augmented_matrix_ <= 0 ||
      cols_augmented_matrix_ <= 0) {
    throw std::logic_error("THE FIRST LINE IN FILE INCORRECT");
  } else {
    file.get();
  }
}

void SystemOfLinearEquations::FillMatrixFromFile(std::ifstream& file) {
  for (int i = 0; i < rows_augmented_matrix_; ++i) {
    for (int j = 0; j < cols_augmented_matrix_; ++j) {
      file >> augmented_matrix_[i][j];
      if (file.fail() || file.bad()) {
        throw std::logic_error("DATA IN AUGMENTED MATRIX INCORRECT");
      }
    }
  }
  if (!file.eof()) {
    throw std::logic_error("THE FILE HAVE INCORRECT DATA FOR AUGMENTED MATRIX");
  }
}

SystemOfLinearEquations::SystemOfLinearEquations(int amount_variable,
                                                 int amount_equations)
    : rows_augmented_matrix_{amount_equations},
      cols_augmented_matrix_{amount_variable + 1} {
  augmented_matrix_ = std::move(Matrix(
      rows_augmented_matrix_, std::vector<double>(cols_augmented_matrix_)));
}
