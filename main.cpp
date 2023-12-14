#include "./include/NumeriCore.hpp"
#include <iostream>



using namespace NumeriCore::Matrix; 
using namespace NumeriCore::Vector;


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

    Matrix<double> A = {
        {2.0, 4.0, 50.5}, 
        {3.0, 5.0, 71.0}, 
        {3.0, 6.0, 10.0}
    }; 
    NumeriCore::Vector::Vector<double> b = {8.0, 14.0, 17.00};

    Matrix<double> B = {8, 8, {-500, 500}}; 
    Vector<double> c(8); 
    Vector<double> d(8); 

    std::cout << scalarProduct(c,d);

    Vector<double> x = B.solveSystem(c);
    std::cout << "Solution: " << x << std::endl;
    


    return 0;
}
