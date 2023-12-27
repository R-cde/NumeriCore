#include "../../include/headers/Vector/Vector.hpp"
using namespace NumeriCore::Vector;


template<typename U>
float NumeriCore::Vector::magnitude(const Vector<U>& v1)
{
    if (v1.getSize() == 0) {
        throw std::invalid_argument("Vector can not be empty");
    }
    float result = 0;
    for (int i = 0; i < v1.getSize(); ++i) {
        result += std::pow(v1.getElement(i), 2);
    }
    return std::sqrt(result);
}


template <typename U> 
float NumeriCore::Vector::scalarProduct(const Vector<U>& v1, const Vector<U>& v2)
{
    if (v1.getSize() != v2.getSize()) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    float result = 0;
    for (size_t i = 0; i < v1.getSize(); ++i) {
        result += v1.getElement(i) * v2.getElement(i);
    }

    return result;
}


template<typename T> 
float NumeriCore::Vector::angleBetweenVector(const Vector<T>& v1, const Vector<T>& v2)
{
    if (v1.getSize() != v2.getSize()) {
        throw std::invalid_argument("Vectors must have the same size!");
    }

    float dotProduct = scalarProduct(v1, v2);
    float magnitudesProduct = v1.magnitude() * v2.magnitude();

    return (std::acos(dotProduct / magnitudesProduct)) * (180 / M_PI);
}
