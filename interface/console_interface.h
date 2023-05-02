#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <string>
#include <iostream>
#include <vector>
#include "../gauss_solver/gauss_solver.h"
#include "../utils/timer.h"
#include "../gauss_solver/linear_system.h"

class ConsoleInterface {
    public:
    void RunConsoleApp();

    private:
    bool ChooseItemFromFirstPart();

    enum MenuSteps {kCreateSLE = 0, kNumberOfExec, kSolvingPart};

    static const std::vector<std::string> menu_items_;

    LinearSystem augmented_matrix_;
    Timer timer_parallel_gauss_;
    Timer timer_usual_gauss_;

};

#endif // _INTERFACE_CONSOLE_INTERFACE_H_