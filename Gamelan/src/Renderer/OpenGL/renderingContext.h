#ifndef __RENDERING_CONTEXT_H__
#define __RENDERING_CONTEXT_H__

#include "core.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class RenderingContext {
	private:
		GLFWwindow* m_windowHandle;
	
	public:
		RenderingContext(GLFWwindow* windowHandle);

		static void setViewport(uint32_t width, uint32_t height);
		static void setClearColor(float r, float g, float b, float a);
		static void clear();
		static void drawIndexed(uint32_t count);

		void SwapBuffers();
};


#endif
