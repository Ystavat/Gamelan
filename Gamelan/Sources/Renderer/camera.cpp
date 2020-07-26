#include "camera.h"


OrthographicCamera::OrthographicCamera(float width, float height):
	m_projection(1/width, 0, 0, 0,
		     0, 1/height, 0, 0,
		     0, 0, 1, 0,
		     0, 0, 0, 1) { m_viewProjection = dot(m_projection, m_view); }

void OrthographicCamera::setProjection(float width, float height) {
	m_projection = {1/width, 0, 0, 0,
			0, 1/height, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};
	m_viewProjection = dot(m_projection, m_view);
}

void OrthographicCamera::recalculate() {
	mat4 m_R = {
		 C, S, 0, 0,
		-S, C, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1 };
	mat4 m_T = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	m_view = dot(m_R, m_T);
	m_viewProjection = dot(m_projection, m_view);
}
