#include <iostream>
#include "./include/NumeriCore.hpp"



int main() {
    
    DiagonalMatrix<float> dmatrix{
        {1,2,3,4}, 
        {1,2,3,4}, 
        {1,2,3,4}
    };
    NumeriCore::Matrix::Matrix<float> matrix1{
        {1, 2, 3}, 
        {4, 5, 6},
        {7, 8, 9}
    };

    DiagonalMatrix<float> someDMatrix(10, 7, true); 
    Matrix<float> someMatrix(10, 7);  


    DiagonalMatrix <float> dmatrix3 (3, 3, true); 
    std::cout << dmatrix3; 
    std::cout << dmatrix3 * 2.f ; 
    std::cout << 2.f * dmatrix3;     

    return 0;
}



    