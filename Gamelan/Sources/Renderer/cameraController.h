#ifndef __CAMERA_CONTROLLER__
#define __CAMERA_CONTROLLER__

#include "core.h"
#include "camera.h"
#include "Window/Event/event.h"
#include "Window/Event/eventPolling.h"


class OrthographicCameraController {
	private:
		float m_aspectRatio;
		float m_zoomLevel;
		OrthographicCamera m_camera;
		vec3 m_position = { 0.f };
		float m_rotation = 0.f;
		float m_translationSpeed = 5.f;
		float m_rotationSpeed = 1.f;

		bool onMouseScrolled(MouseScrollEvent& event);
		bool onWindowResized(WindowResizeEvent& event);

	public:
		OrthographicCameraController(float aspectRatio): m_aspectRatio(aspectRatio), m_camera(aspectRatio) {}

		void onUpdate(float dt);
		void onEvent(Event& event);

		OrthographicCamera& getCamera() { return m_camera; }
		const OrthographicCamera& getCamera() const { return m_camera; }
};


#endif
