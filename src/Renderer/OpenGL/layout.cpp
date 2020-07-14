#include "layout.h"


uint8_t LayoutElement::s_sizes[ShaderDataType::nbTypes] = {4, 2*4, 3*4, 4*4, 3*3*4, 4*4*4, 2*4, 3*4, 4*4, 1};
uint8_t LayoutElement::s_counts[ShaderDataType::nbTypes] = {1, 2, 3, 4, 3*3, 4*4, 1, 2, 3, 4, 1};
GLenum LayoutElement::s_GLTypes[ShaderDataType::nbTypes] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_INT, GL_INT, GL_INT, GL_INT, GL_BOOL};

LayoutElement::LayoutElement(ShaderDataType type_, bool normalized_): type(type_), normalized(normalized_), offset(0) {}
LayoutElement::LayoutElement() {}

uint8_t LayoutElement::getSize() { return s_sizes[type]; }
uint8_t LayoutElement::getCount() { return s_counts[type]; }
GLenum LayoutElement::getType() { return s_GLTypes[type]; }

Layout::Layout(): m_elements(NULL), m_count(0), m_stride(0) {}
Layout::Layout(std::initializer_list<LayoutElement> elements): m_count(elements.size()), m_stride(0) {
	m_elements = new LayoutElement[m_count];
	for (uint8_t i = 0 ; i < m_count ; i++) {
		m_elements[i] = elements.begin()[i];
		m_elements[i].offset = m_stride;
		m_stride += m_elements[i].getSize();
	}
}
Layout::Layout(LayoutElement* elements, uint8_t count): m_elements(elements), m_count(count), m_stride(0) {
	for (uint8_t i = 0 ; i < m_count ; i++) {
		m_elements[i].offset = m_stride;
		m_stride += m_elements[i].getSize();
	}
}
Layout::Layout(const Layout& other): m_count(other.m_count), m_stride(other.m_stride) {
	CORE_DEBUG("Layout copied");
	m_elements = new LayoutElement[m_count];
	for (uint8_t i = 0 ; i < m_count ; i++) {
		m_elements[i] = other.m_elements[i];
	}
}
Layout::~Layout() { delete[] m_elements; }

uint32_t Layout::getStride() { return m_stride; }

void Layout::bind() {
	for (uint8_t i = 0 ; i < m_count ; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
				m_elements[i].getCount(),
				m_elements[i].getType(),
				m_elements[i].normalized,
				m_stride,
				(const void*)(uintptr_t)(m_elements[i].offset));
	}
}
