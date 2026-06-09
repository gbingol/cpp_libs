#include "fileops.h"

#include <fstream>
#include <iostream>


namespace fs = std::filesystem;

bool writeFile(const fs::path& filePath, std::string_view content) 
{
	std::ofstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Error: Could not create file " << filePath << "\n";
		return false;
	}
	file << content;

	return true;
}


bool appendToFile(const fs::path& filePath, const std::string& content) 
{
	std::ofstream file(filePath, std::ios::app);
	
	if (!file.is_open()) {
		std::cerr << "Error: Could not modify file " << filePath << "\n";
		return false;
	}
	file << content;

	return true;
}
