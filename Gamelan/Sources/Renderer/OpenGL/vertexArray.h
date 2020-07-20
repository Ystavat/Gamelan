#pragma once

#include "GL\glew.h"
#include "core.h"

class VertexArray
{
private:
	uint32_t m_rendererID;
public:

	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

};