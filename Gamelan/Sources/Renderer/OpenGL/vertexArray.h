#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "GL/glew.h"
#include "core.h"


class VertexArray {
	private:
		uint32_t m_id;

	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;
};


#endif
