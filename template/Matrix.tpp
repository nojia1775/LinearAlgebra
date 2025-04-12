#include "../include/Matrix.hpp"
#include "../include/Error.hpp"

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& list)
{
	for (const auto data : list)
		if (data.size() != list.begin()->size())
			throw Error("Error: initializers have to be the same size");
	_nbrLines = list.size();
	_nbrColumns = list.begin()->size();
	_matrix = std::vector<std::vector<T>>(_nbrLines, std::vector<T>(_nbrColumns));
	_matrix.clear();
	for (const auto data : list)
		_matrix.emplace_back(data);
}

template <typename T>
Matrix<T>::Matrix(const vector2& vector)
{
	for (const auto data : vector)
		if (data.size() != vector[0].size())
			throw Error("Error: vectors have to be the same dimension");
	_nbrLines = vector.size();
	_nbrColumns = vector[0].size();
	_matrix = std::vector<std::vector<T>>(_nbrLines, std::vector<T>(_nbrColumns));
	_matrix.clear();
	for (size_t i = 0 ; i < _nbrLines ; i++)
		_matrix.emplace_back(vector[i]);
}

template <typename T>
Matrix<T>&	Matrix<T>::operator=(const Matrix<T>& matrix)
{
	if (this != &matrix)
	{
		_nbrLines = matrix._nbrLines;
		_nbrColumns = matrix._nbrColumns;
		_matrix = matrix._matrix;
	}
	return *this;
}

template <typename T>
Matrix<T>&	Matrix<T>::operator=(const std::initializer_list<std::initializer_list<T>>& list)
{
	for (const auto data : list)
		if (data.size() != list[0].size())
			throw Error("Error: initializers have to be the same size");
	_nbrLines = list.size();
	_nbrColumns = list[0].size();
	_matrix.clear();
	for (size_t i = 0 ; i < _nbrLines ; i++)
		_matrix.emplace_back(list[i]);
	return *this;
}

template <typename T>
Matrix<T>&	Matrix<T>::operator=(const std::vector<std::vector<T>>& vector)
{
	for (const auto data : vector)
		if (data.size() != vector[0].size())
			throw Error("Error: vectors have to be the same dimension");
	_nbrLines = vector.size();
	_nbrColumns = vector[0].size();
	_matrix = std::vector<std::vector<T>>(_nbrLines, std::vector<T>(_nbrColumns));
	_matrix.clear();
	for (size_t i = 0 ; i < _nbrLines ; i++)
		_matrix.emplace_back(vector[i]);
	return *this;
}

template <typename T>
Matrix<T>&	Matrix<T>::operator=(const Vector<T>& vector)
{
	_nbrLines = vector.getDimension();
	_nbrColumns = 1;
	_matrix = std::vector<std::vector<T>>(_nbrLines, std::vector<T>(_nbrColumns));
	_matrix.clear();
	for (size_t i = 0 ; i < _nbrLines ; i++)
		_matrix.emplace_back(vector[i]);
}

template <typename T>
std::vector<T>&	Matrix<T>::operator[](const size_t& index)
{
	if (index > _nbrLines - 1)
		throw Error("Error: index out of range");
	return _matrix[index];
}

template <typename T>
const std::vector<T>&	Matrix<T>::operator[](const size_t& index) const
{
	if (index > _nbrLines - 1)
		throw Error("Error: index out of range");
	return _matrix[index];
}

template <typename T>
void	Matrix<T>::display(void) const
{
	std::cout << "[\n";
	for (const auto data : _matrix)
		Vector(data).display();
	std::cout << "]\n";
}

template <typename T>
const Vector<T>	Matrix<T>::getLine(const size_t& index) const
{
	if (index > getNbrLines() - 1)
		throw Error("Error: index out of range");
	return Vector(_matrix[index]);
}

template <typename T>
const Vector<T>	Matrix<T>::getColumn(const size_t& index) const
{
	if (index > getNbrColumns() - 1)
		throw Error("Error: index out of range");
	Vector<T> result(getNbrLines());
	for (size_t i = 0 ; i < getNbrLines() ; i++)
		result[i] = _matrix[i][index];
	return result;
}

template <typename T>
Matrix<T>	Matrix<T>::operator*(const Matrix<T>& matrix) const
{
	Matrix<T> result(_nbrLines, matrix._nbrColumns);
	for (size_t i = 0 ; i < result._nbrLines ; i++)
	{
		for (size_t j = 0 ; j < result._nbrColumns ; j++)
			result[i][j] = dotProduct(Vector<T>(getLine(i)), Vector<T>(matrix.getColumn(j)));
	}
	return result;
}