#include "window.h"


void Window::error_callback(int code, const char* description) {
	CORE_ERROR("code: ", code, "\n", description);
}

Window::Window(uint32_t width, uint32_t height, const char* title, bool vsync): m_width(width), m_height(height), m_vsync(vsync) {
	PROFILE_FUNCTION();

	CORE_ASSERT(glfwInit(), "GLFW failed to initialize");
	glfwSetErrorCallback(Window::error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	CORE_ASSERT(m_window, "GLFW failed to create a window");

	m_context = new RenderingContext(m_window);
	RenderingContext::setViewport(m_width, m_height);

	glfwSetWindowUserPointer(m_window, &m_hook);
	setWindowEventsCallback(m_window);
	Inputs::setWindow(m_window);
}

Window::~Window() {
	glfwTerminate();
}

void Window::clear() {
	PROFILE_FUNCTION();
	m_context->clear();
}

void Window::onUpdate() {
	PROFILE_FUNCTION();
	m_context->SwapBuffers();
	glfwPollEvents();
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

void Window::setEventCallback(EventCallback callback) { m_hook.callback = callback; } // Override the default hook by our hook
uint32_t Window::getWidth() { return m_width; }
uint32_t Window::getHeight() { return m_height; }
bool Window::isVsync() { return m_vsync; }
void Window::setVsync(bool vsync) {
	m_vsync = vsync;
	glfwSwapInterval(vsync ? 1 : 0);
}
