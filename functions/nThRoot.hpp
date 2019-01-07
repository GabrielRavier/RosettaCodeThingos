#include <type_traits>
#include <cmath>

template <typename T> T nThRoot(T nVal, T degree)
{
	static_assert(std::is_floating_point<T>::value, "only works on floating point");
	
	return pow(value, (T)1 / degree);
}