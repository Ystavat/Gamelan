#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "core.h"
#include "layer.h"
#include "Window/window.h"
#include "Renderer/OpenGL/frameBuffer.h"


class Application {
	private:
		Window* m_window;
		static Application* s_instance;

	protected:
		bool m_running;
		LayerStack m_layerStack;

	public:
		Application(uint32_t width, uint32_t height, const char* title);
		virtual ~Application();

		void run();
		void shutdown();
		void onEvent(Event& event);
		void autoViewPort();

		static Application& get();
};


#endif
