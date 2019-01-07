#include <string>
#include <cstddef>

using std::string;

string stripWhitespace(const string& input)
{
	size_t whitePos = input.find_first_not_of(' ');
	
	if (whitePos == std::string::npos)
		whitePos = 0;
	
	return input.substr(whitePos, input.find_last_not_of(' ') - whitePos + 1);
}

string stripComments(const string& input, const string& delimiters)
{
	return stripWhitespace(input.substr(0, input.find_first_not_of(delimiters)));
}

