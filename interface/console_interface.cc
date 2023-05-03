#include "console_interface.h"

const std::vector<std::string> ConsoleInterface::menu_items_ {
    "\n\u001b[42;1m              \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Enter data matrix description the SLE from the keyboard\n \
    2. Load data matrix the SLE from file\n \
    3. Generate random data matrix for SLE\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n> ",
    "\n\u001b[42;1m              \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Sets the number of algorithm executions\n \
    2. Change data matrix description the SLE\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n> " ,
    "\n\u001b[42;1m             \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Parallel algorithm for solving a SLE\n \
    2. Usual algorithm for solving a SLE\n \
    3. Compare time of execution\n \
    4. Change data matrix description the SLE\n \
    5. Change the number of algorithm executions\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n> "                              
                                    };

void ConsoleInterface::RunConsoleApp() {
    ClearConsole();
    bool exit_flag{false};
    while(!exit_flag) {
      std::cout << menu_items_[MenuSteps::kCreateSLE];
      exit_flag = SelectItemFromCreateSLEPart();
    }
}

bool ConsoleInterface::SelectItemFromCreateSLEPart() {
  int choice = ReadMenuOption(menu_items_[MenuSteps::kCreateSLE]);
  switch (choice) {
  case ItemsForCreateSLEPart::kConsoleInput:
  ClearConsole();
  try {
    this->linear_equations_.ReadAugmentedMatrixFromConsole();
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  break;
  case ItemsForCreateSLEPart::kLoadFromFile:
  break;
  case ItemsForCreateSLEPart::kGenerateRandom:
  break;
  case ItemsForCreateSLEPart::kExit:
  return true;
  break;
  default:
  break;
  }
  return false;
}

int ConsoleInterface::ReadMenuOption(const std::string &current_part_) {
  int choice{};
  bool is_valid_input{false};
  do {
    if((std::cin >> choice) && choice >= 0) {
      is_valid_input = true;
    } else {
      ClearConsole();
      std::cout << "\u001b[41;1mWRONG INPUT!\u001b[0m";
      std::cout << current_part_;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  } while (!is_valid_input);
  return choice;
}

void ConsoleInterface::ClearConsole() {
  system("clear");
}