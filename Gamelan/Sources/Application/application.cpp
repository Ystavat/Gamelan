#include "application.h"


Application::Application(uint32_t width, uint32_t height, const char* title): m_running(true) {
	CORE_WARN("Application started");
	m_window = new Window(width, height, title);
	m_window->setEventCallback(M_BIND(Application::coreDispatcher));
}

Application::~Application() {
	delete m_window;
	CORE_WARN("Application stopped");
}

void Application::coreDispatcher(Event& event) {
	dispatch<WindowCloseEvent>(event, [this](WindowCloseEvent& e) { m_running = false; return true; });
	dispatch<WindowResizeEvent>(event, [](WindowResizeEvent& e) { RenderingContext::setViewport(e.getWidth(), e.getHeight()); return true; });
	if (!event.m_handled) {
		onEvent(event);
	}
}

void Application::Run() {
	std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> timeNow;
	float deltaTime;
	while (m_running) {
		timeNow = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - lastFrameTime).count()/1000000.0;
		lastFrameTime = timeNow;

		m_window->clear();
		onUpdate(deltaTime);
		m_window->onUpdate();
	}
}
