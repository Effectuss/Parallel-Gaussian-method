#include "console_interface.h"

const std::vector<std::string> ConsoleInterface::menu_items_{
    "\n\u001b[42;1m              \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Enter data matrix description the SLE from the keyboard\n \
    2. Load data matrix for SLE from file\n \
    3. Generate random data matrix for SLE\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n> ",
    "\n\u001b[42;1m              \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Sets the number of algorithm executions\n \
    2. Change data matrix description the SLE\n \
    3. Print current augmented matrix\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n> ",
    "\n\u001b[42;1m             \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Parallel algorithm for solving the SLE\n \
    2. Usual algorithm for solving the SLE\n \
    3. Print current augmented matrix\n \
    4. Print result parallel algoritm\n \
    5. Print result usual algorithm\n \
    6. Compare time of execution\n \
    7. Change data matrix description the SLE\n \
    8. Change the number of algorithm executions\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n> "};

ConsoleInterface::ConsoleInterface() { InitMenuFunctional(); }

void ConsoleInterface::InitMenuFunctional() {
  this->func_for_need_part = {
      {MenuSteps::kFirstPart,
       std::bind(&ConsoleInterface::SelectItemForFirstPartMenu, this)},
      {MenuSteps::kSecondPart,
       std::bind(&ConsoleInterface::SelectItemForSecondPartMenu, this)},
      {MenuSteps::kThirdPart,
       std::bind(&ConsoleInterface::SelectedItemForThirdPartMenu, this)}};
}

bool ConsoleInterface::StartNeedPart(ConsoleInterface::MenuSteps menu_step) {
  bool exit_flag{false};
  ClearConsole();
  while (!exit_flag) {
    std::cout << menu_items_[menu_step];
    exit_flag = func_for_need_part.at(menu_step)();
  }
  return exit_flag;
}

bool ConsoleInterface::SelectItemForFirstPartMenu() {
  int choice = ReadMenuOption(menu_items_[MenuSteps::kFirstPart]);
  bool exit_flag = false;
  MenuSteps next_step = MenuSteps::kSecondPart;
  ClearConsole();
  switch (choice) {
    case ItemsForFirstPartMenu::kConsoleInput:
      linear_equations_ = std::move(ReaderSLE::ReadSLEFromConsole());
      break;
    case ItemsForFirstPartMenu::kLoadFromFile:
      try {
        std::string file_name = ReadFullPathToFile();
        linear_equations_ = std::move(ReaderSLE::ReadSLEFromFile(file_name));
      } catch (const std::logic_error& er) {
        std::cout << "\u001b[41;1m" << er.what() << "\u001b[0m";
        return false;
      }
      break;
    case ItemsForFirstPartMenu::kGenerateRandom:
      ClearConsole();
      linear_equations_ = std::move(
          GeneratorSLE::GenerateSLE(ReaderSLE::ReadSizeSLEFromConsole()));
      break;
    case kExit:
      return true;
      break;
    default:
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      return false;
      break;
  }

  if (linear_equations_.IsLinearSystemCompatible()) {
    if (execution_count > 0) next_step = MenuSteps::kThirdPart;
    exit_flag = StartNeedPart(next_step);
  } else {
    ClearConsole();
    std::cout << "\u001b[41;1mTHE SYSTEM OF LINEAR EQUATIONS ISN'T "
                 "COMPATIBLE\u001b[0m";
  }
  return exit_flag;
}

bool ConsoleInterface::SelectItemForSecondPartMenu() {
  int choice = ReadMenuOption(menu_items_[MenuSteps::kSecondPart]);
  bool exit_flag = false;
  ClearConsole();
  switch (choice) {
    case ItemsForSecondPartMenu::kReadNumberOfExec:
      ReadNumberOfExecution();
      exit_flag = StartNeedPart(MenuSteps::kThirdPart);
      break;
    case ItemsForSecondPartMenu::kChangeMatrix:
      exit_flag = StartNeedPart(MenuSteps::kFirstPart);
      break;
    case ItemsForSecondPartMenu::kPrintCurrentSLE:
      PrinterSLE::PrintSLE(linear_equations_);
      break;
    case kExit:
      return true;
    default:
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      break;
  }
  return exit_flag;
}

bool ConsoleInterface::SelectedItemForThirdPartMenu() {
  int choice = ReadMenuOption(menu_items_[MenuSteps::kThirdPart]);
  bool exit_flag = false;
  ClearConsole();
  switch (choice) {
    case ItemsForThirdPartMenu::kParallelAlgo:
      timer_parallel_gauss_.StartTimer();
      linear_equations_.SolveSLEGauss(GaussSolver::TypeOfGaussAlgo::kParallel,
                                      execution_count);
      timer_parallel_gauss_.EndTimer();
      break;
    case ItemsForThirdPartMenu::kUsualAlgo:
      timer_serial_gauss_.StartTimer();
      linear_equations_.SolveSLEGauss(GaussSolver::TypeOfGaussAlgo::kSerial,
                                      execution_count);
      timer_serial_gauss_.EndTimer();
      break;
    case ItemsForThirdPartMenu::kPrintSLE:
      PrinterSLE::PrintSLE(linear_equations_);
      break;
    case ItemsForThirdPartMenu::kPrintResParallel:
      PrinterSLE::PrintParallelResultSLE(linear_equations_);
      break;
    case ItemsForThirdPartMenu::kPrintResUsual:
      PrinterSLE::PrintSerialResultSLE(linear_equations_);
      break;
    case ItemsForThirdPartMenu::kCompareTime:
      PrintExecutionTimeOfAlgorithms();
      break;
    case ItemsForThirdPartMenu::kChangeSLE:
      exit_flag = StartNeedPart(MenuSteps::kFirstPart);
      break;
    case ItemsForThirdPartMenu::kChangeNumberOfExec:
      ReadNumberOfExecution();
      break;
    case kExit:
      exit_flag = true;
      break;
    default:
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      break;
  }
  return exit_flag;
}

void ConsoleInterface::PrintExecutionTimeOfAlgorithms() {
  std::cout << "\n\u001b[42;1mALGORITHM EXECUTION TIME\u001b[0m\n";
  std::cout << "\033[39m\033[1;29mParallel Gauss algoritm: ";
  timer_parallel_gauss_.DisplayTimerValues();
  std::cout << "\033[39m\033[1;29mUsual Gauss algoritm: ";
  timer_serial_gauss_.DisplayTimerValues();
}

int ConsoleInterface::ReadMenuOption(const std::string& current_part_) {
  int choice{};
  bool is_valid_input{false};
  do {
    std::cin >> choice;
    if (std::cin.peek() == '\n' && choice >= 0) {
      is_valid_input = true;
    } else {
      ClearConsole();
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      std::cout << current_part_;
      ClearCin();
    }
  } while (!is_valid_input);
  return choice;
}

void ConsoleInterface::ClearConsole() { system("clear"); }

std::string ConsoleInterface::ReadFullPathToFile() {
  std::string file_name;
  std::cout << "\n\u001b[42;1mENTER FULL PATH TO FILE WITH SLE: \u001b[0m\n> ";
  std::cin >> file_name;
  return file_name;
}

void ConsoleInterface::ReadNumberOfExecution() {
  bool valid_input = false;
  ClearConsole();
  do {
    std::cout << "\n\u001b[42;1mENTER NUMBER OF EXECUTIONS (1 - 100000): "
                 "\u001b[0m\n> ";
    std::cin >> execution_count;
    if (std::cin.peek() == '\n' && execution_count >= 1 &&
        execution_count <= 10000) {
      valid_input = true;
    } else {
      ClearConsole();
      ClearCin();
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
    }
  } while (!valid_input);
}

void ConsoleInterface::ClearCin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ConsoleInterface::Exec() {
  StartNeedPart(MenuSteps::kFirstPart);
  std::cout << "THE END!";
}