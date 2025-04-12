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

		inline				Vector(const Vector<T>& vector) : _vector(vector._vector) {}
		inline				Vector(const std::vector<T>& stdvector) : _vector(stdvector) {}
		inline				Vector(const size_t& dimension) : _vector(std::vector<T>(dimension)) {}
		inline				Vector(const std::initializer_list<T>& list) : _vector(list) {}
						Vector(const Matrix<T>& matrix);

		Vector<T>&			operator=(const Vector<T>& vector);
		inline Vector<T>&		operator=(const std::vector<T>& stdvector) { _vector = stdvector; return *this; }
		inline Vector<T>&		operator=(const std::initializer_list<T>& list) { _vector = list; return *this; }
		Vector<T>&			operator=(const Matrix<T>& matrix);
		Vector<T>			operator+(const Vector<T>& vector) const;
		Vector<T>			operator-(const Vector<T>& vector) const;
		Vector<T>			operator*(const Vector<T>& vector) const;
		Vector<T>			operator*(const float& number) const;
		T&				operator[](const size_t& index);
		const T&			operator[](const size_t& index) const;
		bool				operator==(const Vector<T>& vector) const;
		bool				operator!=(const Vector<T>& vector) const;

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