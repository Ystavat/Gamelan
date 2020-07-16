#include "application.h"


Application::Application(uint32_t width, uint32_t height, const char* title) {
	CORE_WARN("Application started");
	m_window = new Window(width, height, title);
	m_window->setEventCallback([this](Event& e) { onEvent(e); });
}

Application::~Application() {
	delete m_window;
	CORE_WARN("Application stopped");
}

void Application::Run() {
	while (!m_window->shouldClose()) {
		m_window->onUpdate();
		m_window->clear();
		onUpdate();
	}
}
