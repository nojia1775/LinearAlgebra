#pragma once

#include <iostream>
#include "Vector.hpp"
#include "Complex.hpp"

class Error;

template <typename T>
class	Matrix
{
	typedef std::vector<std::vector<T>> vector2;

	protected:
		vector2			_matrix;
		size_t			_nbrLines;
		size_t			_nbrColumns;
	
	public:
		inline			Matrix(void) : _nbrColumns(0), _nbrLines(0) {}
		inline virtual		~Matrix(void) {}

		inline			Matrix(const size_t& nbrLines, const size_t& nbrColumns) : _matrix(vector2(nbrLines, std::vector<T>(nbrColumns, T{}))), _nbrLines(nbrLines), _nbrColumns(nbrColumns) {}
					template <typename U>
					Matrix(const std::initializer_list<std::initializer_list<U>>& list);
					Matrix(const vector2& vector);
					template <typename U>
					Matrix(const Vector<U>& vector);
					template <typename U>
					Matrix(const Matrix<U>& matrix);

					template <typename U>
		Matrix<T>&		operator=(const Matrix<U>& matrix);
					template <typename U>
		Matrix<T>&		operator=(const std::initializer_list<std::initializer_list<U>>& list);
					template <typename U>
		Matrix<T>&		operator=(const std::vector<std::vector<U>>& vector);
					template <typename U>
		Matrix<T>&		operator=(const Vector<U>& vector);
		std::vector<T>&		operator[](const size_t& index);
		const std::vector<T>&	operator[](const size_t& index) const;
					template <typename U>
		Matrix<T>		operator*(const Matrix<U>& matrix) const;
		Matrix<T>		operator*(const float& number) const;
		Matrix<T>		operator/(const float& number) const;
					template <typename U>
		Vector<U>		operator*(const Vector<U>& vector) const;
		Matrix<T>&		operator*=(const float& number);
					template <typename U>
		bool			operator==(const Matrix<U>& matrix) const;
					template <typename U>
		inline bool		operator!=(const Matrix<U>& matrix) const { return !operator==(matrix); }

		inline const size_t&	getNbrLines(void) const { return _nbrLines; }
		inline const size_t&	getNbrColumns(void) const { return _nbrColumns; }
		Vector<T>		getLine(const size_t& index) const;
		Vector<T>		getColumn(const size_t& index) const;
		T			getDeterminant(void) const;

		void			display(void) const;
		inline bool		isSquare(void) const { return _nbrLines == _nbrColumns; }
		bool			isDiagonal(void) const;
		inline bool		isInversible(void) const { return getDeterminant() == 0; }
		std::vector<Matrix<T>>	decomLU(void) const;
		void			switchLine(const size_t& l1, const size_t& l2);
		bool			isUpperTriangle(void) const;
		bool			isLowerTriangle(void) const;
};

template <typename T>
Matrix<T>	powMatrix(const Matrix<T>& matrix, const size_t& power);

#include "../template/Matrix/functions.tpp"
#include "../template/Matrix/getters.tpp"
#include "../template/Matrix/operators.tpp"
#include "../template/Matrix/constructors.tpp"