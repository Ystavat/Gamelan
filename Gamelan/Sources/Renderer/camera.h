#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "core.h"


class OrthographicCamera {
	private:
		float m_left;
		float m_right;
		float m_bottom;
		float m_top;
		float m_near;
		float m_far;
		mat4 m_projection;

	public:
		OrthographicCamera(float left, float right, float bottom, float top, float near=-1, float far=1):
			m_left(left), m_right(right), m_bottom(bottom), m_near(near), m_far(far),
			m_projection(2/(right-left), 0, 0, -(right+left)/(right-left),
			             0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom),
				     0, 0,  -2/(far-near), -(far+near)/(far-near),
				     0, 0, 0, 1) {}
		mat4& getProjection() { return m_projection; }
};


#endif
