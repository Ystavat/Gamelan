#ifndef __FILE_H__
#define __FILE_H__

#include "core.h"
#include "decompress.h"

const char* readFile(const char* name);

const char* readFile(const char* name, int* size);

void writeFile(const char* name, char* buffer, int size);

uint8_t* readPNG(const char* name, uint32_t* pwidth, uint32_t* pheight, uint8_t* pchannels);


#endif
