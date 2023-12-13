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
            DiagonalMatrix(const std::initializer_list<std::initializer_list<T>> &elements, const std::string = "DiagonalMatrix");
            DiagonalMatrix(const std::vector<T>& diagonalElements, const std::string = "DiagonalMatrix"); // generates a n x n Matrix with the diagonal elements at i = j 
            DiagonalMatrix(size_t rows, size_t cols, bool random = false, const std::string = "DiagonalMatrix"); 
            
            
            ~DiagonalMatrix() = default;

        public: 
            std::vector<T>& getDiagonal() const;
            void set_diagonal(const std::vector<T> &diagonal);
        }; 


        // ///////////////////////////////////////////////////////////////////////////////////////////
        // Diagonalmatix class c-tors and d-tors
        // //////////////////////////////////////////////////////////////////////////////////////////


        template <class T>
        DiagonalMatrix<T>::DiagonalMatrix(const std::initializer_list<std::initializer_list<T>>& elements, const std::string name) 
            : Matrix<T>(
                elements, 
                name
                )
        {   
            this->setRows(static_cast<size_t>(elements.begin()->size()));
            this->setCols(static_cast<size_t>(elements.size()));
            this->reserve(static_cast<size_t>(elements.begin()->size()));

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
        DiagonalMatrix<T>::DiagonalMatrix(const std::vector<T>& diagonalElements, const std::string name) // add std::vector<T>{diagonalElements} when calling the ctor
            : Matrix<T>(
                diagonalElements.size(), 
                diagonalElements.size(), 
                {0, 0}, 
                name
                ) 
        {
            this->setRows(diagonalElements.size());
            this->setCols(diagonalElements.size());
            this->reserve(diagonalElements.size());

            for(int i = 0; i < this->getCols(); i++) {
                this->setElement(i, i, static_cast<T>(diagonalElements.at(i)));

            }
            this->saveDiagonal(); 
        }



        template<class T>
        DiagonalMatrix<T>::DiagonalMatrix(size_t rows, size_t cols, bool random, const std::string name)
            : Matrix<T>(rows, cols)
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