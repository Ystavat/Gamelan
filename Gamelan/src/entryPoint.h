#pragma once

extern Application* createApplication();

int main(int argc, char** argv) {

	auto app = createApplication();
	app->Run();
	delete(app);

}