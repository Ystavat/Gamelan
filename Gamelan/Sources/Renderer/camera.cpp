#include "camera.h"


OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float angle, float near, float far):
	m_left(left), m_right(right), m_bottom(bottom), m_near(near), m_far(far),
	m_projection(C*X, -S*Y, 0, A*C-B*S,
		     S*X,  C*Y, 0, A*S+B*C,
		     0, 0, -2/(far-near), -(far+near)/(far-near),
		     0, 0,  0, 1) {}

mat4& OrthographicCamera::getProjection() { return m_projection; }
