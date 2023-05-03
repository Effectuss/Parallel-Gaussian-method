all: build

build :
	g++ -g -Wall -Werror -Wextra -std=c++17 main.cc ./interface/console_interface.cc ./utils/timer.cc ./linear_equation_solver/system_of_linear_equations.cc