#include "../../include/Vector.hpp"
#include "../../include/Error.hpp"
#include "../../include/Matrix.hpp"

template <typename T>
template <typename U>
Vector<T>&	Vector<T>::operator=(const Vector<U>& vector)
{
	if (reinterpret_cast<const void *>(this) != reinterpret_cast<const void *>(&vector))
	{
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
	return *this;
}

template <typename T>
template <typename U>
Vector<T>	Vector<T>::operator+(const Vector<U>& vector) const
{
	if (getDimension() != vector.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < vector.getDimension() ; i++)
		result._vector[i] = _vector[i] + vector._vector[i];
	return result;
}

template <typename T>
template <typename U>
Vector<T>	Vector<T>::operator-(const Vector<U>& vector) const
{
	if (getDimension() != vector.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < vector.getDimension() ; i++)
		result._vector[i] = _vector[i] - vector._vector[i];
	return result;
}

template <typename T>
template <typename U>
Vector<T>	Vector<T>::operator*(const Vector<U>& vector) const
{
	if (getDimension() != vector.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < vector.getDimension() ; i++)
		result._vector[i] = _vector[i] * vector._vector[i];
	return result;
}

template <typename T>
Vector<T>	Vector<T>::operator*(const float& number) const
{
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < getDimension() ; i++)
		result._vector[i] = _vector[i] * number;
	return result;
}

template <typename T>
T&	Vector<T>::operator[](const size_t& index)
{
	if (index > _vector.size() - 1)
		throw Error("Error: index out of range");
	return _vector[index];
}

template <typename T>
const T&	Vector<T>::operator[](const size_t& index) const
{
	if (index > _vector.size() - 1)
		throw Error("Error: index out of range");
	return _vector[index];
}

template <typename T>
template <typename U>
bool	Vector<T>::operator==(const Vector<U>& vector) const
{
	if (vector.getDimension() != getDimension())
		return false;
	for (size_t i = 0 ; i < getDimension() ; i++)
		if (_vector[i] != vector._vector[i])
			return false;
	return true;
}

template <typename T>
template <typename U>
bool	Vector<T>::operator!=(const Vector<U>& vector) const
{
	if (vector.getDimension() != getDimension())
		return true;
	for (size_t i = 0 ; i < getDimension() ; i++)
		if (_vector[i] != vector._vector[i])
			return true;
	return false;
}

template <typename T>
template <typename U>
Vector<T>&	Vector<T>::operator=(const Matrix<U>& matrix)
{
	if (matrix.getNbrColumns() != 1)
		throw Error("Error: the number of column of the matrix has to be 1");
	_vector = std::vector<T>(matrix.getNbrLines());
	for (size_t i = 0 ; i < matrix.getNbrLines() ; i++)
		_vector[i] = matrix[0][i];
	return *this;
}