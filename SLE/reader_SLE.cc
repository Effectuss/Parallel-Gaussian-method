#include "reader_SLE.h"

const std::string ReaderSLE::kCoefficientFormat{
    "\033[39m\033[1;29mCoefficient x"};
const std::string ReaderSLE::kResultFormat{"\033[39m\033[1;29mResult = "};

SLE ReaderSLE::ReadSLEFromConsole() {
  int equations_count = ReadSizeSLEFromConsole();
  SLE::Matrix coefficient_matrix(equations_count, Vector(equations_count));
  Vector vector_constants(equations_count);
  FillSLEValuesFromConsole(coefficient_matrix, vector_constants);
  return SLE(coefficient_matrix, vector_constants);
}

SLE ReaderSLE::ReadSLEFromFile(const std::string &file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::logic_error("THE FILE DOESNT'T EXIST!");
  }
  int equations_count = ReadSizeSLEFromFile(file);
  SLE::Matrix coefficient_matrix(equations_count, Vector(equations_count));
  Vector vector_constants(equations_count);
  FillSLEFromFile(file, coefficient_matrix, vector_constants);
  return SLE(coefficient_matrix, vector_constants);
}

int ReaderSLE::ReadSizeSLEFromConsole() {
  std::cout << "\u001b[42;1mENTER SLE DIMENSION: \u001b[0m\n> ";
  int equations_count = 0;
  bool valid_input = false;
  do {
    std::cin >> equations_count;
    if (std::cin.peek() != '\n') {
      ClearAndIgnoreCin();
    } else if (equations_count <= 0) {
      ClearAndIgnoreCin();
    } else {
      valid_input = true;
    }
  } while (!valid_input);
  return equations_count;
}

int ReaderSLE::ReadSizeSLEFromFile(std::ifstream &file) {
  int equations_count = 0;
  file >> equations_count;
  if (file.peek() != '\n' || equations_count <= 0) {
    throw std::logic_error("THE FIRST LINE IN FILE INCORRECT");
  } else {
    file.get();
  }
  return equations_count;
}

void ReaderSLE::ClearAndIgnoreCin() {
  std::cout << "\u001b[41;1mWRONG INPUT! TRUE AGAIN!\u001b[0m\n";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ReaderSLE::FillSLEValuesFromConsole(SLE::Matrix &coefficient_matrix,
                                         Vector &vector_constants) {
  for (int i = 0; i < static_cast<int>(coefficient_matrix.size()); ++i) {
    int coefficient_x = 1;
    int cols = coefficient_matrix.at(i).size();
    for (int j = 0; j <= cols; ++j) {
      if (coefficient_x != cols + 1) {
        std::cout << kCoefficientFormat << coefficient_x << " = ";
        std::cin >> coefficient_matrix[i][j];
      } else {
        std::cout << kResultFormat;
        std::cin >> vector_constants[i];
      }
      if (std::cin.peek() != '\n') {
        ClearAndIgnoreCin();
        --j;
      } else {
        ++coefficient_x;
      }
    }
  }
}

void ReaderSLE::FillSLEFromFile(std::ifstream &file,
                                SLE::Matrix &coefficient_matrix,
                                Vector &vector_constants) {
  int size = coefficient_matrix.size();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j <= size; ++j) {
      if (j != size) {
        file >> coefficient_matrix[i][j];
      } else {
        file >> vector_constants[i];
      }
      if (file.fail() || file.bad()) {
        throw std::logic_error("DATA IN AUGMENTED MATRIX INCORRECT");
      }
    }
  }
  if (!file.eof()) {
    throw std::logic_error("THE FILE HAVE INCORRECT DATA FOR AUGMENTED MATRIX");
  }
}