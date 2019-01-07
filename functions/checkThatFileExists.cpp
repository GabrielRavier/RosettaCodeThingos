#include <filesystem>
#include <string>

enum class fsEntityType
{
	doesntExist,
	directory,
	notADirectory,
};

namespace fs = std::filesystem;
using std::string;

fsEntityType testFile(const string& path)
{
	fs::path file(path);
	
	if (exists(file))
	{
		if (is_directory(file))
			return fsEntityType::directory;
		else
			return fsEntityType::notADirectory;
	}
	else
		return fsEntityType::doesntExist;
}