#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include "core.h"
#include <GL/glew.h>


class FrameBuffer {
	private:
		uint32_t m_id;
		uint32_t m_colorAttachment;
		uint32_t m_width;
		uint32_t m_height;

	public:
		FrameBuffer(uint32_t width, uint32_t height);
		~FrameBuffer() { glDeleteFramebuffers(1, &m_id); }

		void bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_id); }
		void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};


#endif
