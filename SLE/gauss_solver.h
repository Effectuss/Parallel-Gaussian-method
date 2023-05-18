#ifndef _SLE_GAUSS_SOLVER_H_
#define _SLE_GAUSS_SOLVER_H_

#include <pthread.h>

#include <mutex>
#include <thread>
#include <vector>

class SLE;

class GaussSolver {
 public:
  enum TypeOfGaussAlgo { kParallel, kSerial };

  std::vector<double> SolveSerialGauss(SLE system) const;
  std::vector<double> SolveParallelGauss(SLE system) const;

 private:
  using Matrix = std::vector<std::vector<double> >;

  int FindMaxRow(const Matrix& matrix, int k, int equations) const;
  void SwapRows(Matrix& matrix, int k, int max_row) const;
  void NullifyColumnSerial(Matrix& matrix, int k, int size) const;
  void SolveEquations(const Matrix& matrix, int variables,
                      std::vector<double>& result) const;
  void NullifyColumnParallel(Matrix& matrix, int start, int size,
                             int opora) const;
  void MakeTreangularMatrix(Matrix& matrix, int start, int end, int row) const;

  static constexpr double kEPS = 1e-6;
};
#endif  // _SLE_GAUSS_SOLVER_H_