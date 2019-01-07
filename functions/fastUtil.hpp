#ifndef FASTUTIL_HPP_INCLUDED
#define FASTUTIL_HPP_INCLUDED

#include <optional>
#include <climits>
#include <type_traits>

template <typename T> std::optional<T> safeNeg(T x)
{
	constexpr T min = (T)1 << ((sizeof(T) * CHAR_BIT) - 1);
	
	if (x == min)
		return {};
	
	return -x;
}

template <typename T> std::optional<T> safeAbs(T x)
{
	constexpr T n = sizeof(T) * CHAR_BIT;
	
	if (x == ((T)1 << (n - 1)))
		return {};
	
	const T t = x >> (n - 1);
	
	return (x ^ t) - t;
}

template <typename T> T iPow(T x, int exp)
{
	const bool isNegative = exp < 0;
	T r = 1;
	
	while (1)
	{
		if (exp & 1)
			r *= x;
		exp /= 2;
		if (!exp)
			break;
		x *= x;
	}
	
	return isNegative ? 1 / r : r;
}

template <typename T> std::optional<T> safeSub(T a, T b)
{
	static_assert(std::is_signed<T>(), "type must be signed (for now)");
	typedef typename std::make_unsigned<T>::type uT;
	T s = (uT)a - (uT)b;
	
	if (b >= 0)
	{
		if (s > a)
			return {};
	}
	else
	{
		if (s <= a)
			return {};
	}
	return s;
}

template <typename T> std::optional<T> safeAdd(T a, T b)
{
	static_assert(std::is_signed<T>(), "type must be signed (for now)");
	typedef typename std::make_unsigned<T>::type uT;
	T s = (uT)a + (uT)b;
	
	if (b >= 0)
	{
		if (s < a)
			return {};
	}	
	else
	{
		if (s >= a)
			return {};
	}
	return s;
}

#endif