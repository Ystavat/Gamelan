#include "file.h"


const char* readFile(const char* name) {
	int size;
	char* content;

	std::ifstream file(name);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
		content = new char[size+1];
		file.seekg(0, std::ios::beg);
		file.read(content, size);
		content[size] = '\0';
		file.close();
		return content;
	}

	CORE_CRITIC("Could not open file \"", name, "\"");
	exit(EXIT_FAILURE);
}

const char* readFile(const char* name, int* size) {
	char* content;

	std::ifstream file(name);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		*size = file.tellg();
		content = new char[*size];
		file.seekg(0, std::ios::beg);
		file.read(content, *size);
		file.close();
		return content;
	}

	CORE_CRITIC("Could not open file \"", name, "\"");
	exit(EXIT_FAILURE);
}

void writeFile(const char* name, char* buffer, int size) {
	std::ofstream file(name);
	if (file.is_open()) {
		file.write(buffer, size);
		file.close();
		return;
	}

	CORE_CRITIC("Could not open file \"", name, "\"");
	exit(EXIT_FAILURE);
}
