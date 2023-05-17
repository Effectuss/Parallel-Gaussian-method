#include "generator_SLE.h"

SLE GeneratorSLE::GenerateSLE(int equations_count) {
  SLE::Matrix coefficient_matrix(equations_count, Vector(equations_count));
  Vector vector_constants(equations_count);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(-100000.0, 100000.0);
  for (int i = 0; i < equations_count; ++i) {
    for (int j = 0; j <= equations_count; ++j) {
      if (j != equations_count) {
        coefficient_matrix[i][j] = dis(gen);
      } else {
        vector_constants[i] = dis(gen);
      }
    }
  }
  return SLE(coefficient_matrix, vector_constants);
}
