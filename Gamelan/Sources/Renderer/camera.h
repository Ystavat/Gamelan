#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "core.h"

#define C cos(m_rotation)
#define S sin(m_rotation)
#define X m_position.x
#define Y m_position.y
#define W 1/width
#define H 1/height


class OrthographicCamera {
	private:
		mat4 m_projection;
		mat4 m_view;
		mat4 m_viewProjection;

		vec3 m_position = { 0.0f };
		float width = 1.0f;
		float height = 1.0f;
		float m_rotation = 0.0f;

		void recalculate();

	public:
		OrthographicCamera(float aspectRatio): OrthographicCamera(aspectRatio, 1) {};
		OrthographicCamera(float width, float height);
		void setProjection(float width, float height);

		const vec3& getPosition() const { return m_position; }
		void setPosition(const vec3& position) { m_position = position; recalculate(); }

		float getRotation() const { return m_rotation; }
		void setRotation(float rotation) { m_rotation = rotation; recalculate(); }

		const mat4& getProjection() { return m_projection; }
		const mat4& getView() { return m_view; }
		const mat4& getViewProjection() { return m_viewProjection; }
};


#endif
