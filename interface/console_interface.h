#ifndef _INTERFACE_CONSOLE_INTERFACE_H_
#define _INTERFACE_CONSOLE_INTERFACE_H_

#include <string>
#include <iostream>

class ConsoleInterface{
    public:
    ConsoleInterface() {
        std::cout << main_menu_;
    }
    private:
    static const std::string main_menu_;
};
#endif // _INTERFACE_CONSOLE_INTERFACE_H_