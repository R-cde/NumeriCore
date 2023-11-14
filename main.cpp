#include "./include/NumeriCore.hpp"
#include <iostream>

int main() {
    // Test matrix creation
    NumeriCore::Matrix::Matrix<int> matrix1{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    NumeriCore::Matrix::Matrix<int> matrix2{
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    // Test matrix addition, subtraction, and multiplication
    NumeriCore::Matrix::Matrix<int> resultAddition = matrix1 + matrix2;
    NumeriCore::Matrix::Matrix<int> resultSubtraction = matrix1 - matrix2;
    NumeriCore::Matrix::Matrix<int> resultMultiplication = matrix1 * matrix2;

    std::cout << "Matrix1 + Matrix2:\n" << resultAddition << "\n\n";
    std::cout << "Matrix1 - Matrix2:\n" << resultSubtraction << "\n\n";
    std::cout << "Matrix1 * Matrix2:\n" << resultMultiplication << "\n\n";

    // Test scalar addition, subtraction, and multiplication
    int scalar = 2;
    NumeriCore::Matrix::Matrix<int> resultScalarAddition = matrix1 + scalar;
    NumeriCore::Matrix::Matrix<int> resultScalarSubtraction = matrix1 - scalar;
    NumeriCore::Matrix::Matrix<int> resultScalarMultiplication = matrix1 * scalar;

    std::cout << "Matrix1 + Scalar:\n" << resultScalarAddition << "\n\n";
    std::cout << "Matrix1 - Scalar:\n" << resultScalarSubtraction << "\n\n";
    std::cout << "Matrix1 * Scalar:\n" << resultScalarMultiplication << "\n\n";

    // Test compound assignment with matrices and scalars
    matrix1 += matrix2;
    std::cout << "Matrix1 after += Matrix2:\n" << matrix1 << "\n\n";

    matrix1 -= matrix2;
    std::cout << "Matrix1 after -= Matrix2:\n" << matrix1 << "\n\n";

    matrix1 *= matrix2;
    std::cout << "Matrix1 after *= Matrix2:\n" << matrix1 << "\n\n";

    matrix1 += scalar;
    std::cout << "Matrix1 after += Scalar:\n" << matrix1 << "\n\n";

    matrix1 -= scalar;
    std::cout << "Matrix1 after -= Scalar:\n" << matrix1 << "\n\n";

    matrix1 *= scalar;
    std::cout << "Matrix1 after *= Scalar:\n" << matrix1 << "\n\n";

    // Test matrix equality and inequality
    if (matrix1 == matrix2) {
        std::cout << "Matrix1 is equal to Matrix2\n";
    } else {
        std::cout << "Matrix1 is not equal to Matrix2\n";
    }

    if (matrix1 != matrix2) {
        std::cout << "Matrix1 is not equal to Matrix2\n";
    } else {
        std::cout << "Matrix1 is equal to Matrix2\n";
    }

    return 0;
}
