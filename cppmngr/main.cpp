#include <iostream>

#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>


#include "fileops.h"
#include "checkinstalled.h"



int execCmd(const std::string& command) {
#ifdef _WIN32
	return std::system((command + " > nul 2>&1").c_str());
#else
	return std::system((command + " > /dev/null 2>&1").c_str());
#endif
}






void generateProject(const std::string& projName) 
{
	namespace fs = std::filesystem;
	
	fs::path projDir = projName;

	auto fileContents = GetFileContents(projName);

	try 
	{
		if (fs::exists(projDir)) {
			std::cerr << "Error: Directory '" << projName << "' already exists.\n";
			return;
		}
		fs::create_directories(projDir);

		
		if (!writeFile(projDir / "CMakeLists.txt", fileContents[0]) || 
			!writeFile(projDir / "main.cpp", fileContents[1]) ||
			!writeFile(projDir / ".gitignore", fileContents[2])) 
		{
			return; 
		}

		fs::path prevDir = fs::current_path(); 
		fs::current_path(projDir);

		// 2. Initialize Git
		std::cout << "Initializing Git repository...\n";
		execCmd("git init");

		if(isVcpkgInstalled())
		{
			// 3. Add vcpkg support
			std::cout << "Adding vcpkg port... \n";
			execCmd("vcpkg new --application");

			std::cout << "To add new ports (e.g. eigen3): vcpkg add port eigen3 \n";
		}

		// Restore context
		fs::current_path(prevDir);
		std::cout << "\nProject generation complete for '" << projName << "'!\n";

	} catch (const fs::filesystem_error& e) {
		std::cerr << "Filesystem system error: " << e.what() << "\n";
	}
}



int main(int argc, char* argv[]) 
{
	std::vector<std::string> args(argv, argv + argc);

	if (args.size() < 3 || args[1] != "--new") 
	{
		std::cout << "Usage: " << args[0] << " --new <project_name> \n";
		return 1;
	}

	generateProject(args[2]);

	return 0;
}
