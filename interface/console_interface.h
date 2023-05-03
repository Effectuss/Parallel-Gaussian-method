#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <iostream>
#include <string>
#include <vector>

#include "../linear_equation_solver/system_of_linear_equations.h"
#include "../utils/timer.h"

class ConsoleInterface {
 public:
  void RunConsoleApp();

 private:
  bool SelectItemFromCreateSLEPart();
  int ReadMenuOption(const std::string &current_part_);
  void ClearConsole();

  enum MenuSteps { kCreateSLE = 0, kNumberOfExec, kSolvingPart };
  
  enum ItemsForCreateSLEPart {
    kExit,
    kConsoleInput,
    kLoadFromFile,
    kGenerateRandom
  };

  static const std::vector<std::string> menu_items_;

  SystemOfLinearEquations linear_equations_;
  Timer timer_parallel_gauss_;
  Timer timer_usual_gauss_;
};

#endif  // _INTERFACE_CONSOLE_INTERFACE_H_