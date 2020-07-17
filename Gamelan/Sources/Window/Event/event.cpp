#include "event.h"


EventType WindowCloseEvent::getType() { return WindowClose; }
EventType WindowCloseEvent::getStaticType() { return WindowClose; }

WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height): m_width(width), m_height(height) {}
EventType WindowResizeEvent::getType() { return WindowResize; }
EventType WindowResizeEvent::getStaticType() { return WindowResize; }
uint32_t WindowResizeEvent::getWidth() { return m_width; }
uint32_t WindowResizeEvent::getHeight() { return m_height; }

EventType WindowFocusEvent::getType() { return WindowFocus; }
EventType WindowFocusEvent::getStaticType() { return WindowFocus; }

EventType WindowLoseFocusEvent::getType() { return WindowLoseFocus; }
EventType WindowLoseFocusEvent::getStaticType() { return WindowLoseFocus; }

WindowMoveEvent::WindowMoveEvent(int x, int y): m_x(x), m_y(y) {}
EventType WindowMoveEvent::getType() { return WindowMove; }
EventType WindowMoveEvent::getStaticType() { return WindowMove; }
int WindowMoveEvent::getX() { return m_x; }
int WindowMoveEvent::getY() { return m_y; }

KeyEvent::KeyEvent(int keyCode): m_keyCode(keyCode) {}
int KeyEvent::getKeyCode() { return m_keyCode; }

KeyPressEvent::KeyPressEvent(int keyCode, bool repeat): KeyEvent(keyCode), m_repeat(repeat) {}
EventType KeyPressEvent::getType() { return KeyPress; }
EventType KeyPressEvent::getStaticType() { return KeyPress; }
bool KeyPressEvent::isRepeated() { return m_repeat; }

KeyReleaseEvent::KeyReleaseEvent(int keyCode): KeyEvent(keyCode) {}
EventType KeyReleaseEvent::getType() { return KeyRelease; }
EventType KeyReleaseEvent::getStaticType() { return KeyRelease; }

MouseButtonEvent::MouseButtonEvent(int button): m_button(button) {}
int MouseButtonEvent::getButton() { return m_button; }

MouseButtonPressEvent::MouseButtonPressEvent(int button): MouseButtonEvent(button) {}
EventType MouseButtonPressEvent::getType() { return MouseButtonPress; }
EventType MouseButtonPressEvent::getStaticType() { return MouseButtonPress; }

MouseButtonReleaseEvent::MouseButtonReleaseEvent(int button): MouseButtonEvent(button) {}
EventType MouseButtonReleaseEvent::getType() { return MouseButtonRelease; }
EventType MouseButtonReleaseEvent::getStaticType() { return MouseButtonRelease; }

MouseMoveEvent::MouseMoveEvent(int x, int y): m_x(x), m_y(y) {}
EventType MouseMoveEvent::getType() { return MouseMove; }
EventType MouseMoveEvent::getStaticType() { return MouseMove; }
int MouseMoveEvent::getX() { return m_x; }
int MouseMoveEvent::getY() { return m_y; }

MouseScrollEvent::MouseScrollEvent(float dx, float dy): m_dx(dy), m_dy(dy) {}
EventType MouseScrollEvent::getType() { return MouseScroll; }
EventType MouseScrollEvent::getStaticType() { return MouseScroll; }
float MouseScrollEvent::getDx() { return m_dx; }
float MouseScrollEvent::getDy() { return m_dy; }
