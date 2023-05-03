#include "system_of_linear_equations.h"

void SystemOfLinearEquations::ReadAugmentedMatrixFromFile()
{
    
}

void SystemOfLinearEquations::ReadAugmentedMatrixFromConsole() {
    std::cout << "\n\u001b[42;1mENTER MATRIX DIMENSION: \u001b[0m\n> ";
    if (!(std::cin >> rows_augmented_matrix_ >> cols_augmented_matrix_)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    augmented_matrix_ = std::move(std::vector<std::vector<double>>(rows_augmented_matrix_, std::vector<double>(cols_augmented_matrix_)));
    for(int i = 0; i < rows_augmented_matrix_; ++i) {
        for(int j = 0; j < cols_augmented_matrix_; ++j) {
            std::cout << "Enter a value for [" << i << "][" << j << "]: ";
            if(!(std::cin >> augmented_matrix_[i][j])) {
                std::cout << "\u001b[41;1mWRONG INPUT! TRUE AGAIN!\u001b[0m\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                --j;
            }
        }
    }
}

void SystemOfLinearEquations::GenerateAugmentedMatrixFromConsole()
{
    
}
