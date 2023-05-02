#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <string>
#include <iostream>
#include <vector>
#include "../gauss_solver/gauss_solver.h"

class ConsoleInterface {
    public:
    using Matrix = std::vector<std::vector<double>>;
    ConsoleInterface(){
        int item;
        std::cout << menu_items_[0];
        std::cin >> item;
        system("clear");
        std::cout << menu_items_[1];
        std::cin >> item;
        system("clear");
        std::cout << menu_items_[2];
    }
    private:

    enum MenuSteps {kInitMatrix, kNumberOfExec, kSolvingPart};

    static const std::vector<std::string> menu_items_;

    Matrix augmented_matrix_;
    
};

#endif // _INTERFACE_CONSOLE_INTERFACE_H_