#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__

#include "core.h"
#include <GL/glew.h>
#include "Utils/tuple.h"
#include "tplVB.h"


#define SHADER_TYPE_DEF(ALIAS, COUNT, BASE, TYPE, GLTYPE)\
struct ALIAS {\
	typedef TYPE type;\
	typedef BASE base;\
	static constexpr GLenum GLtype = GLTYPE;\
	static constexpr size_t count = COUNT;\
	static constexpr size_t size = sizeof(type);\
}; constexpr GLenum ALIAS::GLtype; constexpr size_t ALIAS::count; constexpr size_t ALIAS::size;

namespace lyt {
	SHADER_TYPE_DEF(Float, 1, float, float, GL_FLOAT);
	SHADER_TYPE_DEF(Float2, 2, float, vec2, GL_FLOAT);
	SHADER_TYPE_DEF(Float3, 3, float, vec2, GL_FLOAT);
	SHADER_TYPE_DEF(Float4, 4, float, vec4, GL_FLOAT);
	SHADER_TYPE_DEF(Int, 1, int, int, GL_INT);
	SHADER_TYPE_DEF(Int2, 2, int, int2, GL_INT);
	SHADER_TYPE_DEF(Int3, 3, int, int3, GL_INT);
	SHADER_TYPE_DEF(Int4, 4, int, int4, GL_INT);
	SHADER_TYPE_DEF(Mat2, 2*2, float, mat2, GL_FLOAT);
	SHADER_TYPE_DEF(Mat3, 3*3, float, mat3, GL_FLOAT);
	SHADER_TYPE_DEF(Mat4, 4*4, float, mat4, GL_FLOAT);
	SHADER_TYPE_DEF(Bool, 1, bool, bool, GL_BOOL);
}

template<size_t... T>
struct calc{};
template<size_t H>
struct calc<H>{ static constexpr size_t get() { return H; } };
template<size_t H, size_t... T>
struct calc<H, T...>{ static constexpr size_t get() { return H+calc<T...>::get(); } };

template<class H, class...  T>
class VertexBuffer {
	private:
		typedef Tuple<typename H::type, typename T::type...> type;
		static constexpr size_t s_sizes[sizeof...(T)+1] = { H::size, T::size... };
		static constexpr size_t s_counts[sizeof...(T)+1] = { H::count, T::count... };
		static constexpr size_t s_types[sizeof...(T)+1] = { H::GLtype, T::GLtype... };
		static constexpr size_t s_stride = calc<H::size, T::size...>::get();
		uint32_t m_id;
		type* m_data;
		size_t m_length;

	public:
		VertexBuffer(size_t n): m_data(new type[n]), m_length(n) { glGenBuffers(1, &m_id); }
		~VertexBuffer() { delete[] m_data; }

		type& operator[](size_t i) { return m_data[i]; }

		constexpr size_t getStride() { return s_stride; }
		void* getRaw() { return m_data; }

		void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
		void update() { glBufferData(GL_ARRAY_BUFFER, m_length*s_stride, m_data, GL_STATIC_DRAW); }
		void applyLayout() {
			size_t stride = 0;
			for (size_t i = 0 ; i < sizeof...(T)+1 ; i++) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, s_counts[i], s_types[i], GL_FALSE, s_stride, (const void*)(uintptr_t)stride);
				stride += s_sizes[i];
			}
		}
		
		vertCons<tmp<>, tmp<>, H::count, tmp<H, T...>> cons;
};

template<class H, class...  T>
constexpr size_t VertexBuffer<H, T...>::s_sizes[];
template<class H, class...  T>
constexpr size_t VertexBuffer<H, T...>::s_counts[];
template<class H, class...  T>
constexpr size_t VertexBuffer<H, T...>::s_types[];
template<class H, class...  T>
constexpr size_t VertexBuffer<H, T...>::s_stride;

#endif
