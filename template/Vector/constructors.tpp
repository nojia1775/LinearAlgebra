#include "../../include/Vector.hpp"
#include "../../include/Error.hpp"
#include "../../include/Matrix.hpp"

template <typename T>
template <typename U>
Vector<T>::Vector(const Vector<U>& vector)
{
	_vector = std::vector<T>(vector.getDimension());
	for (size_t i = 0 ; i < vector.getDimension() ; i++)
	{
		if constexpr (std::is_same<U, Complex>::value)
		{
			if constexpr (std::is_same<T, Complex>::value)
				_vector[i] = vector[i];
			else
				_vector[i] = static_cast<float>(vector[i].getRealPart());
		}
		else
			_vector[i] = static_cast<float>(vector[i]);
	}
}

template <typename T>
template <typename U>
Vector<T>::Vector(const Matrix<U>& matrix)
{
	if (matrix.getNbrColumns() != 1)
		throw Error("Error: matrix has to have 1 column");
	_vector = std::vector<T>(matrix.getNbrLines());
	*this = matrix.getColumn(0);
}