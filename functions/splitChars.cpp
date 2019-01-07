#include <string>

using std::string;

auto splitChars(const string& str, const string& delim)
{
	string result;
	for (auto ch : str)
	{
		if (!result.empty() && ch != result.back())
			result += delim;
		result += ch;
	}
	
	return result;
}