#include "frameBuffer.h"


FrameBuffer::FrameBuffer(uint32_t slot, uint32_t width, uint32_t height): m_width(width), m_height(height) {
	glGenFramebuffers(1, &m_id);
	m_slot = slot;
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	glActiveTexture(GL_TEXTURE0+slot);
	glGenTextures(1, &m_colorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);
	
	CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Incomplete framebuffer");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

VertexArray* FrameBuffer::s_vao_p;
VertexBuffer<lyt::Float2, lyt::Float2>* FrameBuffer::s_vbo_p;
IndexBuffer* FrameBuffer::s_ibo_p;
void FrameBuffer::init() {
	PROFILE_FUNCTION();

	s_vao_p = new VertexArray();
	s_vbo_p = new VertexBuffer<lyt::Float2, lyt::Float2>(4);
	VertexBuffer<lyt::Float2, lyt::Float2> vbo = *s_vbo_p;
	vbo[0].set(-1.0, -1.0, 0.0, 0.0);
	vbo[1].set( 1.0, -1.0, 1.0, 0.0);
	vbo[2].set( 1.0,  1.0, 1.0, 1.0);
	vbo[3].set(-1.0,  1.0, 0.0, 1.0);
	vbo.bind();
	vbo.update();
	vbo.applyLayout();

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	s_ibo_p = new IndexBuffer(indices, 6);

	s_vao_p->unbind();
	s_vbo_p->unbind();
	s_ibo_p->unbind();
}

void FrameBuffer::pass() {
	s_vao_p->bind();
	RenderingContext::drawIndexed(6);
}
