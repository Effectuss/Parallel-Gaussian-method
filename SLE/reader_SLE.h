#ifndef _SLE_READER_SLE_H_
#define _SLE_READER_SLE_H_

#include "SLE.h"

class ReaderSLE {
 public:
  static SLE ReadSLEFromConsole();
  static SLE ReadSLEFromFile(const std::string& file_name);
  static int ReadSizeSLEFromConsole();

 private:
  using Vector = std::vector<double>;

  static void ClearAndIgnoreCin();
  static int ReadSizeSLEFromFile(std::ifstream& file);
  static void FillSLEValuesFromConsole(SLE::Matrix& coefficient_matrix,
                                       Vector& vector_constants);

  static void FillSLEFromFile(std::ifstream& file,
                              SLE::Matrix& coefficient_matrix,
                              Vector& vector_constants);

  static const std::string kCoefficientFormat;
  static const std::string kResultFormat;
};

#endif  // _SLE_READER_SLE_H_