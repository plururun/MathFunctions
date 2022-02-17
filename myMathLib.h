#pragma once
/*
	Lib contains few math algorithms

	definitions:
	a - bottom limit
	b - upper limit
	h - step
	foo - function with arguments;
	x - some point
*/

#define GOLDEN_RATIO	1.6180339887498948
#define PI		3.1415926535897932
#define EULER_NUMBER	2.7182818284590452

//absolute value taker
template <typename T>
inline T absolute(const T& value)
{
	if (value < (T)0)	return value * (T)(-1);
	else			return value;
}

namespace math {
namespace integral {

	template <typename T>
	inline T reimannSum(const T& a, const T& b, const T& h, T (*foo)(const T&)) //computing the inegral using a Reimann Sum
	{
		T S = (T)0;
		T x = (T)0;

		for (x = a; x < b; x += h)
			S += (*foo)(x);

		return S * h;
	}

	template <typename T>
	inline T trapezoidalRule(const T& a, const T& b, const T& h, T (*foo)(const T&)) //computing the inegral using a Trapezoidal Rule
	{
		T S = (T)0;
		T x = (T)0;

		for (x = a; x < b; x += h)
			S += (h / (T)2) * (*foo)(x) + (*foo)(x + h);

		return S;
	}

	template <typename T>
	inline T simpsonsRule(const T& a, const T& b, const T& h, T (*foo)(const T&)) //computing the inegral using a Simpson's Rule
	{
		T S = (T)0;
		T x = (T)0;

		for (x = a; x < b; x += h)
			S += (*foo)(x) + (T)4 * (*foo)(x + h / (T)2) + (*foo)(x + h);

		return (h / (T)6) * S;
	}
}

namespace derivative {

	template <typename T>
	inline T firstDerFirstPrec(const T& x, const T& h, T (*foo)(const T&))
	{
		return ((*foo)(x + h) - (*foo)(x)) / h;
	}

	template <typename T>
	inline T firstDerSymmSecondPrec(const T& x, const T& h, T (*foo)(const T&))
	{
		return ((*foo)(x + h) - (*foo)(x - h)) / ((T)2 * h);
	}

	template <typename T>
	inline T secondDerSecondPrec(const T& x, const T& h, T (*foo)(const T&))
	{
		return ((*foo)(x + h) - (T)2 * (*foo)(x) + (*foo)(x - h)) / (h * h);
	}

	template <typename T>
	inline T thirdDer(const T& x, const T& h, T (*foo)(const T&))
	{
		return ((*foo)(x + (T)2 * h) - (T)2 * (*foo)(x + h) + (T)2 * (*foo)(x - h) - (*foo)(x - (T)2 * h)) / ((T)2 * h * h * h);
	}
}

namespace optimization 
{
	template <typename T>
	inline T goldenSectionSearch(T& a, T& b, const T& eps, T (*foo)(const T&))
	{
		T x1, x2, y1, y2;

		do
		{
			x1 = b - (b - a) / (T)GOLDEN_RATIO;
			x2 = a + (b - a) / (T)GOLDEN_RATIO;
			y1 = (*foo)(x1);
			y2 = (*foo)(x2);

			if (y1 < y2)
				b = x2;
			else
				a = x1;
		} while (absolute(b - a) > eps);

		return (a + b) / (T)2;
	}
}
}
