#ifndef _SLE_GENERATOR_SLE_H_
#define _SLE_GENERATOR_SLE_H_

#include "SLE.h"

class GeneratorSLE {
 public:
  static SLE GenerateSLE(int equations_count);

 private:
  using Vector = std::vector<double>;
};

#endif  // _SLE_GENERATOR_SLE_H_