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


			Vector(const Vector& other);
			Vector(Vector&&) noexcept = default;             // Delete move constructor
			Vector& operator=(Vector&&) = delete;  // Delete move assignment operator

			~Vector() = default;

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

			Vector& operator= (const Vector<T>& vec); 
			Vector& operator= (const Vector<T>&& vec); 

			T& operator[](size_t index);
			const T& operator[](size_t index) const;

			bool operator==(const Vector& v);
			bool operator!=(const Vector<T>& v);

			template<typename U>
			friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

		public:
			float magnitude() const;
			float scalarProduct					(const Vector<T>& v1) const;
			float angleBetweenVector			(const Vector<T>& v1) const;
			float scalarTripleProduct			(const Vector<T>& v2,				const Vector<T>& v3) const;
			Vector<T> crossProduct				(const Vector<T>& v2) const;
			friend Vector<T> reflect			(const Vector<T>& incident,			const Vector<T>& normal);
			friend Vector<T> interpolate		(const Vector<T>& startVector,		const Vector<T>& endVector,		float t);
			friend Vector<T> vectorLerp			(const Vector<T>& startVector,		const Vector<T>& endVector,		float t);
			friend Vector<T> refract			(const Vector<T>& incident,			const Vector<T>& normal,		float eta1, float eta2);

			Vector<T>& normalize() const;

		public: 

			T& getElement(size_t index); 
			const T& getElement(size_t index) const;
			const size_t getSize() const;

			template<size_t Index>
			void setElement(const T& value); 
			void setElement(const size_t index, T&& value);
			void setElement(const size_t index, const T& value);
			void setElement(const size_t index, const T value);

		private:
			std::vector<T> m_elements;
			std::string m_name = "Unknown";
		};


		template<typename U>  float magnitude				(const Vector<U>& v1);
		template<typename U>  float scalarProduct			(const Vector<U>& v1, 			const Vector<U>& v2);
		template<typename U>  float angleBetweenVector 		(const Vector<U>& v1, 			const Vector<U>& v2); 
		template<typename U>  float scalarTripleProduct 	(const Vector<U>& v1, 			const Vector<U>& v2, 		const Vector<U>& v3); 
		template<class U>   Vector<U> crossProduct 			(const Vector<U>& v1, 			const Vector<U>& v2);
		

		template <typename T>
		inline Vector<T>::Vector(const Vector& other) 
			: m_elements(other.m_elements)
			, m_name(other.m_name) 
		{}



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


		template <typename T> 
		inline Vector<T>& Vector<T>::operator= (const Vector& vector) 
		{
			if (this != &vector)
			{
				m_elements = vector.m_elements;
				m_name = vector.m_name;
			}
			return *this;
		}

		template <typename T> 
		inline Vector<T>& Vector<T>::operator= (const Vector&& vector) 
		{
			if (this != &vector)
			{
				m_elements = vector.m_elements;
				m_name = vector.m_name;
			}
			return *this;
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

		template<typename U>
		std::ostream& operator<<(std::ostream& os, const Vector<U>& vec) {
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
		inline float Vector<T>::magnitude() const
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
		inline float Vector<T>::scalarProduct(const Vector<T>& v1) const
		{
			if (v1.getSize() != m_elements.size()) {
				throw std::invalid_argument("Vectors must have the same size");
			}

			float result = 0;
			for (size_t i = 0; i < v1.getSize(); ++i) {
				result += v1.getElement(i) * m_elements.at(i);
			}

			return result;
		}



		template<typename T> 
		float Vector<T>::angleBetweenVector(const Vector<T>& v1) const
		{
			if (this->m_elements.size() != v1.getSize()) {
				throw std::invalid_argument("Vectors must have the same size!");
			}

			float dotProduct = this->scalarProduct(v1);
			float magnitudesProduct = v1.magnitude() * this->magnitude();

			return (std::acos(dotProduct / magnitudesProduct)) * (180 / M_PI);
		}



		template <typename T>
		float Vector<T>::scalarTripleProduct(const Vector<T>& v2, const Vector<T>& v3) const
		{
			if (getSize() != v2.getSize() || getSize() != v3.getSize()) {
				throw std::invalid_argument("Vectors must have the same size!");
			}

			Vector<T> crossProductResult = v2.crossProduct(v3);
			float result = this->scalarProduct(crossProductResult);

			return result;
		}


		template <typename T>
		Vector<T> Vector<T>::crossProduct(const Vector<T>& v) const
		{
			if (getSize() != v.getSize() || getSize() != 3)
			{
				throw std::invalid_argument("Cross product is only defined for 3D vectors!");
			}

			Vector<T> result(3);
			result.template setElement<0>(static_cast<T>(getElement(1) * v.getElement(2) - getElement(2) * v.getElement(1)));
			result.template setElement<1>(static_cast<T>(getElement(2) * v.getElement(0) - getElement(0) * v.getElement(2)));
			result.template setElement<2>(static_cast<T>(getElement(0) * v.getElement(1) - getElement(1) * v.getElement(0)));

			return result;
		}


		template<typename T>
		inline Vector<T>& Vector<T>::normalize() const
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
		const size_t Vector<T>::getSize() const 
		{
			return m_elements.size();
		}


		template<typename T>
		template<size_t Index>
		void Vector<T>::setElement(const T& value) 
		{
			if (Index < m_elements.size()) {
				m_elements[Index] = value;
			}
			else {
				throw std::out_of_range("Index out of range");
			}
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
		inline void Vector<T>::setElement(const size_t index, T&& value)
		{
			if (index >= m_elements.size()) {
				throw std::out_of_range("Index out of range");
			}
			m_elements[index] = std::forward<T>(value);
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

	};
};

#endif 



