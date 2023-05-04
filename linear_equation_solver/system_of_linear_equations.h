#ifndef _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_
#define _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_

#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class SystemOfLinearEquations {
 public:
  using Matrix = std::vector<std::vector<double> >;

  SystemOfLinearEquations() = default;
  SystemOfLinearEquations(int amount_variable, int equations);

  // ?
  void ReadAugmentedMatrixFromFile(const std::string& filename);

  void ReadAugmentedMatrixFromConsole();
  void GenerateAugmentedMatrix();
  void PrintSystemOfLinearEquations();

  // ?
  bool IsCompabilitySystem();

 private:
  void CreateCoefficientMantrixAndVectorOfConstants();
  void ClearAndIgnoreCin();
  void ReadIndexForAugmentedMatrix();
  void ResizeAugmentedMatrix();

  int rows_augmented_matrix_;
  int cols_augmented_matrix_;
  Matrix augmented_matrix_;
  Matrix coefficient_matrix_;
  std::vector<double> vector_of_constants_;
};

#endif  // _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_