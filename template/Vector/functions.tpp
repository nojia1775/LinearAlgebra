#include "../../include/Vector.hpp"
#include "../../include/Error.hpp"
#include "../../include/Matrix.hpp"

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
void	Vector<T>::normalise(void)
{
	for (auto& data : _vector)
		data /= getNorm();
}

static inline Vector<Complex>	computeProj(const Vector<Complex>& e, const Vector<Complex>& vector) { return Vector<Complex>(e * dotProduct<Complex>(vector, e)); }

template <typename T>
std::vector<Vector<Complex>>	orthonormalize(const std::vector<Vector<T>>& vectors)
{
	for (const auto& vector : vectors)
	{
		if (vector.getDimension() != vectors[0].getDimension())
			throw Error("Error: all vectors must be the same dimension");
	}
	for (size_t i = 0 ; i < vectors.size() ; i++)
	{
		for (size_t j = 0 ; j < vectors.size() ; j++)
		{
			if (i != j)
				if (linearlyDependants(vectors[i], vectors[j]))
					throw Error("Error: some vectors are dependants");
		}
	}
	std::vector<Vector<Complex>> newVectors(vectors.size());
	std::vector<Vector<Complex>> result;
	for (size_t i = 0 ; i < vectors.size() ; i++)
		newVectors[i] = Vector<Complex>(vectors[i]);
	result.push_back(newVectors[0].getNormalised());
	for (size_t i = 1 ; i < newVectors.size() ; i++)
	{
		for (size_t j = 0 ; j < result.size() ; j++)
			newVectors[i] = newVectors[i] - computeProj(result[j], newVectors[i]);
		result.push_back(newVectors[i].getNormalised());
	}
	return result;
}

template <typename A, typename B>
bool	linearlyDependants(const Vector<A>& a, const Vector<B>& b)
{
	if (a.getDimension() != b.getDimension())
		throw Error("Error: vectors are not the same dimension");
	Complex scalar = 0;
	for (size_t i = 0 ; i < a.getDimension() ; i++)
	{
		b[i] == 0 ? scalar = 0 : scalar = Complex(a[i]) / Complex(b[i]);
		if (scalar != 0)
			break;
	}
	if (scalar == 0)
		throw Error("Error: at least one vector is null");
	for (size_t i = 0 ; i < a.getDimension() ; i++)
	{
		if (Complex(a[i]) / Complex(b[i]) != scalar)
			return false;
	}
	return true;
}