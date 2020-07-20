#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__

#include "GL/glew.h"
#include "core.h"


class IndexBuffer {
	private:
		uint32_t m_id;
		uint32_t m_count;

	public:
		IndexBuffer(const uint32_t* data, uint32_t count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline uint32_t getCount() const { return m_count; }
};


#endif
