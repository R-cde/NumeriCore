#include <iostream>
#include <vector>
#include <cstdio> 


#include "./include/NumeriCore.hpp"
#include "./src/Vector/Vector.cpp"

std::vector<std::string> filesToRemove = {
    "./main.o"
    };

 

template <typename T>
float NumeriCore::Vector::scalarTripleProduct(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3)
{
    if (v1.getSize() != v2.getSize() || v1.getSize() != v3.getSize())
    {
        throw std::invalid_argument("Vectors must have the same size!");
    }

    Vector<T> crossProductResult = crossProduct(v2, v3);
    float result = scalarProduct(v1, crossProductResult);

    return result;
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


    Matrix<double> A = {
        {2.0, 4.0, 50.5}, 
        {3.0, 5.0, 71.0}, 
        {3.0, 6.0, 10.0}
    }; 
    Matrix<double> B = {3, 3, {-500, 500}}; 


    Vector<double> b(3); 
    Vector<double> c(3); 
    Vector<double> d(3); 

    Vector<double> x = B.solveSystem(c);
    std::cout << "Solution: " << x << std::endl;
 
    std::cout << std::endl;
    std::cout << "(called from intern function) \t magnitude : " << d.magnitude() << std::endl;
    std::cout << "(called from extern function) \t magnitude : " << magnitude(d)  << std::endl; 
    std::cout << "d :" << d << std::endl;
    std::cout << "(called from intern function) \t scalar : " << d.scalarProduct(c) << std::endl;
    std::cout << "(called from extern function) \t scalar : " << scalarProduct(c, d)  << std::endl; 
    std::cout << std::endl;
    std::cout << "(called from intern function) \t angleBetweenVectors : " << d.angleBetweenVector(c) << std::endl;
    std::cout << "(called from extern function) \t angleBetweenVectors : " << angleBetweenVector(c,d)  << std::endl; 
    std::cout << std::endl;
    std::cout << "(called from intern function) \t scalarTripleProduct : " << d.scalarTripleProduct(c, b) << std::endl;
    // std::cout << "(called from extern function) \t scalarTripleProduct : " << scalarTripleProduct(c,d,b) << std::endl; 
    // std::cout << std::endl;
    // std::cout << "(called from intern function) \t crossProduct : " << d.crossProduct(c) << std::endl;
    // std::cout << "(called from extern function) \t crossProduct : " << crossProduct(c,d)  << std::endl; 


    std::remove("./main.o"); 
    return 0;
}



    