#ifndef _GAUSS_SOLVER_MATRIX_MANAGER_H_
#define _GAUSS_SOLVER_MATRIX_MANAGER_H_

#include <vector>
#include <thread>

class LinearSystem {
    public:

    private:
    std::vector<std::vector<double> > augmented_matrix_;
    std::vector<std::vector<double> > coefficient_matrix_;
    std::vector<double> vector_of_constants_;
};

#endif // _GAUSS_SOLVER_MATRIX_MANAGER_H_