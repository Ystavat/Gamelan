#ifndef __DECOMPRESS_H__
#define __DECOMPRESS_H__

#include "core.h"
#include <zlib.h>

void filter(uint8_t* buffer, uint32_t scanLine, uint8_t pad, uint32_t position, uint8_t type, bool priorH = true, bool priorV = true);

bool autoInflate(uint8_t** buffer_, uint32_t* size_);

struct PNGChunk {
	char m_type[5];
	uint32_t m_length;

	PNGChunk(std::ifstream& file);

	static uint32_t getLong(std::ifstream& file);

	static void move(std::ifstream& file, int delta = 4);

	bool is(const char* type);
};


#endif
