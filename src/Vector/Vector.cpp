#include "../../include/headers/Vector/Vector.hpp"
using namespace NumeriCore::Vector;



template<class U>
double scalarProduct(const Vector<U>& v1, const Vector<U>& v2) {
    if (v1.getSize() != v2.getSize()) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    double result = 0;
    for (size_t i = 0; i < v1.getSize(); ++i) {
        result += static_cast<double>(v1[i]) * static_cast<double>(v2[i]);
    }

    return result;
}