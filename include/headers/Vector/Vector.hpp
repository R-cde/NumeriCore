#ifndef __VECTOR_HPP__
#define	__VECTOR_HPP__

#include <iostream>
#include <initializer_list>
#include <math.h>
#include <vector>

namespace NumeriCore
{
	namespace Vector
	{
		template <typename T>
		class Vector
		{
		public:
			Vector() = default;
			Vector(const size_t length, const std::string name = "Unknown");
			Vector(std::initializer_list<T> values, const std::string name = "Unknown");
			Vector(std::initializer_list<T>& values, const std::string name = "Unknown");

		public:

			Vector	operator+	(const Vector& v) const;
			Vector& operator+=	(const Vector& v);
			Vector	operator+	(const T a);
			Vector& operator+=	(const T a) const;

			Vector	operator-	(const Vector& v) const;
			Vector& operator-=	(const Vector& v);
			Vector	operator-	(const T a);
			Vector& operator-=	(const T a) const;

			Vector	operator*	(const Vector& v) const;
			Vector& operator*=	(const Vector& v);
			Vector	operator*	(const T a);
			Vector& operator*=	(const T a) const;

			Vector	operator/	(const Vector& v) const;
			Vector& operator/=	(const Vector& v);
			Vector	operator/	(const T a);
			Vector& operator/=	(const T a) const;

			T& operator[](size_t index);
			const T& operator[](size_t index) const;

			bool operator==(const Vector& v);
			bool operator!=(const Vector<T>& v);

			friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

		public:
			float magnitude();
			friend float scalarProduct			(const Vector<T>& v1,				const Vector<T>& v2);
			friend float angeleBetweenVector	(const Vector<T>& v1,				const Vector<T>& v2);
			friend float scalarTripleProduct	(const Vector<T>& v1,				const Vector<T>& v2,			const Vector<T>& v3);
			friend Vector<T> crossProduct		(const Vector<T>& v1,				const Vector<T>& v2);
			friend Vector<T> reflect			(const Vector<T>& incident,			const Vector<T>& normal);
			friend Vector<T> interpolate		(const Vector<T>& startVector,		const Vector<T>& endVector,		float t);
			friend Vector<T> vectorLerp			(const Vector<T>& startVector,		const Vector<T>& endVector,		float t);
			friend Vector<T> refract			(const Vector<T>& incident,			const Vector<T>& normal,		float eta1, float eta2);

			Vector<T>& normalize();

		public: 

			T& getElement(size_t index); 
			const T& getElement(size_t index) const;
			const size_t getSize() const;

			void setElement(const size_t index, const T& value);
			void setElement(const size_t index, const T value);

		private:
			std::vector<T> m_elements;
			std::string m_name = "Unknown";
		};


		template<typename T>
		inline Vector<T>::Vector(const size_t length, const std::string name) 
			: m_name(name)
		{
			for(int i = 0; i < length; ++i) {
				m_elements.push_back(i);
			}

		}

		template<typename T>
		inline Vector<T>::Vector(std::initializer_list<T> values, const std::string name)
			: m_elements(values)
			, m_name(name)
		{}


		template<typename T>
		inline Vector<T>::Vector(std::initializer_list<T>& values, const std::string name)
			: m_elements(values)
			, m_name(name)
		{}

		template<typename T>
		inline Vector<T> Vector<T>::operator+(const Vector& v) const
		{	
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}
			Vector result(*this);
			result += v;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator+=(const Vector& v)
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}

			for (size_t i = 0; i < m_elements.size(); i++) {
				m_elements[i] += v.m_elements[i];
			}
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator+(const T a)
		{
			Vector<T> result(*this);
			result += a;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator+=(const T a) const
		{
			for (size_t i = 0; i < m_elements.size(); i++) {
				m_elements[i] += a;
			}
			return *this;
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator-(const Vector& v) const
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}
			Vector result(*this);
			result -= v;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator-=(const Vector& v)
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}
			for (size_t i = 0; i < m_elements.size(); i++) {
				m_elements[i] -= v.m_elements[i];
			}
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator-(const T a)
		{
			Vector result(*this);
			result -= a;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator-=(const T a) const
		{
			for (size_t i = 0; i < m_elements.size(); i++) {
				m_elements[i] -= a;
			}
			return *this;
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator*(const Vector& v) const
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}
			Vector result(*this);
			result *= v;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator*=(const Vector& v)
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}
			for (size_t i = 0; i < m_elements.size(); i++) {
				m_elements[i] *= v.m_elements[i];
			}
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator*(const T a)
		{
			for (size_t i = 0; i < m_elements.size(); i++) {
				m_elements[i] *= a;
			}
			return *this;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator*=(const T a) const
		{
			Vector<T> result(*this);
			for (size_t i = 0; i < this->m_elements.size(); i++) {
				result.m_elements[i] *= a;
			}
			return result;
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator/(const Vector& v) const
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}
			Vector result(*this);
			result /= v;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator/=(const Vector& v)
		{
			if (m_elements.size() != v.m_elements.size()) {
				throw std::runtime_error("Vectors must have the same size");
			}

			for (size_t i = 0; i < m_elements.size(); i++) {
				if (v.m_elements[i] == 0) {
					throw std::runtime_error("Divisor can't be zero");
				}
				m_elements[i] /= v.m_elements[i];
			}
		}

		template<typename T>
		inline Vector<T> Vector<T>::operator/(const T a)
		{
			Vector result(*this);
			result /= a;
			return result;
		}

		template<typename T>
		inline Vector<T>& Vector<T>::operator/=(const T a) const
		{
			for (size_t i = 0; i < m_elements.size(); i++) {
				if (a == 0) {
					throw std::runtime_error("Divisor can't be zero");
				}
				m_elements[i] /= a;
			}
		}

		template<typename T>
		inline T& Vector<T>::operator[](const size_t pos)
		{
			if (pos < m_elements.size()) {
				return m_elements[pos];
			} else {
				throw std::out_of_range("Index out of range");
			}
		}

		template<typename T>
		inline const T& Vector<T>::operator[](size_t pos) const 
		{
			if (pos < m_elements.size()) {
				return m_elements[pos];
			} else {
				throw std::out_of_range("Index out of range");
			}
		}

		template<typename T>
		inline bool Vector<T>::operator==(const Vector& v)
		{
			if (v.m_elements.size() != this->m_elements.size()) {
				throw std::invalid_argument("Vector comparison failed! Vectors do not have the same size!");
				return false;
			}
			for (size_t i = 0; i < v.m_elements.size(); ++i) {
				if (v.m_elements.at(i) != this->m_elements.at(i)) {
					return false;
				}
			}
			return true;
		}

		template<typename T>
		inline bool Vector<T>::operator!=(const Vector<T>& v)
		{
			if (v.m_elements.size() != m_elements.size()) {
				throw std::invalid_argument("Vector comparison failed! Vectors do not have the same size!");
				return true;
			}
			for (size_t i = 0; i < v.m_elements.size(); ++i) {
				if (v.m_elements.at(i) != m_elements.at(i)) {
					return true;
				}
			}
			return false;
		}

		template<typename T>
		std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
			os << "[ ";
			for (size_t i = 0; i < vec.getSize(); ++i) {
				os << vec[i];
				if (i < vec.getSize() - 1) {
					os << "  ";  // Add space for better readability
				}
			}
			os << " ]";
			return os;
		}


		template<typename T>
		inline float Vector<T>::magnitude()
		{
			if (m_elements.size() == 0) {
				throw std::invalid_argument("Vector can not be empty");
			}
			float result = 0;
			for (const auto& element : m_elements) {
				result += std::pow(element, 2);
			}
			return std::sqrt(result);
		}


		template<typename T>
		inline Vector<T>& Vector<T>::normalize()
		{
			float mag = this->magnitude();
			if (mag == 0) {
				throw std::invalid_argument("Cannot normalize a zero vector");
			}
			for (auto& element : m_elements) {
				element /= mag;
			}
			return *this;
		}


		template<typename T>
		float scalarProduct(const Vector<T>& v1, const Vector<T>& v2) {
			if (v1.getSize() != v2.getSize()) {
				throw std::invalid_argument("Vectors must have the same size");
			}

			float result = 0;
			for (size_t i = 0; i < v1.getSize(); ++i) {
				result += v1.getElement(i) * v2.getElement(i);
			}

			return result;
		}



		template<class T>
		T& Vector<T>::getElement(size_t index)
		{
			if (index < m_elements.size()) {
				return m_elements[index];
			} else {
				throw std::out_of_range("Index out of range | T&");
			}
		}


		template<class T>
		const T& Vector<T>::getElement(size_t index) const 
		{
			if (index < m_elements.size()) {
				return m_elements[index];
			} else {
				throw std::out_of_range("Index out of range | const T&");
			}
		}


		template<class T>
		const size_t Vector<T>::getSize() const {
			return m_elements.size();
		}



		
		template<typename T>
		inline void Vector<T>::setElement(const size_t index, const T& value)
		{
			if (index >= m_elements.size()) {
				throw std::out_of_range("Index out of range");
			}
			m_elements[index] = value;
		}


		template<typename T>
		inline void Vector<T>::setElement(const size_t index, const T value)
		{
			if (index < m_elements.size()) {
				m_elements[index] = value;
			} else {
				throw std::out_of_range("Index out of range");
			}
		}


		template<typename T> 
		float angeleBetweenVector(const Vector<T>& v1, const Vector<T>& v2)
		{
			if (v1.m_elements.size() != v2.m_elements.size()) {
				throw std::invalid_argument("Vectors must have the same size!");
			}

			float dotProduct = scalarProduct(v1, v2);
			float magnitudesProduct = v1.magnitude() * v2.magnitude();

			return (std::acos(dotProduct / magnitudesProduct)) * (180 / M_PI);
		}
	};
};

#endif 



