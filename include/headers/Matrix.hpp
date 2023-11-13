#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream> 
#include <vector> 
#include <initializer_list> 
#include <math.h> 
#include <iomanip>
#include <random> 


namespace NumeriCore 
{
    namespace Matrix 
    {
        template<class T> 
        class Matrix
        {
        public: 

            // ////////////////////////////////////////////////////////////////////////////////////////
            // Matix class c-tors and d-tors
            // ////////////////////////////////////////////////////////////////////////////////////////  
            
            Matrix() = default; 
            Matrix(size_t _rows, size_t _cols, std::string _name = "Unkown");  
            Matrix(const std::initializer_list<std::initializer_list<T>>& _list, std::string _name = "Unkown"); 

            ~Matrix() = default;


            // //////////////////////////////////////////////////////////////////////////////////////////
            //  Matix class operator overload
            // ///////////////////////////////////////////////////////////////////////////////////////// 

            operator +(const Matrix& m1); // Matrix 1 
            operator -(const Matrix& m1); // Matrix 1
            operator *(const Matrix& m1); // Matrix 1

            Matrix<T>& operator + (const Matrix& m1, const Matrix& m2); // Matrix 1, Matrix 2 
            Matrix<T>& operator - (const Matrix& m1, const Matrix& m2); // Matrix 1, Matrix 2
            Matrix<T>& operator * (const Matrix& m1, const Matrix& m2); // Matrix 1, Matrix 2 

            operator +=(const Matrix& m1); // Matrix 1 
            operator -=(const Matrix& m1); // Matrix 1
            operator *=(const Matrix& m1); // Matrix 1

            bool operator==(const Matrix& m1, const Matrix& m2); // Matrix 1, Matrix 2
            bool operator!=(const Matrix& m1, const Matrix& m2); // Matrix 1, Matrix 2

            friend std::ostream& operator<<(std::ostream& os, const Matrix& m); // Matrix

            // //////////////////////////////////////////////////////////////////////////////////////////
            //  Matix class functions
            // //////////////////////////////////////////////////////////////////////////////////////////
            
        private: 
            std::string m_name = "Unknown"; 
            size_t m_rows; 
            size_t m_cols; 
            std::vector<std::vector<T>> m_elements; 
        }; // end class Matrix




        // ///////////////////////////////////////////////////////////////////////////////////////////
        // Matix class c-tors and d-tors
        // //////////////////////////////////////////////////////////////////////////////////////////

        /**
         * @brief Matrix constructor from initializer list
         * Initializes a matrix with the provided elements in the form of an initializer list.
         * 
         * Example usage:
         * \code
         * NumeriCore::Matrix::Matrix<int> myMatrix{
         *     { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} },
         *     "MyMatrix"
         * };
         * \endcode
         * 
         * @param _list Initializer list of initializer lists representing the matrix.
         * @param _name Name of the matrix (default is "Unknown").
         * @throw std::invalid_argument If rows have different column counts
         * @tparam T Type of matrix elements.
         */

        template<class T> 
        inline Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& _list, std::string _name)
            : m_name(_name)
        {
            this->m_rows = _list.size(); 
            this->m_cols = _list.begin() -> size();
            this->m_elements.reserve(m_rows); 

            for(const auto& row : _list) {
                if(row.size() != m_cols) {
                    throw std::invalid_argument("All rows must have the same number of columns!"); 
                    exit(1);
                } 
                 std::vector<T> tempRow(row.begin(), row.end());
                m_elements.push_back(tempRow);
            } 
        } 

    


        /**
         * @brief Matrix random initialization constructor
         * @param _rows Number of rows in the matrix.
         * @param _cols Number of columns in the matrix.
         * @param _name Name of the matrix (default is "Unknown").
         * @tparam T Type of matrix elements.
         */

        template<class T>
        inline Matrix<T>::Matrix(size_t _rows, size_t _cols, std::string _name)
            : m_name(_name)
            , m_rows(_rows)
            , m_cols(_cols)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<T> dis(-2000, 5000);

            for (auto& row : m_elements) {
                for (T element : row) {
                    element = static_cast<T>(dis(gen));
                }
            }
        }


        // //////////////////////////////////////////////////////////////////////////////////////////
        // Matix class c-tors and d-tors
        // /////////////////////////////////////////////////////////////////////////////////////////
        
        
    }; // end namespace Matrix
}; // end namespace NumeriCore

#endif