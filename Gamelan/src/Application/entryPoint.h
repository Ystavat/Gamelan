#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

#include "core.h"
#include "application.h"

#define GAMELAN_USE(app) Application* createApplication() { return new app(); }


extern Application* createApplication();

int main(int argc, char** argv);


#endif
