#include "gauss_solver.h"

#include "SLE.h"

std::vector<double> GaussSolver::SolveParallelGauss(SLE system) const {
  std::vector<double> result;
  int size = system.GetAmountOfEquations();
  // int num_treads = std::thread::hardware_concurrency();
  // int num_treads = 3;
  Matrix matrix = system.GetAugmentedMatrix();
  // for (int i = 0; i < size; ++i) {
  //   for (int j = 0; j < size; ++j) {
  //     std::cout << matrix[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // int c;
  // std::cin >> c;
  for (int k = 0; k < size - 1; ++k) {
    MakeTreangularMatrix(matrix, k + 1, size - 1, k);
  }
  // std::cout << "GO AHEAD" << std::endl;
  // int c;
  // for (int l = 0; l < (int)matrix.size(); ++l) {
  //   for (int m = 0; m < (int)matrix[l].size(); ++m) {
  //     std::cout << std::setw(8) << std::left << matrix[l][m] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cin >> c;
  for (int k = size - 1; k > 0; --k) {
    MakeTreangularMatrix(matrix, 0, k - 1, k);
  }
  // for (int k = size - 1; k >= 0; --k) {
  //   if (k < num_treads) {
  //     num_treads = k;
  //   }
  //   int count = k / num_treads;
  //   int start = 0;
  //   for (int i = 0; i < num_treads; ++i) {
  //     if (i == num_treads - 1) {
  //       count = size - i * count - 1;
  //     }
  //     threads.emplace_back(&GaussSolver::NullifyColumnParallel, this,
  //                          std::ref(matrix), start, count, k);
  //     start += count;
  //   }
  //   for (auto &th : threads) {
  //     th.join();
  //   }
  //   threads.clear();
  // }
  // std::cout << "BACKWARD" << std::endl;
  // for (int l = 0; l < (int)matrix.size(); ++l) {
  //   for (int m = 0; m < (int)matrix[l].size(); ++m) {
  //     std::cout << std::setw(10) << std::left << matrix[l][m] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cin >> c;

  for (int i = 0; i < size; ++i) {
    result.push_back(matrix[i][size] / matrix[i][i]);
  }
  return result;
}

void GaussSolver::NullifyColumnParallel(Matrix &matrix, int start, int size,
                                        int opora) const {
  // std::cout << "NULLFASF" << std::endl;
  // std::cout << "START = " << start << std::endl;
  // std::cout << "SIZE = " << size << std::endl;
  // std::cout << "OPORA = " << size << std::endl;
  for (int i = start; i < std::min(size + start, (int)matrix.size()); ++i) {
    double coeff = (-matrix[i][opora]) / matrix[opora][opora];
    // int asd;
    for (int j = opora; j <= (int)matrix[i].size(); ++j) {
      // for (int l = 0; l < (int)matrix.size(); ++l) {
      //   for (int m = 0; m < (int)matrix[l].size(); ++m) {
      //     std::cout << matrix[l][m] << " ";
      //   }
      //   std::cout << std::endl;
      // }
      // std::cout << "COORD ELENT = " << i << " " << j << " " << opora << " "
      // << j
      //           << std::endl;
      matrix[i][j] += coeff * matrix[opora][j];
      // for (int l = 0; l < (int)matrix.size(); ++l) {
      //   for (int m = 0; m < (int)matrix[l].size(); ++m) {
      //     std::cout << matrix[l][m] << " ";
      //   }
      //   std::cout << std::endl;
      // }
      // std::cin >> asd;
    }
  }
}

void GaussSolver::MakeTreangularMatrix(Matrix &matrix, int start, int end,
                                       int row) const {
  std::vector<std::thread> threads;
  int row_count = end - start + 1;
  int thread_count =
      std::min((int)std::thread::hardware_concurrency(), row_count);
  int step = row_count / thread_count;
  // std::cout << "row_count = " << row_count << std::endl;
  // std::cout << "thread_count = " << thread_count << std::endl;
  // std::cout << "step = " << step << std::endl;
  // if (size - k - 1 < num_treads) {
  //   num_treads = size - k - 1;
  // }
  // int count = (size - k - 1) / num_treads;
  // int start = k + 1;

  for (int i = 0; i < thread_count; ++i) {
    // if (i == tread_count - 1) {
    //   count = size - i * count - 1;
    // }
    threads.emplace_back(&GaussSolver::NullifyColumnParallel, this,
                         std::ref(matrix), start, step, row);
    start += step;
  }

  for (auto &th : threads) {
    th.join();
  }

  threads.clear();
}

std::vector<double> GaussSolver::SolveSerialGauss(SLE system) const {
  int size = system.GetAmountOfEquations();
  SLE::Matrix matrix = system.GetAugmentedMatrix();
  std::vector<double> result(size);
  for (int k = 0; k < size; ++k) {
    int max_row = FindMaxRow(matrix, k, size);
    SwapRows(matrix, k, max_row);
    NullifyColumnSerial(matrix, k, size);
  }

  SolveEquations(matrix, size, result);

  return result;
}

int GaussSolver::FindMaxRow(const SLE::Matrix &matrix, int k,
                            int equations) const {
  double max_value = fabs(matrix[k][k]);
  int max_row = k;
  for (int i = k + 1; i < equations; ++i) {
    if (fabs(matrix[i][k] - max_value) > kEPS) {
      max_value = fabs(matrix[i][k]);
      max_row = i;
    }
  }
  return max_row;
}

void GaussSolver::SwapRows(SLE::Matrix &matrix, int k, int max_row) const {
  if (max_row != k) {
    std::swap(matrix[k], matrix[max_row]);
  }
}

void GaussSolver::NullifyColumnSerial(Matrix &matrix, int k, int size) const {
  for (int i = k + 1; i < size; ++i) {
    double coeff = (-matrix[i][k]) / matrix[k][k];
    for (int j = k + 1; j <= size; ++j) {
      matrix[i][j] += coeff * matrix[k][j];
    }
  }
}

void GaussSolver::SolveEquations(const SLE::Matrix &matrix, int variables,
                                 std::vector<double> &result) const {
  for (int i = variables - 1; i >= 0; --i) {
    result[i] = matrix[i][variables];
    for (int j = i + 1; j < variables; ++j) {
      result[i] -= matrix[i][j] * result[j];
    }
    result[i] /= matrix[i][i];
  }
}
