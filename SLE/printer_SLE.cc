#include "printer_SLE.h"

void PrinterSLE::PrintSLE(const SLE& system) {
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

void PrinterSLE::PrintParallelResultSLE(const SLE& system) {
  std::cout << "\n\u001b[42;1mPARALLEL ALGORITHM RESULT\u001b[0m\n";
  std::vector<double> res = system.GetParallelResultSLE();
  for (const auto& el : res) {
    std::cout << "\033[39m\033[1;29m" << el << " ";
  }
  std::cout << std::endl;
}

void PrinterSLE::PrintSerialResultSLE(const SLE& system) {
  std::cout << "\n\u001b[42;1mSERIAL ALGORITHM RESULT\u001b[0m\n";
  std::vector<double> res = system.GetSerialResultSLE();
  for (const auto& el : res) {
    std::cout << "\033[39m\033[1;29m" << el << " ";
  }
  std::cout << std::endl;
}
