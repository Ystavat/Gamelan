#ifndef __EVENTCALLBACK_H__
#define __EVENTCALLBACK_H__

#include "core.h"
#include <GLFW/glfw3.h>
#include "event.h"

#define GET_HOOK GLFWHook& hook = *(GLFWHook*)glfwGetWindowUserPointer(window) // Defines our hook


using EventCallback = std::function<void(Event&)>; // Pointer to a function
struct GLFWHook {
	EventCallback callback = [](Event& e) { CORE_TRACE(e.getType()); }; // Default hook
};

void setWindowEventsCallback(GLFWwindow* window);


#endif
