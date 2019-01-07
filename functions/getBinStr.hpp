#ifndef GETBINSTR_INCLUDED
#define GETBINSTR_INCLUDED

#include <bitset>
#include <string>
#include <limits>

template <typename T> std::string getBinStr(const T& n)
{
	if (n > 0)
	{
		auto str = std::bitset<std::numeric_limits<T>::digits>(n).to_string();
		return str.substr(str.find('1'));	// Remove leading 0s
	}
	else
		return std::string('0');
}

#endif