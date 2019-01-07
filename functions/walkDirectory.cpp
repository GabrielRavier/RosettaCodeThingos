#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <vector>
#include <string>

namespace fs = boost::filesystem;
using std::vector;
using std::string;

vector<string> walkDirectoryNonRecursively(const fs::path& dir, const boost::regex& pattern)
{
	vector<string> result;
	for (fs::directory_iterator iter(dir), end; iter != end; ++iter)
	{
		boost::smatch match;
		const string fn = iter->path().filename().string();
		
		if (boost::regex_match(fn, match, pattern))
			result.push_back(match[0]);
	}
	
	return result;
}

vector<string> walkDirectoryRecursively(const fs::path& dir, const boost::regex& pattern)
{
	vector<string> result;
	
	for(fs::recursive_directory_iterator iter(dir), end; iter != end; ++iter)
	{
		string name = iter->path().filename().string();
		if (boost::regex_match(name, pattern))
			result.push_back(iter->path().string());
	}
}