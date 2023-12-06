#ifndef __DIAGONALMATRIX_HPP__
#define __DIAGONALMATRIX_HPP__

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include "Matrix.hpp"

namespace NumeriCore 
{
    namespace Matrix 
    {
        template <class T>
        class DiagonalMatrix : public Matrix<T> 
        {
        public:
            DiagonalMatrix() = default; 
            DiagonalMatrix(const std::initializer_list<std::initializer_list<T>> &diagonal, const std::string = "DiagonalMatrix");
            DiagonalMatrix(size_t rows, size_t cols, bool random = false, const std::string = "DiagonalMatrix"); // @param random generates by defaults 1s otherwise random numbers between [5000, - 2000]
            
            ~DiagonalMatrix() = default;

        public: 
            std::vector<T>& getDiagonal() const;
            void set_diagonal(const std::vector<T> &diagonal);
        }; 


        // ///////////////////////////////////////////////////////////////////////////////////////////
        // Diagonalmatix class c-tors and d-tors
        // //////////////////////////////////////////////////////////////////////////////////////////


        template <class T>
        DiagonalMatrix<T>::DiagonalMatrix(const std::initializer_list<std::initializer_list<T>>& diagonal, const std::string name) 
            : Matrix<T>(
                diagonal, 
                name
                )
        {   
            this->setRows(static_cast<size_t>(diagonal.begin()->size()));
            this->setCols(static_cast<size_t>(diagonal.size()));
            this->reserve(static_cast<size_t>(diagonal.begin()->size()));

            for(int i = 0; i < this->getCols(); i++) {
                for(int j = 0; j < this->getRows(); j++) {
                    if(i != j) {
                        this->setElement(i, j, static_cast<T>(0));
                    }
                }
            }
            this->saveDiagonal(); 
        }
    
        template<class T>
        DiagonalMatrix<T>::DiagonalMatrix(size_t rows, size_t cols, bool random, const std::string name)
            : Matrix<T>(rows, cols, name)
        {
            for(int i = 0; i < this->getRows(); i++) {
                for(int j = 0; j < this->getCols(); j++) {
                    if(i != j) {
                        this->setElement(i, j, static_cast<T>(0));
                    }
                    if(random == false) {
                        if(i == j) {
                            this->setElement(i, j, static_cast<T>(1));
                        }
                    }
                }  
            } 
            this->saveDiagonal(); 
        }

       
        // ///////////////////////////////////////////////////////////////////////////////////////////
        // Diagonalmatix class methodes 
        // //////////////////////////////////////////////////////////////////////////////////////////



    }
}


#endif /* __DIAGONALMATRIX_HPP__ */