#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../linear_equation_solver/system_of_linear_equations.h"
#include "../utils/timer.h"

class ConsoleInterface {
 public:
  ConsoleInterface();

  void Exec();

 private:
  enum MenuSteps { kFirstPart, kSecondPart, kThirdPart };

  enum ItemsForFirstPartMenu {
    kConsoleInput = 1,
    kLoadFromFile,
    kGenerateRandom
  };

  enum ItemsForSecondPartMenu {
    kReadNumberOfExec = 1,
    kChangeMatrix,
    kPrintCurrentSLE
  };

  enum ItemsForThirdPartMenu {
    kParallelAlgo = 1,
    kUsualAlgo,
    kPrintResultAndSLE,
    kCompareTime,
    kChangeSLE,
    kChangeNumberOfExec
  };

  void InitMenuFunctional();

  bool StartNeedPart(MenuSteps menu_step);
  bool SelectItemForFirstPartMenu();
  std::string ReadFullPathToFile();
  bool SelectItemForSecondPartMenu();
  void ReadNumberOfExecution();
  bool SelectedItemForThirdPartMenu();

  // void PrintWrongInput(const std::string& current_part_);
  void ClearCin();
  void ClearConsole();
  int ReadMenuOption(const std::string& current_part_);

  static constexpr int kExit = 0;
  static const std::vector<std::string> menu_items_;

  std::map<MenuSteps, std::function<bool(void)>> func_for_need_part;
  SystemOfLinearEquations linear_equations_;
  Timer timer_parallel_gauss_;
  Timer timer_usual_gauss_;
  int number_of_exec_ = 0;
};

#endif  // _INTERFACE_CONSOLE_INTERFACE_H_