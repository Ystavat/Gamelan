#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

#include "core.h"
#include "application.h"

#define GAMELAN_USE(app) Application* createApplication() { return new app(); }


extern Application* createApplication();

int main(int argc, char** argv) {

	LOG_INIT();
	CORE_LOGGER(setPrompt("[%f(%l)]%N: "));
	APP_LOGGER(setPrompt("[%f(%l)]%N: "));
	PROFILE_SESSION();

	{
		PROFILE_SCOPE("Engine runtime");

		Application* app = createApplication();
		app->Run();
		delete(app);
	}

	LOG_TERMINATE();
	exit(EXIT_SUCCESS);
}

#endif