#include "camera.h"


OrthographicCamera::OrthographicCamera(float width, float height):
	m_projection(1/width, 0, 0, 0,
		     0, 1/height, 0, 0,
		     0, 0, 1, 0,
		     0, 0, 0, 1) { m_viewProjection = dot(m_view, m_projection); }

void OrthographicCamera::setProjection(float width, float height) {
	m_projection = {1/width, 0, 0, 0,
			0, 1/height, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};
}

void OrthographicCamera::recalculate() {
	m_view = { C, S, 0, 0,
		  -S, C, 0, 0,
		   0, 0, 1, 0,
		   0, 0, 0, 1 };
	/*mat4 m_T = { 1, 0, 0, X,
		0, 1, 0, Y,
		0, 0, 1, 0,
		0, 0, 0, 1 };*/
	m_viewProjection = dot(m_view, m_projection);
}
