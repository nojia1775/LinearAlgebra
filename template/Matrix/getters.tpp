#include "../../include/Matrix.hpp"
#include "../../include/Error.hpp"

template <typename T>
Vector<T>	Matrix<T>::getLine(const size_t& index) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (index > getNbrLines() - 1)
		throw Error("Error : index out of range");
	return Vector<T>(_matrix[index]);
}

template <typename T>
Vector<T>	Matrix<T>::getColumn(const size_t& index) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (index > getNbrColumns() - 1)
		throw Error("Error : index out of range");
	Vector<T> result(getNbrLines());
	for (size_t i = 0 ; i < getNbrLines() ; i++)
		result[i] = _matrix[i][index];
	return result;
}

template <typename T>
static T	determinant3(const Matrix<T>& matrix)
{
	if (matrix.empty())
		throw Error("Error: matrix is empty");
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

size_t swap = 0;

template <typename T>
T	Matrix<T>::determinant(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error : matrix must be square");
	if (lowerTriangle() || upperTriangle())
	{
		T result = pow(-1, swap);
		for (size_t i = 0 ; i < getNbrColumns() ; i++)
			result *= _matrix[i][i];
		swap = 0;
		return result;
	}
	if (getNbrColumns() == 1)
		return _matrix[0][0];
	else if (getNbrLines() == 2)
		return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
	else if (getNbrLines() == 3)
		return determinant3(*this);
	else
		return decompLU(swap)[2].determinant();
}

template <typename T>
Matrix<T>	Matrix<T>::inverse(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error: matrix is not square");
	if (inversible() == false)
		throw Error("Error : this matrix is not inversible");
	if (getNbrColumns() == 2)
	{
		Matrix<T> result(getNbrLines(), getNbrColumns());
		result[0][0] = _matrix[1][1];
		result[1][1] = _matrix[0][0];
		result[0][1] = _matrix[0][1] * -1;
		result[1][0] = _matrix[1][0] * -1;
		return result * (Complex(1) / determinant());
	}
	else
		return adjugate() * (Complex(1) / determinant());
}

template <typename T>
Matrix<T>	Matrix<T>::transpose(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	Matrix<T> result(getNbrColumns(), getNbrLines());
	for (size_t i = 0 ; i < getNbrLines() ; i++)
	{
		for (size_t j = 0 ; j < getNbrColumns() ; j++)
			result[j][i] = _matrix[i][j];
	}
	return result;
}

template <typename T>
Matrix<T>	Matrix<T>::comatrix(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (!square())
		throw Error("Error : matrix must be square");
	if (getNbrColumns() == 1)
		return *this;
	Matrix<T> com(getNbrColumns(), getNbrColumns());
	for (size_t i = 0 ; i < getNbrColumns() ; i++)
	{
		for (size_t j = 0 ; j < getNbrColumns() ; j++)
		{
			size_t x = 0;
			Matrix<T> lowMatrix(getNbrColumns() - 1, getNbrColumns() - 1);
			for (size_t k = 0 ; k < getNbrColumns() ; k++)
			{
				for (size_t l = 0 ; l < getNbrColumns() ; l++)
				{
					if (k != i && l != j)
					{
						lowMatrix[x / (getNbrColumns() - 1)][x % (getNbrColumns() - 1)] = _matrix[k][l];
						x++;
					}
				}
			}
			com[i][j] = lowMatrix.determinant() * pow(-1, i + j);
		}
	}
	return com;
}

template <typename T>
std::vector<Complex>	Matrix<T>::eigenValues(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (square() == false)
		throw Error("Error : matrix must be square");
	std::vector<Complex> eigenValues;
	if (getNbrColumns() == 2)
	{
		T a = 1;
		T b = -_matrix[0][0] - _matrix[1][1];
		T c = _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
		T delta = pow(b, 2) - 4 * a * c;
		if (delta < 0)
		{
			eigenValues.push_back(Complex(-b / 2, -sqrt(std::abs(delta)) / 2));
			eigenValues.push_back(Complex(-b / 2, sqrt(std::abs(delta)) / 2));
		}
		else if (delta == 0)
			eigenValues.push_back(-b / 2);
		else
		{
			eigenValues.push_back((-b - sqrt(delta)) / 2);
			eigenValues.push_back((-b + sqrt(delta)) / 2);
		}
		return eigenValues;
	}
	std::vector<Matrix<Complex>> qr(QR());
	Matrix<Complex> A(qr[1] * qr[0]);
	while (!A.upperTriangle())
	{
		std::cout << areOrthogonals(A.getColumn(0), A.getColumn(1)) << std::endl;
		A.display();
		qr = A.QR();
		A = qr[1] * qr[0];
	}
	for (size_t i = 0 ; i < A.getNbrColumns() ; i++)
		eigenValues.push_back(A[i][i]);
	return eigenValues;
}

template <typename T>
std::vector<Vector<Complex>>	Matrix<T>::eigenVectors(void) const
{
	if (empty())
		throw Error("Error: matrix is empty");
	if (getNbrColumns() != 2)
		throw Error("Error : eigen vectors unavailable for now");
	std::vector<Vector<Complex>> eigenVectors;
	std::vector<Complex> eigenValues = eigenValues();
	for (const auto& eigenValue : eigenValues)
	{
		Vector<Complex> eigenVector(2);
		eigenVector[0] = Complex(-_matrix[0][1]) / (Complex(_matrix[0][0]) - eigenValue);
		eigenVector[1] = 1;
		eigenVectors.push_back(eigenVector.normalised());
	}
	return eigenVectors;
}