#include "../../include/Vector.hpp"
#include "../../include/Error.hpp"
#include "../../include/Matrix.hpp"
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