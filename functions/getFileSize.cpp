#include <fstream>
#include <string>

using std::string;
using std::ifstream;

std::ios::off_type getFileSize(const string& name)
{
	ifstream f(name);
	std::ios::pos_type begin = f.tellg();
	
	f.seekg(0, std::ios::end);
	
	std::ios::pos_type end = f.tellg();
	return end - begin;
}