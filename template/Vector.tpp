#include "../include/Vector.hpp"
#include "../include/Error.hpp"
#include "../include/Matrix.hpp"
#include <variant>

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
	*this = matrix.getColumn(0);
}

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
void	Vector<T>::display(void) const
{
	std::cout << "[";
	size_t i = 0;
	for (const auto& data : _vector)
	{
		if (i < _vector.size() - 1)
			std::cout << data << " , ";
		else
			std::cout << data;
		i++;
	}
	std::cout << "]\n";
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

template <typename T, typename Ta, typename Tb>
T	dotProduct(const Vector<Ta>& a, const Vector<Tb>& b)
{
	if (a.getDimension() != b.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	if constexpr (std::is_same<Ta, Complex>::value || std::is_same<Tb, Complex>::value)
	{
		Complex result;
		for (size_t i = 0 ; i < a.getDimension() ; i++)
		result += Complex(a[i]) * Complex(b[i]);
		return result;
	}
	T result{};
	for (size_t i = 0 ; i < a.getDimension() ; i++)
		result += a[i] * b[i];
	return result;
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
float	Vector<T>::getNorm(void) const
{
	Vector<Complex> Cvector = *this;
	float norm = 0;
	for (size_t i = 0 ; i < getDimension() ; i++)
		norm += pow(Cvector[i].getModule(), 2);
	return sqrt(norm);
}

template <typename T>
Vector<T>	Vector<T>::getNormalised(void) const
{
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < getDimension() ; i++)
		result[i] = _vector[i] / getNorm();
	return result;
}

template <typename T>
void	Vector<T>::normalise(void)
{
	for (auto& data : _vector)
		data /= getNorm();
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