#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <iostream>
#include <string>
#include <vector>

#include "../linear_equation_solver/system_of_linear_equations.h"
#include "../utils/timer.h"

class ConsoleInterface {
 public:
  void Exec();

 private:
  void StartFirstPartMenu();
  bool SelectItemForFirstPartMenu();
  std::string ReadFullPathToFile();

  bool StartSecondPartMenu();
  bool SelectItemForSecondPartMenu();
  void ReadNumberOfExecution();

  bool StartThirdPartMenu();

  void PrintWrongInput(const std::string& current_part_);
  void ClearCin();
  void ClearConsole();
  int ReadMenuOption(const std::string& current_part_);

  enum MenuSteps { kFirstPart = 0, kSecondPart, kThirdPart };

  enum ItemsForFirstPartMenu {
    kConsoleInput = 1,
    kLoadFromFile,
    kGenerateRandom
  };

  enum ItemsForSecondPartMenu {
    kReadNumberOfExec = 1,
    kChangeMatrix,
    kPrintCurrentMatrix
  };

  static const std::vector<std::string> menu_items_;
  static constexpr int kExit = 0;

  SystemOfLinearEquations linear_equations_;
  Timer timer_parallel_gauss_;
  Timer timer_usual_gauss_;
  int number_of_exec_;
};

#endif  // _INTERFACE_CONSOLE_INTERFACE_H_