#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "core.h"
#include "layer.h"
#include "Window/window.h"


class Application {
	private:
		Window* m_window;

	protected:
		bool m_running;
		LayerStack m_layerStack;

	public:
		Application(uint32_t width, uint32_t height, const char* title);
		virtual ~Application();

		void Run();
		void onEvent(Event& event);
};


#endif
