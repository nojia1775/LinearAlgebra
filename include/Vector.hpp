#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "Complex.hpp"
#include "LinearAlgebra.hpp"
#include <variant>

template <typename T>
class Matrix;

template <typename T>
class	Vector
{
	private:
		std::vector<T>			_vector;

	public:
		inline				Vector(void) : _vector(std::vector<T>()) {}
		inline				~Vector(void) {}
						template <typename U>
		inline				Vector(const Vector<U>& vector) : _vector(vector._vector) {}
						template <typename U>
		inline				Vector(const std::vector<U>& stdvector) : _vector(stdvector) {}
		inline				Vector(const size_t& dimension) : _vector(std::vector<T>(dimension)) {}
						template <typename U>
		inline				Vector(const std::initializer_list<U>& list) : _vector(list) {}
						template <typename U>
						Vector(const Matrix<U>& matrix);

						template <typename U>
		Vector<T>&			operator=(const Vector<U>& vector);
						template <typename U>
		inline Vector<T>&		operator=(const std::vector<U>& stdvector) { _vector = stdvector; return *this; }
						template <typename U>
		inline Vector<T>&		operator=(const std::initializer_list<U>& list) { _vector = list; return *this; }
						template <typename U>
		Vector<T>&			operator=(const Matrix<U>& matrix);
						template <typename U>
		Vector<T>			operator+(const Vector<U>& vector) const;
						template <typename U>
		Vector<T>			operator-(const Vector<U>& vector) const;
						template <typename U>
		Vector<T>			operator*(const Vector<U>& vector) const;
		Vector<T>			operator*(const float& number) const;
		T&				operator[](const size_t& index);
		const T&			operator[](const size_t& index) const;
						template <typename U>
		bool				operator==(const Vector<U>& vector) const;
						template <typename U>
		bool				operator!=(const Vector<U>& vector) const;

		inline size_t			getDimension(void) const { return _vector.size(); }
		float				getNorm(void) const;
		Vector<T>			getNormalised(void) const;
		inline const std::vector<T>&	getStdVector(void) const { return _vector; }

		void				display(void) const;
		void				normalise(void);
};

template <typename T, typename Ta, typename Tb>
T	dotProduct(const Vector<Ta>& a, const Vector<Tb>& b);

template <typename Ta, typename Tb>
inline bool	areOrthogonals(const Vector<Ta>& a, const Vector<Tb>& b) { return dotProduct(a, b) == Complex{}; }

#include "../template/Vector.tpp"