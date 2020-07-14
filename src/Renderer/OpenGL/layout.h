#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "core.h"
#include <GL/glew.h>


enum ShaderDataType {
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool,
	nbTypes	
};

struct LayoutElement {
	ShaderDataType type;
	bool normalized;
	uint32_t offset;

	static uint8_t s_sizes[ShaderDataType::nbTypes];
	static uint8_t s_counts[ShaderDataType::nbTypes];
	static GLenum s_GLTypes[ShaderDataType::nbTypes];

	LayoutElement();
	LayoutElement(ShaderDataType type_, bool normalized_ = false);

	uint8_t getSize();
	uint8_t getCount();
	GLenum getType();
};

class Layout {
	private:
		LayoutElement* m_elements;
		uint8_t m_count;
		uint32_t m_stride;

	public:
		Layout();
		Layout(std::initializer_list<LayoutElement> elements);
		Layout(LayoutElement* elements, uint8_t count);
		Layout(const Layout& other);
		~Layout();

		uint32_t getStride();

		void bind();
};


#endif
