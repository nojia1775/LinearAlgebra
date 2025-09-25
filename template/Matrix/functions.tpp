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
bool	Matrix<T>::diagonal(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
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
	if (matrix.empty())
		throw Error("Error: matrix is empty");
	Matrix<T> result(matrix);
	if (result.diagonal())
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
	if (matrix.empty())
		throw Error("Error: matrix is empty");
	for (size_t i = pos ; i < matrix.getNbrLines() ; i++)
		if (matrix[i][pos] != T{})
			return i;
	return pos;
}

template <typename T>
void	Matrix<T>::switchLinePartial(size_t i, size_t j, size_t upto)
{
	if (empty())
		throw Error("Error: matrix is empty");
	for (size_t k = 0; k < upto; ++k)
		std::swap((*this)[i][k], (*this)[j][k]);
}


// retourne P, L et U tel que PA = LU
template <typename T>
std::vector<Matrix<T>>	Matrix<T>::decompLU(size_t& swap) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if constexpr (!std::is_floating_point<T>::value && !std::is_same<T, Complex>::value)
		throw Error("Error : matrix must be a floating type");
	if (!square())
		throw Error("Error : matrix must be square");
	IdentityMatrix<T> P(getNbrColumns());
	IdentityMatrix<T> L(getNbrColumns());
	Matrix<T> U(*this);
	for (size_t i = 0 ; i < getNbrColumns() ; i++)
		L[i][i] = 1;
	for (size_t i = 0 ; i < getNbrLines() ; i++)
	{
		if (Complex(U[i][i]).getModule() < std::numeric_limits<float>::epsilon())
		{
			swap++;
			size_t pivot = goodToSwitch(U, i);
			U.switchLine(i, pivot);
			P.switchLine(i, pivot);
			L.switchLinePartial(i, pivot, i);
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
	if (empty())
		throw Error("Error: matrix is empty");
	if (l1 == l2)
		return;
	if (l1 > getNbrLines() - 1)
		throw Error("Error : l1 out of range");
	if (l2 > getNbrLines() - 1)
		throw Error("Error : l2 out of range");
	Vector<T> tmp(getLine(l1));
	_matrix[l1] = _matrix[l2];
	_matrix[l2] = tmp.getStdVector();
}

template <typename T>
bool	Matrix<T>::upperTriangle(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error : matrix have to be square");
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
bool	Matrix<T>::lowerTriangle(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error : matrix have to be square");
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
	if (empty())
		throw Error("Error: matrix is empty");
	if (c1 > getNbrColumns() - 1)
		throw Error("Error : c1 out of range");
	if (c2 > getNbrColumns() - 1)
		throw Error("Error : c2 out of range");
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
bool	Matrix<T>::null(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	for (const auto& datas : _matrix)
	{
		for (const auto& data : datas)
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
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error : matrix must be square");
	std::vector<Matrix<Complex>> qr(2, Matrix<Complex>(getNbrColumns(), getNbrColumns()));
	std::vector<Vector<Complex>> columns(getNbrColumns());
	for (size_t i = 0 ; i < getNbrColumns() ; i++)
		columns[i] = Vector<Complex>(getColumn(i));
	std::vector<Vector<Complex>> vectors(orthonormalize(columns));
	for (size_t i = 0 ; i < vectors.size() ; i++)
	{
		for (size_t j = 0 ; j < vectors[0].dimension() ; j++)
			qr[0][j][i] = vectors[i][j];
	}
	qr[1] = qr[0].transpose() * (*this);
	return qr;
}

template <typename T>
T	Matrix<T>::trace(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error: matrix must be square");
	T result{};
	for (size_t i = 0 ; i < getNbrColumns() ; i++)
		result += _matrix[i][i];
	return result;
}

template <typename T>
static std::vector<size_t>	find_pivot(const std::vector<size_t>& begin, const Matrix<T>& matrix)
{
	if (matrix.empty())
		throw Error("Error: matrix is empty");
	for (size_t i = begin[1] ; i < matrix.getNbrColumns() ; i++)
	{
		for (size_t j = begin[0] ; j < matrix.getNbrLines() ; j++)
		{
			if (matrix[j][i] != 0)
				return {j, i};
		}
	}
	return {};
}

template <typename T>
static int	which_line(const Vector<T>& vector, const size_t& start, const size_t& end)
{
	if (vector.empty())
		throw Error("Error: matrix is empty");
	for (size_t i = start ; i < end ; i++)
		if (vector[i] == 0)
			return i;
	return end;
}

template <typename T>
Matrix<T>	Matrix<T>::row_echelon(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	Matrix<T> matrix(*this);
	std::vector<size_t> pivot = find_pivot({0, 0}, matrix);
	size_t count = 0;
	while (!pivot.empty())
	{
		if (pivot.empty())
			return matrix;
		if (pivot[0] > count)
		{
			size_t line = which_line(matrix.getColumn(pivot[1]), count, pivot[0]);
			matrix.switchLine(line, pivot[0]);
			pivot[0] = line;
		}
		T normalisation = matrix[pivot[0]][pivot[1]];
		for (size_t i = pivot[1] ; i < matrix.getNbrColumns() ; i++)
			matrix[pivot[0]][i] /= normalisation;
		for (size_t i = 0 ; i < matrix.getNbrLines() ; i++)
		{
			if (i == pivot[0])
				continue;
			T scalar = matrix[i][pivot[1]] / matrix[pivot[0]][pivot[1]];
			for (size_t j = 0 ; j < matrix.getNbrColumns() ; j++)
				matrix[i][j] -= matrix[pivot[0]][j] * scalar;
		}
		count++;
		pivot = find_pivot({pivot[0] + 1, pivot[1] + 1}, matrix);
	}
	return matrix;
}

template <typename T>
static size_t	count_rank(const Matrix<T>& rref)
{
	size_t count = 0;
	for (size_t i = 0 ; i < rref.getNbrLines() ; i++)
	{
		for (size_t j = 0 ; j < rref.getNbrColumns() ; j++)
		{
			if (rref[i][j] > std::numeric_limits<float>::epsilon())
			{
				count++;
				break;
			}
		}
	}
	return count;
}

template <typename T>
size_t	Matrix<T>::rank(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	Matrix<T> rref(row_echelon());
	return count_rank(rref);
}