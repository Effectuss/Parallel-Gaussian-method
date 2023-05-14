#ifndef _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_
#define _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_

#include <fstream>
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
  SystemOfLinearEquations(const SystemOfLinearEquations& other_system) =
      default;
  SystemOfLinearEquations(SystemOfLinearEquations&& other_system) = default;
  SystemOfLinearEquations& operator=(
      const SystemOfLinearEquations& other_system) = default;
  SystemOfLinearEquations& operator=(SystemOfLinearEquations&& other_system) =
      default;
  ~SystemOfLinearEquations() = default;

  const Matrix& GetAugmentedMatrix() const;
  const Matrix& GetCoefficientMatrix() const;
  const std::vector<double>& GetVectorOfConstants() const;
  int GetAmountOfEquations() const;
  int GetAmountOfVariable() const;

  void GenerateAugmentedMatrix();
  void PrintSystemOfLinearEquations();
  void ReadAugmentedMatrixFromFile(const std::string& file_name);
  void ReadAugmentedMatrixFromConsole();

  bool IsLinearSystemCompatible();

 private:
  static int FindRankOfMatrix(Matrix matrix);

  bool IsEmptySystem();

  void CreateCoefficientMantrixAndVectorOfConstants();
  void ResizeAugmentedMatrix();

  void ReadIndexForAugmentedMatrixFromConsole();

  // Methods for work with file
  void ReadIndexForAugmentedMatrixFromFile(std::ifstream& file);
  void FillMatrixFromFile(std::ifstream& file);
  void ClearAndIgnoreCin();

  static constexpr double kEPS = 1e-6;
  int rows_augmented_matrix_;
  int cols_augmented_matrix_;
  Matrix augmented_matrix_;
  Matrix coefficient_matrix_;
  std::vector<double> vector_of_constants_;
};

#endif  // _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_