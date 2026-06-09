#pragma once

#include <string>
#include <filesystem>



bool writeFile(const std::filesystem::path &filePath, std::string_view content);

bool appendToFile(const std::filesystem::path &filePath, const std::string &content);


inline auto GetFileContents(const std::string& projectName)
{

	std::string cmakeContent = "cmake_minimum_required(VERSION 3.27)\n"
		"project(" + projectName + " VERSION 1.0 LANGUAGES CXX)\n\n"
		"set(CMAKE_CXX_STANDARD 17)\n"
		"set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"
		"set(CMAKE_EXPORT_COMPILE_COMMANDS ON) \n"
		"set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out)\n"
		"set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out)\n\n"
		"add_executable(${PROJECT_NAME} main.cpp)\n";


	std::string cppContent ="#include <iostream>\n\n"
		"int main() {\n"
		"    std::cout << \"Hello from " + projectName + "!\\n\";\n"
		"    return 0;\n"
		"}\n";


	std::string gitignoreContent = "build/ \n"
	".cmake/ \n"
	"out/ \n"
	"CMakeUserPresets.json \n"
	"vcpkg_installed/ \n";

	return std::vector<std::string>{cmakeContent, cppContent, gitignoreContent};
}