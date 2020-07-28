#include "cameraController.h"


void OrthographicCameraController::onUpdate(float dt) {
	bool translated = false;
	bool rotated = false;
	if (Inputs::isKeyPressed(262)) {
		m_position.x -= m_translationSpeed*dt;
		translated = true;
	}
	if (Inputs::isKeyPressed(263)) {
		m_position.x += m_translationSpeed*dt;
		translated = true;
	}
	if (Inputs::isKeyPressed(264)) {
		m_position.y += m_translationSpeed*dt;
		translated = true;
	}
	if (Inputs::isKeyPressed(265)) {
		m_position.y -= m_translationSpeed*dt;
		translated = true;
	}
	if (Inputs::isKeyPressed(65)) {
		m_rotation -= m_rotationSpeed*dt;
		rotated = true;
	}
	if (Inputs::isKeyPressed(68)) {
		m_rotation += m_rotationSpeed*dt;
		rotated = true;
	}
	if (translated) {
		m_camera.setPosition(m_position);
	}
	if (rotated) {
		m_camera.setRotation(m_rotation);
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
