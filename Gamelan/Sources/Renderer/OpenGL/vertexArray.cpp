#include "vertexArray.h"


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const {
	glBindVertexArray(m_id);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}
