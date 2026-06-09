#include "checkinstalled.h"

#include <filesystem>
#include <string>
#include <sstream>





bool isVcpkgInstalled() 
{
	namespace fs = std::filesystem;
	
	const auto pathEnv = std::getenv("PATH");
	if (!pathEnv)
		return false;

#ifdef _WIN32
	std::string targetExe = "vcpkg.exe";
	char pathSeparator = ';'; // Windows uses semicolons
#else
	std::string targetExe = "vcpkg";
	char pathSeparator = ':'; // Linux/macOS use colons
#endif

	std::string pathStr(pathEnv);
	std::stringstream ss(pathStr);
	std::string directory;

	while (std::getline(ss, directory, pathSeparator)) 
	{
		if (directory.empty()) continue;

		try {
			auto fullPath = fs::path(directory) / targetExe;
			
			if (fs::exists(fullPath) && !fs::is_directory(fullPath)) {
				return true; 
			}
		} catch (const fs::filesystem_error&) {
			continue;
		}
	}

	return false;
}