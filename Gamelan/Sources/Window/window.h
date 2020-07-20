#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "core.h"
#include "Renderer/OpenGL/renderingContext.h"
#include "Event/event.h"
#include "Event/eventCallback.h"
#include "Event/eventPolling.h"

class Window {
	private:
		uint32_t m_width;
		uint32_t m_height;
		bool m_vsync;
		GLFWHook m_hook;
		GLFWwindow* m_window;
		RenderingContext* m_context;

		static void error_callback(int code, const char* description);
	
	public:
		Window(uint32_t width, uint32_t height, const char* title, bool vsync = true);
		~Window();

		void clear();
		void onUpdate();
		bool shouldClose();

		void setEventCallback(EventCallback callback);
		uint32_t getWidth();
		uint32_t getHeight();
		bool isVsync();
		void setVsync(bool vsync);
};


#endif
