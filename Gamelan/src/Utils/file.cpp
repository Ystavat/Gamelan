#include "file.h"


const char* readFile(const char* name) {
	int size;
	char* content;

	std::ifstream file;
	file.open(name, std::ios_base::in | std::ios_base::binary);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
		CORE_DEBUG(size);
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

	std::ifstream file;
	file.open(name, std::ios_base::in | std::ios_base::binary);
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

uint8_t* readPNG(const char* name, uint32_t* pwidth, uint32_t* pheight, uint8_t* pchannels) {
	uint8_t skipHeader = 8;
	uint8_t channels = *pchannels;
	uint32_t width;
	uint32_t height;
	uint8_t pad;
	uint32_t position = 0;
	uint8_t type;
	uint8_t* content;
	uint8_t* image;

	std::ifstream file;
	file.open(name, std::ios_base::in | std::ios_base::binary);
	if (file.is_open()) {
		file.seekg(skipHeader);
		PNGChunk ihdr(file);
		if (!ihdr.is("IHDR")) {
			CORE_CRITIC("Bad format \"", name, "\"");
			exit(EXIT_FAILURE);
		}

		width = PNGChunk::getLong(file);
		height = PNGChunk::getLong(file);
		char flags[5];
		file.read(flags, 5);
		if ((flags[1] != 2 && flags[1] != 6) || flags[2] || flags[3] || flags[4]) {
			CORE_CRITIC("Unsupported format \"", name, "\"");
		}
		pad = flags[1] == 2 ? 3 : 4;
		if (channels == 0) {
			channels = pad;
			*pchannels = pad;
		}
		image = new uint8_t[width*height*channels];
		memset(image, 255, width*height*channels);

		PNGChunk::move(file);
		while (!file.eof()) {
			PNGChunk c(file);
			if (c.is("IEND"))
				break;
			if (c.is("IDAT")) {
				content = new uint8_t[c.m_length];
				file.read((char*)content, c.m_length);
				autoInflate(&content, &c.m_length);
				position = 0;
				for (uint32_t y = 0 ; y < height ; y++) {
					type = content[position++];
					for (uint32_t x = 0 ; x < width ; x++) {
						for (uint32_t z = 0 ; z < pad ; z++) {
							filter(content, width, pad, position, type, x > 0, y > 0);
							if (z < channels) {
								image[(y*width+x)*channels+z] = content[position];
							}
							position++;
						}
					}
				}
				delete[] content;
				*pwidth = width;
				*pheight = height;
				break;
			} else {
				PNGChunk::move(file, c.m_length);
			}
			PNGChunk::move(file);
		}
		return image;
	}

	CORE_CRITIC("Could not open file \"", name, "\"");
	exit(EXIT_FAILURE);
}
