#include "renderingContext.h"


RenderingContext::RenderingContext(GLFWwindow* windowHandle): m_windowHandle(windowHandle) {
	glfwMakeContextCurrent(m_windowHandle);
	CORE_ASSERT(glewInit()==GLEW_OK, "Glew failed to initialize")

	CORE_INFO(glGetString(GL_VERSION));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void RenderingContext::setViewport(uint32_t width, uint32_t height) { glViewport(0, 0, width, height); }
void RenderingContext::setClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
void RenderingContext::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void RenderingContext::drawIndexed(uint32_t count) { glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL); }

void RenderingContext::SwapBuffers() { glfwSwapBuffers(m_windowHandle); }
