#ifndef __FILE_H__
#define __FILE_H__

#include "core.h"

const char* readFile(const char* name);

const char* readFile(const char* name, int* size);

void writeFile(const char* name, char* buffer, int size);

#endif