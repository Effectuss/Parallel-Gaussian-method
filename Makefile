all: build

build :
	g++ -g -std=c++17 main.cc ./interface/console_interface.cc ./utils/timer.cc ./SLE/system_of_linear_equations.cc ./SLE/gauss_solver.cc ./SLE/generator_SLE.cc
	./SLE/printer_SLE.cc ./SLE/reader_SLE.cc