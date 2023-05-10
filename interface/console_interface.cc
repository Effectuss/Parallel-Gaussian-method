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
    \033[39m\033[1;29m1. Parallel algorithm for solving a SLE\n \
    2. Usual algorithm for solving a SLE\n \
    3. Compare time of execution\n \
    4. Change data matrix description the SLE\n \
    5. Change the number of algorithm executions\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n> "};

bool ConsoleInterface::SelectItemForFirstPartMenu() {
  int choice = ReadMenuOption(menu_items_[MenuSteps::kFirstPart]);
  bool exit_flag = false;
  ClearConsole();
  switch (choice) {
    case ItemsForFirstPartMenu::kConsoleInput:
      this->linear_equations_.ReadAugmentedMatrixFromConsole();
      break;
    case ItemsForFirstPartMenu::kLoadFromFile:
      try {
        std::string file_name = ReadFullPathToFile();
        this->linear_equations_.ReadAugmentedMatrixFromFile(file_name);
      } catch (const std::logic_error& er) {
        std::cout << "\u001b[41;1m" << er.what() << "\u001b[0m";
        return false;
      }
      break;
    case ItemsForFirstPartMenu::kGenerateRandom:
      this->linear_equations_.GenerateAugmentedMatrix();
      break;
    case kExit:
      return true;
      break;
    default:
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      return false;
      break;
  }
  exit_flag = StartNeedPart(MenuSteps::kSecondPart);
  return exit_flag;
}

bool ConsoleInterface::SelectItemForSecondPartMenu() {
  int choice = ReadMenuOption(menu_items_[MenuSteps::kSecondPart]);
  bool exit_flag = false;
  ClearConsole();
  switch (choice) {
    case ItemsForSecondPartMenu::kReadNumberOfExec:
      ReadNumberOfExecution();
      break;
    case ItemsForSecondPartMenu::kChangeMatrix:
      StartNeedPart(MenuSteps::kFirstPart);
      return true;
      break;
    case ItemsForSecondPartMenu::kPrintCurrentMatrix:
      this->linear_equations_.PrintSystemOfLinearEquations();
      return false;
      break;
    case kExit:
      return true;
    default:
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      return false;
      break;
  }
  exit_flag = StartNeedPart(MenuSteps::kThirdPart);
  return exit_flag;
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

bool ConsoleInterface::StartNeedPart(ConsoleInterface::MenuSteps menu_step) {
  bool exit_flag{false};
  ClearConsole();
  while (!exit_flag) {
    std::cout << menu_items_[menu_step];
    exit_flag = func_for_need_part.at(menu_step)();
  }
  return exit_flag;
}

bool ConsoleInterface::SelectedItemForThirdPartMenu() { return false; }

void ConsoleInterface::ReadNumberOfExecution() {
  bool valid_input = false;
  ClearConsole();
  do {
    std::cout << "\n\u001b[42;1mENTER NUMBER OF EXECUTIONS (1 - 10000): "
                 "\u001b[0m\n> ";
    std::cin >> number_of_exec_;
    if (std::cin.peek() == '\n' && number_of_exec_ >= 1 &&
        number_of_exec_ <= 10000) {
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

void ConsoleInterface::Exec() { StartNeedPart(MenuSteps::kFirstPart); }

void ConsoleInterface::InitMenuFunctional() {
  this->func_for_need_part = {
      {MenuSteps::kFirstPart,
       std::bind(&ConsoleInterface::SelectItemForFirstPartMenu, this)},
      {MenuSteps::kSecondPart,
       std::bind(&ConsoleInterface::SelectItemForSecondPartMenu, this)},
      {MenuSteps::kThirdPart,
       std::bind(&ConsoleInterface::SelectedItemForThirdPartMenu, this)}};
}

ConsoleInterface::ConsoleInterface() { InitMenuFunctional(); }
