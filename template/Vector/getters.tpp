#include "../../include/Vector.hpp"
#include "../../include/Error.hpp"
#include "../../include/Matrix.hpp"
template <typename T>
float	Vector<T>::norm(void) const
{
	if (empty())
		throw Error("Error: vector is empty");
	Vector<Complex> Cvector = *this;
	float norm = 0;
	for (size_t i = 0 ; i < dimension() ; i++)
		norm += pow(Cvector[i].getModule(), 2);
	return sqrt(norm);
}

template <typename T>
Vector<T>	Vector<T>::normalised(void) const
{
	if (empty())
		throw Error("Error: vector is empty");
	Vector<T> result(dimension());
	for (size_t i = 0 ; i < dimension() ; i++)
		result[i] = _vector[i] / norm();
	return result;
}