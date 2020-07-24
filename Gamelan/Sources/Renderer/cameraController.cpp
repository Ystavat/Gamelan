#include "cameraController.h"


void OrthographicCameraController::onUpdate(float dt) {
	if (Inputs::isKeyPressed(65)) {
		APP_ERROR("camera");
	}
}

bool OrthographicCameraController::onWindowResized(WindowResizeEvent& event) {
	APP_TRACE("resized");
	return true;
}

bool OrthographicCameraController::onMouseScrolled(MouseScrollEvent& event) {
	APP_TRACE("scrolled");
	return true;
}

void OrthographicCameraController::onEvent(Event& event) {
	dispatch<WindowResizeEvent>(event, M_BIND(OrthographicCameraController::onWindowResized));
	dispatch<MouseScrollEvent>(event, M_BIND(OrthographicCameraController::onMouseScrolled));
}
