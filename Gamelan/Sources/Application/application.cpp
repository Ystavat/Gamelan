#include "application.h"


Application* Application::s_instance = nullptr;

Application::Application(uint32_t width, uint32_t height, const char* title): m_running(true) {
	CORE_ASSERT_NOT(s_instance, "Only a single application can be instanciated");
	s_instance = this;
	CORE_WARN("Application started");
	m_window = new Window(width, height, title); // Set the width, height and title of the window
	m_window->setEventCallback(M_BIND(Application::onEvent)); // Override the default hook by our hook
}

Application::~Application() {
	delete m_window;
	CORE_WARN("Application stopped");
}

void Application::onEvent(Event& event) {
	dispatch<WindowCloseEvent>(event, [this](WindowCloseEvent& e) { m_running = false; return true; });
	dispatch<WindowResizeEvent>(event, [](WindowResizeEvent& e) { RenderingContext::setViewport(e.getWidth(), e.getHeight()); return true; });
	m_layerStack.onEvent(event);
}

void Application::Run() {
	std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> timeNow;
	float deltaTime;
	while (m_running) {
		timeNow = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - lastFrameTime).count()/1000000.0f;
		lastFrameTime = timeNow;

		m_window->clear();
		m_layerStack.onUpdate(deltaTime);
		m_window->onUpdate();
	}
}

Application& Application::get() { return *s_instance; }
