#include "gauss_solver.h"

#include "SLE.h"

void GaussSolver::MakeDiagonalSystem(Matrix& matrix, Barrier& barrier,
                                     Barrier& phase_one, int start, int end,
                                     int size) const {
  PerformForwardSubstitution(matrix, start, end, barrier, size);
  if (end == size) {
    matrix[end - 1][end] /= matrix[end - 1][end - 1];
  }
  phase_one.Wait();
  PerformBackwardSubstitution(matrix, start, end, barrier, size);
}

void GaussSolver::PerformForwardSubstitution(Matrix& matrix, int start, int end,
                                             Barrier& barrier, int size) const {
  for (int k = 0; k < size - 1; ++k) {
    for (int i = k + 1; i < size; ++i) {
      if ((i >= start) && (i < end)) {
        double coeff = (-matrix[i][k]) / matrix[k][k];
        for (int j = 1; j <= size; ++j) {
          matrix[i][j] += coeff * matrix[k][j];
        }
      }
    }
    barrier.Wait();
  }
}

void GaussSolver::PerformBackwardSubstitution(Matrix& matrix, int start,
                                              int end, Barrier& barrier,
                                              int size) const {
  for (int i = size - 2; i >= 0; --i) {
    if ((i >= start) && (i < end)) {
      for (int j = i + 1; j < size; ++j) {
        matrix[i][size] -= matrix[i][j] * matrix[j][size];
      }
      matrix[i][size] /= matrix[i][i];
    }
    barrier.Wait();
  }
}

std::vector<double> GaussSolver::SolveParallelGauss(SLE system,
                                                    int numb_thread) const {
  if (numb_thread > std::thread::hardware_concurrency() || numb_thread <= 0) {
    throw std::logic_error("The number of threads incorrect! Try again!");
  }

  std::vector<std::thread> pool_thread;
  Barrier barrier(numb_thread), phase_one(numb_thread);
  int size = system.GetAmountOfEquations();
  int step_interval = size / (numb_thread - 1);
  SLE::Matrix matrix = system.GetAugmentedMatrix();

  for (int i = 0; i < numb_thread - 1; ++i) {
    int start = step_interval * i;
    int end = step_interval * (i + 1);
    pool_thread.emplace_back(&GaussSolver::MakeDiagonalSystem, this,
                             std::ref(matrix), std::ref(barrier),
                             std::ref(phase_one), start, end, size);
  }

  for (auto& th : pool_thread) {
    if (th.joinable()) {
      th.join();
    }
  }

  std::vector<double> result;
  for (int i = 0; i < size; ++i) result.push_back(system(i, size));

  return result;
}

std::vector<double> GaussSolver::SolveSerialGauss(SLE system) const {
  int size = system.GetAmountOfEquations();
  SLE::Matrix matrix = system.GetAugmentedMatrix();
  std::vector<double> result(size);
  for (int k = 0; k < size; ++k) {
    int max_row = FindMaxRow(matrix, k, size);
    int pivot_row = k;
    SwapRows(matrix, pivot_row, max_row);
    NullifyColumn(matrix, pivot_row, size);
  }

  SolveEquations(matrix, size, result);

  return result;
}

int GaussSolver::FindMaxRow(const SLE::Matrix& matrix, int pivot_row,
                            int size) const {
  double max_value = fabs(matrix[pivot_row][pivot_row]);
  int max_row = pivot_row;
  for (int i = pivot_row + 1; i < size; ++i) {
    if (fabs(matrix[i][pivot_row] - max_value) > kEPS) {
      max_value = fabs(matrix[i][pivot_row]);
      max_row = i;
    }
  }
  return max_row;
}

void GaussSolver::SwapRows(SLE::Matrix& matrix, int pivot_row,
                           int max_row) const {
  if (max_row != pivot_row) {
    std::swap(matrix[pivot_row], matrix[max_row]);
  }
}

void GaussSolver::NullifyColumn(Matrix& matrix, int pivot_row, int size) const {
  for (int i = pivot_row + 1; i < size; ++i) {
    double coeff = (-matrix[i][pivot_row]) / matrix[pivot_row][pivot_row];
    for (int j = pivot_row + 1; j <= size; ++j) {
      matrix[i][j] += coeff * matrix[pivot_row][j];
    }
  }
}

void GaussSolver::SolveEquations(const SLE::Matrix& matrix, int size,
                                 std::vector<double>& result) const {
  for (int i = size - 1; i >= 0; --i) {
    result[i] = matrix[i][size];
    for (int j = i + 1; j < size; ++j) {
      result[i] -= matrix[i][j] * result[j];
    }
    result[i] /= matrix[i][i];
  }
}
