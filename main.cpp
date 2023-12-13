#include "./include/NumeriCore.hpp"
#include <iostream>



using namespace NumeriCore::Matrix; 

int main() {
    // Test matrix creation
    Matrix<float> matrix1{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    Matrix<float> matrix2{
        {9, 8, 7},
        {6, 5, 4},
        {6, 5, 4}
    };



    Matrix<int> matrix3 {5, 4, {0, 100}}; 

    matrix3.gaussElimination();
    std::cout << matrix3; 

    return 0;
}
