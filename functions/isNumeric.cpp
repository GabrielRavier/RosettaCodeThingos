#include <string>
#include <algorithm>
#include <cctype>

using std::string;

bool isNumeric(const string& str)
{
	return std::all_of(str.begin(), str.end(), isdigit);
}