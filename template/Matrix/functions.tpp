#include "../../include/Matrix.hpp"
#include "../../include/Error.hpp"
#include "../../include/IdentityMatrix.hpp"

template <typename T>
void	Matrix<T>::display(void) const
{
	std::cout << "[\n";
	for (const auto& data : _matrix)
		Vector<T>(data).display();
	std::cout << "]\n";
}

template <typename T>
bool	Matrix<T>::isDiagonal(void) const
{
	if (!isSquare())
		return false;
	for (size_t i = 0 ; i < _nbrLines ; i++)
	{
		for (size_t j = 0 ; j < _nbrColumns ; j++)
		{
			if (i != j && _matrix[i][j])
				return false;
			if (i == j && _matrix[i][j] == 0)
				return false;
		}
	}
	return true;
}

template <typename T>
Matrix<T>	powMatrix(const Matrix<T>& matrix, const size_t& power)
{
	Matrix<T> result(matrix);
	if (result.isDiagonal())
	{
		for (size_t i = 0 ; i < result.getNbrColumns() ; i++)
			result[i][i] = pow(result[i][i], power);
		return result;
	}
	for (size_t i = 0 ; i < power - 1 ; i++)
		result = result * matrix;
	return result;
}

template <typename T>
static size_t	goodToSwitch(const Matrix<T>& matrix, const size_t& pos)
{
	for (size_t i = pos ; i < matrix.getNbrLines() ; i++)
		if (matrix[i][pos] != T{})
			return i;
	return pos;
}

// retourne P, L et U tel que PA = LU
template <typename T>
std::vector<Matrix<T>>	Matrix<T>::decomLU(void) const
{
	if (!isSquare())
		throw Error("Error: matrix has to be square");
	Matrix<T> L(getNbrColumns(), getNbrColumns());
	Matrix<T> U(*this);
	IdentityMatrix<T> P(getNbrColumns());
	for (size_t i = 0 ; i < getNbrColumns() ; i++)
		L[i][i] = 1;
	for (size_t i = 0 ; i < getNbrLines() ; i++)
	{
		if (U[i][i] == T{})
		{
			U.switchLine(i, goodToSwitch(*this, i));
			P.switchLine(i, goodToSwitch(*this, i));
		}
		for (size_t j = i + 1 ; j < U.getNbrLines() ; j++)
		{
			if (U[j][i] != T{})
			{
				L[j][i] = U[j][i] / U[i][i];
				for (size_t k = i ; k < U.getNbrColumns() ; k++)
					U[j][k] -= U[i][k] * L[j][i];
			}
		}
	}
	return {P, L, U};
}

template <typename T>
void	Matrix<T>::switchLine(const size_t& l1, const size_t& l2)
{
	if (l1 == l2)
		return;
	if (l1 > getNbrLines() - 1)
		throw Error("Error: l1 out of range");
	if (l2 > getNbrLines() - 1)
		throw Error("Error: l2 out of range");
	Vector<T> tmp(getLine(l1));
	_matrix[l1] = _matrix[l2];
	_matrix[l2] = tmp.getStdVector();
}

template <typename T>
bool	Matrix<T>::isUpperTriangle(void) const
{
	if (!isSquare())
		throw Error("Error: matrix has to be square");
	for (size_t i = 0 ; i < getNbrLines() ; i++)
	{
		for (size_t j = 0 ; j < getNbrColumns() ; j++)
		{
			if (i > j && _matrix[i][j] != T{})
				return false;
		}
	}
	return true;
}

template <typename T>
bool	Matrix<T>::isLowerTriangle(void) const
{
	if (!isSquare())
		throw Error("Error: matrix has to be square");
	for (size_t i = 0 ; i < getNbrLines() ; i++)
	{
		for (size_t j = 0 ; j < getNbrColumns() ; j++)
		{
			if (i < j && _matrix[i][j] != T{})
				return false;
		}
	}
	return true;
}