#include "../include/Vector.hpp"
#include "../include/Error.hpp"
#include "../include/Matrix.hpp"
#include <variant>

template <typename T>
Vector<T>&	Vector<T>::operator=(const Vector<T>& vector)
{
	if (this != &vector)
		_vector = vector._vector;
	return *this;
}

template <typename T>
Vector<T>	Vector<T>::operator+(const Vector& vector) const
{
	if (getDimension() != vector.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < vector.getDimension() ; i++)
		result._vector[i] = _vector[i] + vector._vector[i];
	return result;
}

template <typename T>
Vector<T>	Vector<T>::operator-(const Vector& vector) const
{
	if (getDimension() != vector.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	Vector<T> result(getDimension());
	for (size_t i = 0 ; i < vector.getDimension() ; i++)
		result._vector[i] = _vector[i] - vector._vector[i];
	return result;
}

template <typename T>
Vector<T>	Vector<T>::operator*(const Vector& vector) const
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

template <typename Ta, typename Tb>
std::variant<Complex, float>	dotProduct(const Vector<Ta>& a, const Vector<Tb>& b)
{
	if (a.getDimension() != b.getDimension())
		throw Error("Error: vectors have to be the same dimension");
	Complex result;
	for (size_t i = 0 ; i < a.getDimension() ; i++)
	{
		Complex za(a[i]);
		Complex zb(b[i]);
		result += za * zb.getConjugate();
	}
	if constexpr (std::is_same<Ta, Complex>::value || std::is_same<Tb, Complex>::value)
		return result;
	else
		return result.getRealPart();
}

template <typename T>
bool	Vector<T>::operator==(const Vector<T>& vector) const
{
	if (vector.getDimension() != getDimension())
		return false;
	for (size_t i = 0 ; i < getDimension() ; i++)
		if (_vector[i] != vector._vector[i])
			return false;
	return true;
}

template <typename T>
bool	Vector<T>::operator!=(const Vector<T>& vector) const
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
Vector<T>&	Vector<T>::operator=(const Matrix<T>& matrix)
{
	if (matrix.getNbrColumns() != 1)
		throw Error("Error: the number of column of the matrix has to be 1");
	_vector = std::vector<T>(matrix.getNbrLines());
	for (size_t i = 0 ; i < matrix.getNbrLines() ; i++)
		_vector[i] = matrix[0][i];
	return *this;
}