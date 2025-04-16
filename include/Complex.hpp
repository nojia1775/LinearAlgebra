#pragma once

#include <iostream>
#include <cmath>

class Error;

class	Complex
{
	public:
		float			_real;
		float			_imaginary;

	public:
		inline			Complex(void) : _real(0), _imaginary(0) {}
		inline			~Complex(void) {}

		inline			Complex(const float& real, const float& imaginary) : _real(real), _imaginary(imaginary) {}
		inline			Complex(const Complex& complex) : _real(complex._real), _imaginary(complex._imaginary) {}
					template <typename T>
		inline			Complex(const T& number) : _real(static_cast<float>(number)), _imaginary(0) {}

		inline const float&	getImaginaryPart(void) const { return _imaginary; }
		inline const float&	getRealPart(void) const { return _real; }
		inline const Complex	getConjugate(void) const { return Complex(_real, -_imaginary); }
		inline float		getModule(void) const { return sqrt(pow(_real, 2) + pow(_imaginary, 2)); }
		float			getArgument(void) const;

		Complex&		operator=(const Complex& complex);
					template <typename T>
		Complex&		operator=(const T& number);
		inline Complex		operator+(const Complex& complex) const { return Complex(_real + complex._real, _imaginary + complex._imaginary); }
		inline Complex		operator+(const float& number) const { return Complex(_real + number, _imaginary); }
		inline Complex		operator-(const Complex& complex) const { return Complex(_real - complex._real, _imaginary - complex._imaginary); }
		inline Complex		operator-(const float& number) const { return Complex(_real - number, _imaginary); }
		Complex			operator/(const Complex& complex) const;
		Complex			operator/(const float& number) const;
		Complex			operator*(const Complex& complex) const;
		inline Complex		operator*(const float& number) const { return Complex(_real * number, _imaginary * number); }
		inline void		operator+=(const Complex& complex) { _real += complex._real; _imaginary += complex._imaginary; }
		inline void		operator+=(const float& number) { _real += number; }
		inline void		operator-=(const Complex& complex) { _real -= complex._real; _imaginary -= complex._imaginary; }
		inline void		operator-=(const float& number) { _real -= number; }
		void			operator*=(const Complex& complex);
		inline void		operator*=(const float& number) { _real *= number; _imaginary *= number; }
		void			operator/=(const Complex& complex);
		void			operator/=(const float& number);
		inline bool		operator==(const Complex& complex) const { return _imaginary == complex._imaginary && _real == complex._real; }
		inline bool		operator==(const float& number) const { return _real == number && _imaginary == 0; }
		inline bool		operator!=(const Complex& complex) const { return _imaginary != complex._imaginary || _real != complex._real; }
		inline bool		operator!=(const float& number) const { return _real != number && _imaginary != 0; }
		template <typename T>
		inline bool		operator>(const T& number) const { return _real > number; }
		template <typename T>
		inline bool		operator<(const T& number) const { return _real < number; }
};

std::ostream&	operator<<(std::ostream& o, const Complex& complex);

#include "../template/Complex.tpp"