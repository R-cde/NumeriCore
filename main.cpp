#include <iostream>
#include "./include/NumeriCore.hpp"
#include <vector>

template <typename T>
void printVector(const std::vector<std::vector<T>>* vector) {
    if (!vector) {
        std::cerr << "Error: Null pointer provided.\n";
        return;
    }

    for (const auto& row : *vector) {
        for (const auto& element : row) {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
}
 
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

    // std::cout << dmatrix3.getColumn(1);  

    printVector(dmatrix3.getColumns(0, 1)); 
    std::cout << '\n' << std::endl;
    printVector(dmatrix3.getRows(0, 1)); 


    Matrix<double> A = {
        {2.0, 4.0, 50.5}, 
        {3.0, 5.0, 71.0}, 
        {3.0, 6.0, 10.0}
    }; 
    NumeriCore::Vector::Vector<double> b = {8.0, 14.0, 17.00};

    Matrix<double> B = {8, 8, {-500, 500}}; 
    Vector<double> c(8); 
    Vector<double> d(8); 

    Vector<double> x = B.solveSystem(c);
    std::cout << "Solution: " << x << std::endl;
    

    return 0;
}



    