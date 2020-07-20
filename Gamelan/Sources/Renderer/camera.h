#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "core.h"

#define X 2/(right-left)
#define Y 2/(top-bottom)
#define A -(right+left)/(right-left)
#define B -(top+bottom)/(top-bottom)
#define C cos(angle)
#define S sin(angle)


class OrthographicCamera {
	private:
		float m_left;
		float m_right;
		float m_bottom;
		float m_top;
		float angle;
		float m_near;
		float m_far;
		mat4 m_projection;

	public:
		OrthographicCamera(float left, float right, float bottom, float top, float angle=0, float near=-1, float far=1);

		mat4& getProjection();
};


#endif
