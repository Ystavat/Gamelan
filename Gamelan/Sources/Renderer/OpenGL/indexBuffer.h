#pragma once

#include "GL\glew.h"
#include "core.h"

class IndexBuffer
{
private:
	uint32_t m_rendererID;
	uint32_t m_count;
public:

	IndexBuffer(const uint32_t* data, uint32_t count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline uint32_t GetCount() const { return m_count; }
};