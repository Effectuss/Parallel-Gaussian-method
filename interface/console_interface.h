#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "SLE.h"
#include "generator_SLE.h"
#include "printer_SLE.h"
#include "reader_SLE.h"
#include "timer.h"

class ConsoleInterface {
 public:
  ConsoleInterface();
  ConsoleInterface(const ConsoleInterface& other) = delete;
  ConsoleInterface(ConsoleInterface&& other) = delete;
  ConsoleInterface& operator=(const ConsoleInterface& other) = delete;
  ConsoleInterface& operator=(ConsoleInterface&& other) = delete;

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
    kPrintSLE,
    kPrintResParallel,
    kPrintResUsual,
    kCompareTime,
    kChangeSLE,
    kChangeNumberOfExec
  };

  void InitMenuFunctional();

  bool StartNeedPart(MenuSteps menu_step);
  bool SelectItemForFirstPartMenu();
  static std::string ReadFullPathToFile();
  bool SelectItemForSecondPartMenu();
  void ReadNumberOfExecution();
  bool SelectedItemForThirdPartMenu();
  void PrintExecutionTimeOfAlgorithms();

  static void ClearCin();
  static void ClearConsole();
  static int ReadMenuOption(const std::string& current_part_);
  void RunBothAlgorithmsForCompare();

  static constexpr int kExit = 0;
  static const std::vector<std::string> menu_items_;
  std::map<MenuSteps, std::function<bool(void)>> func_for_need_part;
  SLE linear_equations_;
  int execution_count = 0;
  Timer timer_parallel_gauss_;
  Timer timer_serial_gauss_;
};

#endif  // _INTERFACE_CONSOLE_INTERFACE_H_