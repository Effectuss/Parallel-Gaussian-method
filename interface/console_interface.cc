#include "console_interface.h"

const std::vector<std::string> ConsoleInterface::menu_items_ {
    "\n\u001b[42;1m              \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Enter data matrix description the SLE from the keyboard\n \
    2. Load data matrix the SLE from file\n \
    3. Generate random data matrix for SLE\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n",
    "\n\u001b[42;1m              \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Sets the number of algorithm executions\n \
    2. Change data matrix description the SLE\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n" ,
    "\n\u001b[42;1m             \
    CHOOSE AN OPTION:                     \u001b[0m\n \
    \033[39m\033[1;29m1. Parallel algorithm for solving a SLE\n \
    2. Usual algorithm for solving a SLE\n \
    3. Compare time of execution\n \
    4. Change data matrix description the SLE\n \
    5. Change the number of algorithm executions\n \
    0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n"                              
                                    };