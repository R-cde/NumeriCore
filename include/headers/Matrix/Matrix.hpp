#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream> 
#include <vector> 
#include <initializer_list> 
#include <math.h> 
#include <iomanip>
#include <random> 


#include "../Vector/Vector.hpp"

namespace NumeriCore 
{


    /**
     * @brief Struct representing a range with two double values.
     * @details This struct is used to define a range with two double values, 
     *          typically denoted as value_1 and value_2.
     * @note It can be utilized, for example, to represent a numeric interval 
     *       or a pair of values in a mathematical or computational context.
     */
    typedef struct {
        double value_1;
        double value_2;
    } m_range; 


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
            Matrix(size_t _rows, size_t _cols, const m_range& range = {-2000, 5000}, std::string _name = "Unkown");  
            Matrix(const std::initializer_list<std::initializer_list<T>>& _list, std::string _name = "Unkown"); 

            ~Matrix() = default;


            // //////////////////////////////////////////////////////////////////////////////////////////
            //  Matix class operator overload
            // ///////////////////////////////////////////////////////////////////////////////////////// 

            Matrix &operator +=(const Matrix&  m1); // Matrix 1 += operator
            Matrix &operator -=(const Matrix& m1); // Matrix 1 -= operator
            Matrix &operator *=(const Matrix& m1); // Matrix 1 *= operator

            template<class U> friend Matrix<U> operator +(const Matrix<U>& m1, const Matrix<U>& m2); // Matrix 1 + Matrix 2 
            template<class U> friend Matrix<U> operator -(const Matrix<U>& m1, const Matrix<U>& m2); // Matrix 1 - Matrix 2
            template<class U> friend Matrix<U> operator *(const Matrix<U>& m1, const Matrix<U>& m2); // Matrix 1 * Matrix 2 

            Matrix<T> operator +(const T& scalar); // some Number for scalar
            Matrix<T> operator -(const T& scalar); // some Number for scalar
            Matrix<T> operator *(const T& scalar); // some Number for scalar

            template<class U> friend Matrix<U> operator+(const U& scalar, const Matrix<U>& mat); // some Number for scalar + Matrix
            template<class U> friend Matrix<U> operator-(const U& scalar, const Matrix<U>& mat); // some Number for scalar - Matrix
            template<class U> friend Matrix<U> operator*(const U& scalar, const Matrix<U>& mat); // some Number for scalar * Matrix 

            Matrix<T> &operator +=(const T& scalar); // some Number for scalar 
            Matrix<T> &operator -=(const T& scalar); // some Number for scalar 
            Matrix<T> &operator *=(const T& scalar); // some Number for scalar
  

            bool operator==(const Matrix& m1); // Matrix 1
            bool operator!=(const Matrix& m1); // Matrix 1
            
            template<class U>
            friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m); // Matrix output << operator

            // //////////////////////////////////////////////////////////////////////////////////////////
            //  Matix class fgetters , setters and printerts
            // //////////////////////////////////////////////////////////////////////////////////////////

            void setRows(size_t rows); // set number of rows 
            void setCols(size_t cols); // set number of cols 

            size_t getRows() const; // get number of rows
            size_t getCols() const; // get number of cols
            
            T getElement(size_t row, size_t col) const; // get element at index row, column
            T& getElement(size_t row, size_t col); // get reference to element at index row, column

            void saveDiagonal(); // save diagonal of matrix in m_diagonal 
            void printDiagonal(); // print diagonal of matrix in m_diagonal 
            std::vector<T> getDiagonal() const; // get diagonal of matrix 



            std::vector<T>& getRow(size_t row) const; // return reference row of matrix 
            std::vector<T>* getRow(size_t row); // return pointer row of matrix 
            
            std::vector<T>& getColumn(size_t column) const; // return reference column of matrix  
            std::vector<T>* getColumn(size_t column); // return pointer column of matrix 

            std::vector<std::vector<T>>& getRows(size_t row_start, size_t row_end) const; // return reference rows rows from row_start to row_end of matrix
            std::vector<std::vector<T>>* getRows(size_t row_start, size_t row_end); // return pointer rows from row_start to row_end of matrix

            std::vector<std::vector<T>>& getColumns(size_t column_start, size_t column_end) const; // return columns from column_start to column_end of matrix
            std::vector<std::vector<T>>* getColumns(size_t column_start, size_t column_end); // return columns from column_start to column_end of matrix



            // //////////////////////////////////////////////////////////////////////////////////////////
            //  Matix class fgetters , setters and printerts
            // //////////////////////////////////////////////////////////////////////////////////////////
           
            void transpose(); // traspose matrix
            void inverse();
           



            template<typename U> void gaussianElimination(NumeriCore::Vector::Vector<U>& resultVector); 
            template<typename U> void gaussianJordanElimination(NumeriCore::Vector::Vector<T>& resultVector); 

            template<typename U> NumeriCore::Vector::Vector<U> solveSystem(NumeriCore::Vector::Vector<U>& vector);



        protected:
            void setElement(size_t row, size_t col, T element); // set element at index row, column
            void reserve(size_t value); // reserve memory for matrix

        private: 
            bool m_isSquare = (m_rows == m_cols) ? true : false;

            std::vector<T> m_diagonal;
            std::string m_name = "Unknown"; 
            
            size_t m_rows = 0; 
            size_t m_cols = 0; 
            
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

            saveDiagonal(); 
        } 

    
        /**
         * @brief Matrix random initialization constructor
         * @param _rows Number of rows in the matrix.
         * @param _cols Number of columns in the matrix.
         * @param _name Name of the matrix (default is "Unknown").
         * @tparam T Type of matrix elements.
         */

        template<class T>
        inline Matrix<T>::Matrix(size_t _rows, size_t _cols, const m_range& range, std::string _name)
            : m_name(_name)
            , m_rows(_rows)
            , m_cols(_cols)
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            T value; // some Value to test if its char type 


            if constexpr (std::is_integral<T>::value) 
            {   
                if(std::is_same<T, char>::value) // special for char type
                {
                    std::uniform_int_distribution<T> dis(33, 126);
                    m_elements.resize(m_rows, std::vector<T>(m_cols));

                    // Fill the matrix with random values
                    for (size_t i = 0; i < m_rows; ++i) {
                        for (size_t j = 0; j < m_cols; ++j) {
                            m_elements[i][j] = static_cast<T>(dis(gen));
                        }
                    }
                }
                else // for normal types, like int, long, etc 
                {
                    std::uniform_int_distribution<T> dis(range.value_1, range.value_2);
                    m_elements.resize(m_rows, std::vector<T>(m_cols));

                    // Fill the matrix with random values
                    for (size_t i = 0; i < m_rows; ++i) {
                        for (size_t j = 0; j < m_cols; ++j) {
                            m_elements[i][j] = static_cast<T>(dis(gen));
                        }
                    }
                }
            } 
            else // floating point types 
            {
                std::uniform_real_distribution<T> dis(range.value_1, range.value_2);
                m_elements.resize(m_rows, std::vector<T>(m_cols));

                // Fill the matrix with random values
                for (size_t i = 0; i < m_rows; ++i) {
                    for (size_t j = 0; j < m_cols; ++j) {
                        m_elements[i][j] = static_cast<T>(dis(gen));
                    }
                }
            }

            saveDiagonal();
        }


        // //////////////////////////////////////////////////////////////////////////////////////////
        // Matix class operators
        // /////////////////////////////////////////////////////////////////////////////////////////

        /**
        * @brief Adds another matrix to the current matrix in-place.
        * @param m1 The matrix to be added.
        * @throws std::invalid_argument if matrices have different dimensions.
        * @return Reference to the modified matrix.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline Matrix<T>& Matrix<T>::operator +=(const Matrix<T>& m1) 
        { 
            if (m_rows != m1.m_rows || m_cols != m1.m_cols) {
                    throw std::invalid_argument("Matrices must have the same dimensions.");
                }

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_elements[i][j] += m1.m_elements[i][j];
                }
            }
            return *this;
        }


        /**
        * @brief Subtracts another matrix from the current matrix in-place.
        * @param m1 The matrix to be subtracted.
        * @throws std::invalid_argument if matrices have different dimensions.
        * @return Reference to the modified matrix.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline Matrix<T>& Matrix<T>::operator -=(const Matrix<T>& m1) 
        { 
            if (m_rows != m1.m_rows || m_cols != m1.m_cols) {
                    throw std::invalid_argument("Matrices must have the same dimensions.");
                }

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_elements[i][j] -= m1.m_elements[i][j];
                }
            }
            return *this;
        }


        /**
        * @brief Multiplies the current matrix element-wise with another matrix in-place.
        * @param m1 The matrix to be multiplied.
        * @throws std::invalid_argument if matrices have different dimensions.
        * @return Reference to the modified matrix.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline Matrix<T>& Matrix<T>::operator *=(const Matrix<T>& m1) 
        { 
            if (m_rows != m1.m_rows || m_cols != m1.m_cols) {
                    throw std::invalid_argument("Matrices must have the same dimensions.");
                }

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_elements[i][j] *= m1.m_elements[i][j];
                }
            }
            return *this;
        }


        /**
        * @brief Adds two matrices and returns the result.
        * @param m1 The first matrix.
        * @param m2 The second matrix.
        * @throws std::invalid_argument if matrices have different dimensions.
        * @return Resultant matrix of the addition.
        * @tparam U Type of matrix elements.
        */

        template<class U> 
        inline Matrix<U> operator+(const Matrix<U>& m1, const Matrix<U>& m2) 
        { 
            if (m1.m_rows != m2.m_rows || m1.m_cols != m2.m_cols) {
                throw std::invalid_argument("Matrices must have the same dimensions.");
            }

            Matrix<U> result(m1.m_rows, m1.m_cols);
            for (size_t i = 0; i < m1.m_rows; ++i) {
                for (size_t j = 0; j < m1.m_cols; ++j) {
                    result.m_elements[i][j] = m1.m_elements[i][j] + m2.m_elements[i][j];
                }
            }
            return result;
        }


        /**
        * @brief Subtracts one matrix from another and returns the result.
        * @param m1 The matrix to be subtracted from.
        * @param m2 The matrix to subtract.
        * @throws std::invalid_argument if matrices have different dimensions.
        * @return Resultant matrix of the subtraction.
        * @tparam U Type of matrix elements.
        */

        template<class U> 
        inline Matrix<U> operator-(const Matrix<U>& m1, const Matrix<U>& m2) 
        { 
            if (m1.m_rows != m2.m_rows || m1.m_cols != m2.m_cols) {
                throw std::invalid_argument("Matrices must have the same dimensions.");
            }

            Matrix<U> result(m1.m_rows, m1.m_cols);
            for (size_t i = 0; i < m1.m_rows; ++i) {
                for (size_t j = 0; j < m1.m_cols; ++j) {
                    result.m_elements[i][j] = m1.m_elements[i][j] - m2.m_elements[i][j];
                }
            }
            return result;
        }   


        /**
        * @brief Multiplies two matrices element-wise and returns the result.
        * @param m1 The first matrix.
        * @param m2 The second matrix.
        * @throws std::invalid_argument if matrices have incompatible dimensions.
        * @return Resultant matrix of the multiplication.
        * @tparam U Type of matrix elements.
        */

        template<class U> 
        inline Matrix<U> operator*(const Matrix<U>& m1, const Matrix<U>& m2) 
        { 
            if (m1.m_cols != m2.m_rows) {
                throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix.");
            }

            Matrix<U> result(m1.m_rows, m2.m_cols);
            for (size_t i = 0; i < m1.m_rows; ++i) {
                for (size_t j = 0; j < m2.m_cols; ++j) {
                    result.m_elements[i][j] = 0;
                    for (size_t k = 0; k < m1.m_cols; ++k) {
                        result.m_elements[i][j] += m1.m_elements[i][k] * m2.m_elements[k][j];
                    }
                }
            }
            return result;
        }


        /**
        * @brief Adds a scalar to each element of the matrix.
        * @param scalar The scalar value to add to each element.
        * @return Resultant matrix after scalar addition.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        Matrix<T> Matrix<T>::operator+(const T& scalar) 
        {
            Matrix<T> result(m_rows, m_cols);

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_elements[i][j] = m_elements[i][j] + scalar;
                }
            }

            return result;
        }


        /**
        * @brief Subtracts a scalar from each element of the matrix.
        * @param scalar The scalar value to subtract from each element.
        * @return Resultant matrix after scalar subtraction.
        * @tparam T Type of matrix elements.
        */
        template<class T>
        inline Matrix<T> Matrix<T>::operator-(const T& scalar)
        {
            Matrix<T> result(m_rows, m_cols);

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_elements[i][j] = m_elements[i][j] - scalar;
                }
            }

            return result;
        }


        /**
        * @brief Multiplies each element of the matrix by a scalar.
        * @param scalar The scalar value to multiply each element by.
        * @return Resultant matrix after scalar multiplication.
        * @tparam T Type of matrix elements.
        */
        template<class T>
        inline Matrix<T> Matrix<T>::operator*(const T& scalar) 
        {
            Matrix<T> result(m_rows, m_cols);

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_elements[i][j] = m_elements[i][j] * scalar;
                }
            }

            return result;
        }


        /**
        * @brief Adds a scalar to each element of the matrix.
        * @param scalar The scalar value to add to each element.
        * @return Reference to the modified matrix after scalar addition.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline Matrix<T>& Matrix<T>::operator+=(const T& scalar)
        {
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_elements[i][j] += scalar;
                }
            }

            return *this;
        }


        /**
        * @brief Subtracts a scalar from each element of the matrix.
        * @param scalar The scalar value to subtract from each element.
        * @return Reference to the modified matrix after scalar subtraction.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline Matrix<T>& Matrix<T>::operator-=(const T& scalar)
        {
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_elements[i][j] -= scalar;
                }
            }

            return *this;
        }

        /**
        * @brief Multiplies each element of the matrix by a scalar.
        * @param scalar The scalar value to multiply each element by.
        * @return Reference to the modified matrix after scalar multiplication.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline Matrix<T>& Matrix<T>::operator*=(const T& scalar)
        {
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_elements[i][j] *= scalar;
                }
            }

            return *this;
        }


        /**
        * @brief Checks if two matrices are equal.
        * @param m1 The matrix to compare.
        * @return True if matrices are equal, false otherwise.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline bool Matrix<T>::operator==(const Matrix<T>& m1) 
        {
            if (m_rows != m1.m_rows || m_cols != m1.m_cols) {
                return false;
            }

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    if (m_elements[i][j] != m1.m_elements[i][j]) {
                        return false;
                    }
                }
            }

            return true;
        }


        /**
        * @brief Checks if two matrices are not equal.
        * @param m1 The matrix to compare.
        * @return True if matrices are not equal, false otherwise.
        * @tparam T Type of matrix elements.
        */

        template<class T>
        inline bool Matrix<T>::operator!=(const Matrix<T>& m1) 
        {
            return !(*this == m1);
        }



        /**
        * @brief Overloaded stream insertion operator for the Matrix class.
        * Formats and outputs the matrix elements with proper alignment and borders.
        * 
        * @param os Output stream.
        * @param matrix Matrix to be printed.
        * @tparam U Type of matrix elements.
        * @return std::ostream& Reference to the output stream.
        */

        template<class U>
        inline std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix) 
        {
            const int minSymbolWidth = 5;
            auto getMaximumNumberWidth = [&matrix]() {
                int maxNumberWidth = 0;
                for (const auto& row : matrix.m_elements) {
                    for (const auto& number : row) {
                        int numberWidth = std::to_string(number).length();
                        maxNumberWidth = std::max(maxNumberWidth, numberWidth);
                    }
                }
                return maxNumberWidth;
            };

            int maxNumberWidth = getMaximumNumberWidth();
            int count = 0;
            int symbolWidth = std::max(minSymbolWidth, maxNumberWidth + 1);
            int totalWidth = symbolWidth * matrix.m_cols + 4;

            for (const auto& row : matrix.m_elements) {
                if (count == 0) {
                    os << "┌";
                    for (size_t i = 0; i < row.size(); ++i) {
                        os << std::setw(symbolWidth) << " " << " ";
                    }
                    os << std::setw(symbolWidth) << "┐" << std::endl;
                }

                count++;

                os << "│";
                for (size_t i = 0; i < row.size(); ++i) {
                    os << std::setw(symbolWidth) << row[i] << " ";
                }
                os << std::setw(symbolWidth) << "│" << std::endl;
            }

            if (count == matrix.m_rows) {
                os << "└";
                for (size_t i = 0; i < matrix.m_elements.back().size(); ++i) {
                    os << std::setw(symbolWidth) << " " << " ";
                }
                os << std::setw(symbolWidth) << "┘" << std::endl;
            }
            return os;
        }

        template<class T> 
        void Matrix<T>::setCols(size_t cols)
        {
            this->m_cols = cols;
        }

        template<class T> 
        void Matrix<T>::setRows(size_t rows) 
        {
            this->m_rows = rows;
        }

        template<class T> 
        size_t Matrix<T>::getCols() const 
        {
            return this->m_cols;
        }
        template<class T> 
        size_t Matrix<T>::getRows() const
        {
            return this->m_rows;
        }

        template<class T> 
        void Matrix<T>::setElement(size_t row, size_t col, T element)
        {
            m_elements.at(row).at(col) = element;
        }

        template<class T> 
        T Matrix<T>::getElement(size_t row, size_t col) const
        {
            return static_cast<T>(m_elements.at(row).at(col));
        }

        template<class T> 
        T& Matrix<T>::getElement(size_t row, size_t col) 
        {
            return m_elements.at(row).at(col);
        }


        template<class T> 
        void Matrix<T>::reserve(size_t value)
        {
            m_elements.reserve(value);
        }

        template<class T> 
        void Matrix<T>::saveDiagonal() 
        {   
            for (size_t i = 0; i < this->getRows(); i++) {
                for (size_t j = 0; j < this->getCols(); j++) {
                    if (i == j) {
                        m_diagonal.push_back(m_elements.at(i).at(j));
                    }
                }
            }
        }

        template<class T>
        void Matrix<T>::printDiagonal() 
        {
            std::cout << std::endl << "{ ";
            for(auto element : m_diagonal) {
                std::cout << element << ' ';
            }
            std::cout << "}\n";
        }

        template<class T>
        std::vector<T> Matrix<T>::getDiagonal() const
        {
            return this->m_diagonal;
        }

        template<class T>
        void Matrix<T>::transpose() 
        {
            Matrix<T> newMatrix(this->getCols(), this->getRows());

            for (size_t i = 0; i < this->getRows(); ++i) {
                for (size_t j = 0; j < this->getCols(); ++j) {
                    newMatrix.setElement(j, i, this->m_elements[i][j]);
                }
            }
            (*this) = newMatrix;
        }


        template<class T>
        template<typename U>
        void NumeriCore::Matrix::Matrix<T>::gaussianElimination(NumeriCore::Vector::Vector<U>& resultVector) 
        {   
            for (size_t i = 0; i < this->getRows(); ++i) { 
                // Find the pivot element
                size_t pivotIndex = i;
                for (size_t j = i + 1; j < this->getRows() && j < resultVector.getSize() && this->getElement(j, i) != 0; ++j) {
                    if (std::abs(this->getElement(j, i)) > std::abs(this->getElement(pivotIndex, i))) {
                        pivotIndex = j;
                    }
                }

                // Swap rows based on the pivot element
                if (pivotIndex != i) {
                    for (size_t col = 0; col < this->getCols(); ++col) {
                        U tempElement = this->getElement(pivotIndex, col);
                        this->setElement(pivotIndex, col, this->getElement(i, col));
                        this->setElement(i, col, tempElement);
                    }

                    U tempValue = resultVector.getElement(pivotIndex);
                    resultVector[pivotIndex] = resultVector[i];
                    resultVector[i] = tempValue;
                }

                    // Perform forward elimination
                for (size_t k = i + 1; k < this->getRows() && k < resultVector.getSize(); ++k) {
                    if (this->getElement(k, i) == 0) {
                        break;
                    }

                    U factor = this->getElement(k, i) / this->getElement(i, i);
                    resultVector[k] -= resultVector[i] * factor;

                    for (size_t j = i; j < this->getCols(); ++j) {
                        this->setElement(k, j, this->getElement(k, j) - factor * this->getElement(i, j));
                    }

                    if (k >= resultVector.getSize()) {
                        break;
                    }
                }
            }
        }




        template<class T>
        template<typename U>
        NumeriCore::Vector::Vector<U> Matrix<T>::solveSystem(NumeriCore::Vector::Vector<U>& vector) 
        {

            this->gaussianElimination(vector);
            Vector::Vector<T> x(this->getRows());             // Calculate the solution vector

            for (int i = this->getRows() - 1; i >= 0; --i) {
                T sum = vector.getElement(i);

                for (size_t j = i + 1; j < this->getCols(); ++j) {
                    sum -= this->getElement(i, j) * x[j];
                }

                if (std::abs(this->getElement(i, i)) < 1e-6) {
                    throw std::runtime_error("Matrix is not solvable");
                }

                if (i < this->m_rows) {
                    x[i] = sum / this->getElement(i, i);
                } else {
                    throw std::out_of_range("Index out of range");
                }

            }
            return x;
        }



        template<class T>
        std::vector<T>& NumeriCore::Matrix::Matrix<T>::getRow(size_t row) const {
            if (row >= m_rows) {
                throw std::out_of_range("getRow: Row index out of range.");
            }
            return m_elements[row];
        }

        template<class T>
        std::vector<T>* NumeriCore::Matrix::Matrix<T>::getRow(size_t row) {
            if (row >= m_rows) {
                throw std::out_of_range("getRow: Row index out of range.");
            }
            return &(m_elements[row]);
        }

        template<class T>
        std::vector<T>& NumeriCore::Matrix::Matrix<T>::getColumn(size_t column) const {
            if (column >= m_cols) {
                throw std::out_of_range("getColumn: Column index out of range.");
            }

            std::vector<T>* result = new std::vector<T>();
            result->reserve(m_rows);

            for (size_t i = 0; i < m_rows; ++i) {
                result->push_back(m_elements[i][column]);
            }

            return *result;
        }

        template<class T>
        std::vector<T>* NumeriCore::Matrix::Matrix<T>::getColumn(size_t column) {
            if (column >= m_cols) {
                throw std::out_of_range("getColumn: Column index out of range.");
            }

            std::vector<T>* result = new std::vector<T>();
            result->reserve(m_rows);

            for (size_t i = 0; i < m_rows; ++i) {
                result->push_back(m_elements[i][column]);
            }

            return result;
        }

        template<class T>
        std::vector<std::vector<T>>& NumeriCore::Matrix::Matrix<T>::getRows(size_t row_start, size_t row_end) const {
            if (row_start >= m_rows || row_end >= m_rows || row_start > row_end) {
                throw std::out_of_range("getRows: Row indices out of range.");
            }

            std::vector<std::vector<T>>* result = new std::vector<std::vector<T>>();
            result->reserve(row_end - row_start + 1);

            for (size_t i = row_start; i <= row_end; ++i) {
                result->push_back(m_elements[i]);
            }

            return *result;
        }

        template<class T>
        std::vector<std::vector<T>>* NumeriCore::Matrix::Matrix<T>::getRows(size_t row_start, size_t row_end) {
            if (row_start >= m_rows || row_end >= m_rows || row_start > row_end) {
                throw std::out_of_range("getRows: Row indices out of range.");
            }

            std::vector<std::vector<T>>* result = new std::vector<std::vector<T>>();
            result->reserve(row_end - row_start + 1);

            for (size_t i = row_start; i <= row_end; ++i) {
                result->push_back(m_elements[i]);
            }

            return result;
        }

        template<class T>
        std::vector<std::vector<T>>& NumeriCore::Matrix::Matrix<T>::getColumns(size_t column_start, size_t column_end) const {
            if (column_start >= m_cols || column_end >= m_cols || column_start > column_end) {
                throw std::out_of_range("getColumns: Column indices out of range.");
            }

            std::vector<std::vector<T>>* result = new std::vector<std::vector<T>>();
            result->reserve(m_rows);

            for (size_t i = 0; i < m_rows; ++i) {
                std::vector<T> temp;
                temp.reserve(column_end - column_start + 1);
                for (size_t j = column_start; j <= column_end; ++j) {
                    temp.push_back(m_elements[i][j]);
                }
                result->push_back(temp);
            }

            return *result;
        }

        template<class T>
        std::vector<std::vector<T>>* NumeriCore::Matrix::Matrix<T>::getColumns(size_t column_start, size_t column_end) {
            if (column_start >= m_cols || column_end >= m_cols || column_start > column_end) {
                throw std::out_of_range("getColumns: Column indices out of range.");
            }

            std::vector<std::vector<T>>* result = new std::vector<std::vector<T>>();
            result->reserve(m_rows);

            for (size_t i = 0; i < m_rows; ++i) {
                std::vector<T> temp;
                temp.reserve(column_end - column_start + 1);
                for (size_t j = column_start; j <= column_end; ++j) {
                    temp.push_back(m_elements[i][j]);
                }
                result->push_back(temp);
            }

            return result;
        }



        template<class U>
        Matrix<U> operator+(const U& scalar, const Matrix<U>& mat) 
        {
            Matrix<U> result = mat;
            for (size_t i = 0; i < mat.getRows(); ++i) {
                for (size_t j = 0; j < mat.getCols(); ++j) {
                    result.setElement(i, j, mat.getElement(i, j) + scalar);
                }
            }
            return result;
        }

        template<class U>
        Matrix<U> operator-(const U& scalar, const Matrix<U>& mat) 
        {
            Matrix<U> result = mat;
            for (size_t i = 0; i < mat.getRows(); ++i) {
                for (size_t j = 0; j < mat.getCols(); ++j) {
                    result.setElement(i, j, mat.getElement(i, j) - scalar);
                }
            }
            return result;
        }

        template<class U>
        Matrix<U> operator*(const U& scalar, const Matrix<U>& mat) 
        {
            Matrix<U> result (mat.getCols(), mat.getRows());
            for (size_t i = 0; i < mat.getRows(); ++i) {
                for (size_t j = 0; j < mat.getCols(); ++j) {
                    result.setElement(i, j, mat.getElement(i, j) * scalar);
                }
            }
            return result;
        }

        


    }; // end namespace Matrix
}; // end namespace NumeriCore

#endif