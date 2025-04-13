#pragma once

#include "LinearAlgebra.hpp"

class	IdentityMatrix : public Matrix<float>
{
	private:
		const size_t		_dimension;

	public:
					IdentityMatrix(const size_t& dimension);
		inline			~IdentityMatrix(void) {}

		inline			IdentityMatrix(const IdentityMatrix& identityMatrix) : Matrix<float>(identityMatrix), _dimension(identityMatrix._dimension) {}
		IdentityMatrix&		operator=(const IdentityMatrix& IdentityMatrix);

		inline const size_t&	getDimension(void) const { return _dimension; }
};