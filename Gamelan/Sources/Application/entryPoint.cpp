#include "entryPoint.h"


int main(int argc, char** argv) {

	LOG_INIT();
	CORE_LOGGER(setPrompt("[%f(%l)]%N: "));
	APP_LOGGER(setPrompt("[%f(%l)]%N: "));
	PROFILE_SESSION();

	{
		PROFILE_SCOPE("Engine runtime");

		Application* app = createApplication();
		app->run();
		delete(app);
	}

	LOG_TERMINATE();
	exit(EXIT_SUCCESS);
}
