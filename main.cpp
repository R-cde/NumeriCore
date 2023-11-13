#include "./include/NumeriCore.hpp"
#include "./include/headers/Matrix.hpp"


int main(int argc, char const *argv[])
{
    NumeriCore::Matrix::Matrix<int> specificMatrix;
    // Create a matrix with 5 rows and 3 columns
    specificMatrix = NumeriCore::Matrix::Matrix<int>(5, 3);


    NumeriCore::Matrix::Matrix<int> myMatrix{
        {{1, 2, 3}, 
         {4, 5, 6}, 
         {7, 8, 9}},
        "MyMatrix"
    };

    return 0;
}
