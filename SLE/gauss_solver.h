#ifndef _SLE_GAUSS_SOLVER_H_
#define _SLE_GAUSS_SOLVER_H_

#include <mutex>
#include <thread>
#include <vector>

#include "barrier.h"

class SLE;

class GaussSolver {
 public:
  enum TypeOfGaussAlgo { kParallel, kSerial };

  static std::vector<double> SolveSerialGauss(const SLE& system);
  static std::vector<double> SolveParallelGauss(const SLE& system,
                                                int numb_thread);

 private:
  using Matrix = std::vector<std::vector<double> >;
  using Vector = std::vector<double>;

  static int FindMaxRow(const Matrix& matrix, int pivot_row, int size);
  static void SwapRows(Matrix& matrix, int pivot_row, int max_row);
  static void NullifyColumn(Matrix& matrix, int pivot_row, int size);
  static void SolveEquations(const Matrix& matrix, int size,
                             std::vector<double>& result);

  static void MakeDiagonalSystem(Matrix& matrix, Barrier& barrier,
                                 Barrier& phase_one, int start, int end,
                                 int size);
  static void PerformForwardSubstitution(Matrix& matrix, int start, int end,
                                         Barrier& barrier, int size);
  static void PerformBackwardSubstitution(Matrix& matrix, int start, int end,
                                          Barrier& barrier, int size);

  static constexpr double kEPS = 1e-6;
};
#endif  // _SLE_GAUSS_SOLVER_H_