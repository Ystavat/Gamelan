#include "vertexArray.h"


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_rendererID);
	glBindVertexArray(m_rendererID);
}

VertexArray::~VertexArray() {
	glDeleteBuffers(1, &m_rendererID);
}

void VertexArray::bind() const {
	glBindVertexArray(m_rendererID);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}