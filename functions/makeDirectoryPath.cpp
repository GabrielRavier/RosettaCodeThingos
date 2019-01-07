#include <filesystem>

namespace fs = std::filesystem;

// Returns whether succeeded
bool makeDirectoryPath(const fs::path& file)
{
	if (fs::exists(file))
		return true;
	
	return fs::create_directories(file);
}