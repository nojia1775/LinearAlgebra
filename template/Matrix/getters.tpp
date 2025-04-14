#include "../../include/Matrix.hpp"
#include "../../include/Error.hpp"

template <typename T>
Vector<T>	Matrix<T>::getLine(const size_t& index) const
{
	if (index > getNbrLines() - 1)
		throw Error("Error: index out of range");
	return Vector<T>(_matrix[index]);
}

template <typename T>
Vector<T>	Matrix<T>::getColumn(const size_t& index) const
{
	if (index > getNbrColumns() - 1)
		throw Error("Error: index out of range");
	Vector<T> result(getNbrLines());
	for (size_t i = 0 ; i < getNbrLines() ; i++)
		result[i] = _matrix[i][index];
	return result;
}

template <typename T>
static T	determinant3(const Matrix<T>& matrix)
{
	T result{};
	size_t j = 0;
	size_t k = 1;
	size_t l = 2;
	for (size_t i = 0 ; i < 3 ; i++)
		result += matrix[0][j++ % 3] * matrix[1][k++ % 3] * matrix[2][l++ % 3];
	j = 2;
	k = 1;
	l = 0;
	for (size_t i = 0 ; i < 3 ; i++)
		result -= matrix[0][j++ % 3] * matrix[1][k++ % 3] * matrix[2][l++ % 3];
	return result;
}

template <typename T>
T	Matrix<T>::getDeterminant(void) const
{
	if (!isSquare())
		throw Error("Error: matrix has to be square");
	if (isLowerTriangle() || isUpperTriangle())
	{
		T result(1);
		for (size_t i = 0 ; i < getNbrColumns() ; i++)
			result *= _matrix[i][i];
		return result;
	}
	if (getNbrLines() == 2)
		return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
	else if (getNbrLines() == 3)
		return determinant3(*this);
	else
		return decomLU()[2].getDeterminant();
}