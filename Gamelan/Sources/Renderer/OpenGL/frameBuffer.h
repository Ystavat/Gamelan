#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include "core.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "renderingContext.h"
#include <GL/glew.h>


class FrameBuffer {
	private:
		uint32_t m_id;
		uint32_t m_slot;
		uint32_t m_colorAttachment;
		uint32_t m_width;
		uint32_t m_height;

		static VertexArray* s_vao_p;
		static VertexBuffer<lyt::Float2, lyt::Float2>* s_vbo_p;
		static IndexBuffer* s_ibo_p;

	public:
		FrameBuffer(uint32_t slot, uint32_t width, uint32_t height);
		~FrameBuffer() { glDeleteFramebuffers(1, &m_id); }

		static void init();
		void pass();

		void bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			RenderingContext::setViewport(m_width, m_height);
		}
		void unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
};


#endif
