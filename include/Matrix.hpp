#pragma once

#include <iostream>
#include "Vector.hpp"
#include "Complex.hpp"

class Error;

template <typename T>
class	Matrix
{
	typedef std::vector<std::vector<T>> vector2;

	private:
		vector2			_matrix;
		size_t			_nbrLines;
		size_t			_nbrColumns;
	
	public:
		inline			Matrix(void) : _nbrColumns(0), _nbrLines(0) {}
		inline			~Matrix(void) {}

		inline			Matrix(const size_t& nbrLines, const size_t& nbrColumns) : _matrix(vector2(nbrLines, std::vector<T>(nbrColumns, T{}))), _nbrLines(nbrLines), _nbrColumns(nbrColumns) {}
					Matrix(const std::initializer_list<std::initializer_list<T>>& list);
					Matrix(const vector2& vector);
		inline			Matrix(const Vector<T>& vector) : _nbrLines(vector.getDimension()), _nbrColumns(1), _matrix(std::vector<std::vector<T>>(1, vector.getStdVector())) {}
					template <typename U>
					Matrix(const Matrix<U>& matrix);

		Matrix<T>&		operator=(const Matrix<T>& matrix);
		Matrix<T>&		operator=(const std::initializer_list<std::initializer_list<T>>& list);
		Matrix<T>&		operator=(const std::vector<std::vector<T>>& vector);
		Matrix<T>&		operator=(const Vector<T>& vector);
		std::vector<T>&		operator[](const size_t& index);
		const std::vector<T>&	operator[](const size_t& index) const;
		Matrix<T>		operator*(const Matrix<T>& matrix) const;
		Matrix<T>		operator*(const float& number) const;
		Matrix<T>		operator/(const float& number) const;
					template <typename U>
		Vector<U>		operator*(const Vector<U>& vector) const;
		Matrix<T>&		operator*=(const float& number);

		inline const size_t&	getNbrLines(void) const { return _nbrLines; }
		inline const size_t&	getNbrColumns(void) const { return _nbrColumns; }
		const Vector<T>		getLine(const size_t& index) const;
		const Vector<T>		getColumn(const size_t& index) const;

		void			display(void) const;
};

#include "../template/Matrix.tpp"