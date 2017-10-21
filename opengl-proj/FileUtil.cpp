#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string readFileToString(const std::string &path) {
	std::ifstream inFile(path);
	if (!inFile.is_open()) {
		throw std::runtime_error("ERROR::FILEUTIL::FILE_NOT_SUCCESSFULLYREAD" + path);
	}

	std::stringstream stream;

	stream << inFile.rdbuf();
	return stream.str();
}