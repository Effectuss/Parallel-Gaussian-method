#ifndef _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_
#define _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_

#include <vector>
#include <thread>
#include <iostream>

class SystemOfLinearEquations {
    public:

    void ReadAugmentedMatrixFromFile();
    void ReadAugmentedMatrixFromConsole();
    void GenerateAugmentedMatrixFromConsole();

    private:
    int rows_augmented_matrix_{};
    int cols_augmented_matrix_{};
    std::vector<std::vector<double> > augmented_matrix_{};
    std::vector<std::vector<double> > coefficient_matrix_{};
    std::vector<double> vector_of_constants_{};
};

#endif // _LINEAR_EQUATION_SOLVER_SYSTEM_OF_LINEAR_EQUATIONS_H_