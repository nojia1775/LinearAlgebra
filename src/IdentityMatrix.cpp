#include "../include/IdentityMatrix.hpp"

IdentityMatrix::IdentityMatrix(const size_t& dimension) : Matrix<float>(dimension, dimension), _dimension(dimension)
{
	for (size_t i = 0 ; i < _dimension ; i++)
	{
		for (size_t j = 0 ; j < _dimension ; j++)
		{
			if (i == j)
				_matrix[i][j] = 1;
			else
				_matrix[i][j] = 0;
		}
	}
}

IdentityMatrix&	IdentityMatrix::operator=(const IdentityMatrix& identityMatrix)
{
	if (this != &identityMatrix)
	{
		if (_dimension == identityMatrix._dimension)
			throw Error("Error: identity matrix have to be the same dimension");
		_matrix = identityMatrix._matrix;
	}
	return *this;
}