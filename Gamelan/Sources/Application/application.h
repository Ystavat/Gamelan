#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "core.h"
#include "Window/window.h"


class Application {
	private:
		Window* m_window;

		void coreDispatcher(Event& event);

	protected:
		bool m_running;

	public:
		Application(uint32_t width, uint32_t height, const char* title);
		virtual ~Application();

		void Run();

		virtual void onUpdate(float deltaTime) = 0;
		virtual void onEvent(Event& event) = 0;
};


#endif
