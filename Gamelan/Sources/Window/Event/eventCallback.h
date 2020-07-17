#ifndef __EVENTCALLBACK_H__
#define __EVENTCALLBACK_H__

#include "core.h"
#include <GLFW/glfw3.h>
#include "event.h"

#define GET_HOOK GLFWHook& hook = *(GLFWHook*)glfwGetWindowUserPointer(window)


using EventCallback = std::function<void(Event&)>;
struct GLFWHook {
	EventCallback callback = [](Event& event) { CORE_TRACE("Default ", event.getType()); };
};

void setWindowEventsCallback(GLFWwindow* window);


#endif
