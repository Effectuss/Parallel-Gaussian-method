#ifndef _SLE_GAUSS_SOLVER_H_
#define _SLE_GAUSS_SOLVER_H_

#include <pthread.h>

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

#include "barrier.h"

class SLE;

class GaussSolver {
 public:
  enum TypeOfGaussAlgo { kParallel, kSerial };

  std::vector<double> SolveSerialGauss(SLE system) const;
  std::vector<double> SolveParallelGauss(SLE system, int numb_thread) const;

 private:
  using Matrix = std::vector<std::vector<double> >;
  using Vector = std::vector<double>;

  int FindMaxRow(const Matrix& matrix, int pivot_row, int size) const;
  void SwapRows(Matrix& matrix, int pivot_row, int max_row) const;
  void NullifyColumn(Matrix& matrix, int pivot_row, int size) const;
  void SolveEquations(const Matrix& matrix, int size,
                      std::vector<double>& result) const;

  void MakeDiagonalSystem(Matrix& matrix, Barrier& barrier, Barrier& phase_one,
                          int start, int end, int size) const;
  void PerformForwardSubstitution(Matrix& matrix, int start, int end,
                                  Barrier& barrier, int size) const;
  void PerformBackwardSubstitution(Matrix& matrix, int start, int end,
                                   Barrier& barrier, int size) const;

  static constexpr double kEPS = 1e-6;
};
#endif  // _SLE_GAUSS_SOLVER_H_