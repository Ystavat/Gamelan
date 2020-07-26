#include "cameraController.h"


void OrthographicCameraController::onUpdate(float dt) {
	if (Inputs::isKeyPressed(65)) {
		APP_ERROR("camera");
	}
}

bool OrthographicCameraController::onWindowResized(WindowResizeEvent& event) {
	m_aspectRatio = (float)event.getWidth() / event.getHeight();
	m_camera.setProjection(m_aspectRatio*m_zoomLevel, m_zoomLevel);
	return false;
}

bool OrthographicCameraController::onMouseScrolled(MouseScrollEvent& event) {
	m_zoomLevel = std::max(0.25f, m_zoomLevel-event.getDy()*0.25f);
	m_camera.setProjection(m_aspectRatio*m_zoomLevel, m_zoomLevel);
	return false;
}

void OrthographicCameraController::onEvent(Event& event) {
	dispatch<WindowResizeEvent>(event, M_BIND(OrthographicCameraController::onWindowResized));
	dispatch<MouseScrollEvent>(event, M_BIND(OrthographicCameraController::onMouseScrolled));
}
