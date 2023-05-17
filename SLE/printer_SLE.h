#ifndef _SLE_PRINTER_SLE_H_
#define _SLE_PRINTER_SLE_H_

#include <iomanip>

#include "system_of_linear_equations.h"

class PrinterSLE {
 public:
  static void PrintSLE(const SLE& system) {
    std::cout << "\n\u001b[42;1mTHE SLE: \u001b[0m\n";
    for (int i = 0; i < system.GetAmountOfEquations(); ++i) {
      for (int j = 0; j <= system.GetAmountOfVariable(); ++j) {
        if (j == system.GetAmountOfVariable() - 1) {
          std::cout << std::setw(8) << std::left << system(i, j) << " | ";
        } else {
          std::cout << std::setw(8) << std::left << system(i, j) << " ";
        }
      }
      std::cout << std::endl;
    }
  }

  static void PrintParallelResultSLE(const SLE& system) {
    std::cout << "\n\u001b[42;1mPARALLEL ALGORITHM RESULT\u001b[0m\n";
    for (const auto& el : system.GetSerialResultSLE()) {
      std::cout << "\033[39m\033[1;29m" << el << " ";
    }
    std::cout << std::endl;
  }

  static void PrintSerialResultSLE(const SLE& system) {
    std::cout << "\n\u001b[42;1mSERIAL ALGORITHM RESULT\u001b[0m\n";
    for (const auto& el : system.GetSerialResultSLE()) {
      std::cout << "\033[39m\033[1;29m" << el << " ";
    }
    std::cout << std::endl;
  }
};

#endif  // _SLE_PRINTER_SLE_H_