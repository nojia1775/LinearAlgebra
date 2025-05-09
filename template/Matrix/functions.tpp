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
std::vector<Matrix<T>>	Matrix<T>::decompLU(void) const
{
	if constexpr (!std::is_floating_point<T>::value && !std::is_same<T, Complex>::value)
		throw Error("Error: matrix must be a floating type");
	if (!isSquare())
		throw Error("Error: matrix has to be square");
	IdentityMatrix<T> P(getNbrColumns());
	IdentityMatrix<T> L(getNbrColumns());
	Matrix<T> U(*this);
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
			if (i > j && (_matrix[i][j] < -1e-10 || _matrix[i][j] > 1e-10))
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

template <typename T>
void	Matrix<T>::switchColumn(const size_t& c1, const size_t& c2)
{
	if (c1 > getNbrColumns() - 1)
		throw Error("Error: c1 out of range");
	if (c2 > getNbrColumns() - 1)
		throw Error("Error: c2 out of range");
	if (c1 == c2)
		return;
	std::vector<T> v1(getColumn(c1).getStdVector());
	std::vector<T> v2(getColumn(c2).getStdVector());
	for (size_t i = 0 ; i < getNbrLines() ; i++)
	{
		_matrix[i][c2] = v1[i];
		_matrix[i][c1] = v2[i];
	}
}

template <typename T>
bool	Matrix<T>::isNull(void) const
{
	for (const auto datas : _matrix)
	{
		for (const auto data : datas)
		{
			if (data > 1e-5 || data < -1e-5)
				return false;
		}
	}
	return true;
}

template <typename T>
std::vector<Matrix<Complex>>	Matrix<T>::QR(void) const
{
	if (!isSquare())
		throw Error("Error: matrix must be square");
	std::vector<Matrix<Complex>> qr(2, Matrix<Complex>(getNbrColumns(), getNbrColumns()));
	std::vector<Vector<Complex>> columns(getNbrColumns());
	for (size_t i = 0 ; i < getNbrColumns() ; i++)
		columns[i] = Vector<Complex>(getColumn(i));
	std::vector<Vector<Complex>> vectors(orthonormalize(columns));
	for (size_t i = 0 ; i < vectors.size() ; i++)
	{
		for (size_t j = 0 ; j < vectors[0].getDimension() ; j++)
			qr[0][j][i] = vectors[i][j];
	}
	qr[1] = qr[0].getTranspose() * (*this);
	return qr;
}