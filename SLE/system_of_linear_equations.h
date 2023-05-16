#ifndef _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_
#define _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class SLE {
 public:
  using Matrix = std::vector<std::vector<double> >;

  SLE() = delete;
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

  bool IsLinearSystemCompatible() const;

 private:
  static int FindRankOfMatrix(Matrix matrix);
  bool IsEmptySystem() const;

  void ResizeAugmentedMatrix();
  void CreateAugmentedMatrix();

  static constexpr double kEPS = 1e-6;
  int rows_augmented_matrix_;
  int cols_augmented_matrix_;
  Matrix augmented_matrix_;
  Matrix coefficient_matrix_;
  std::vector<double> vector_of_constants_;
};

#endif  // _SLE_SYSTEM_OF_LINEAR_EQUATIONS_H_