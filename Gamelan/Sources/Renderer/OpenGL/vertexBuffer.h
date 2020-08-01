#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__

#include "core.h"
#include <GL/glew.h>


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
struct calc;
template<size_t H>
struct calc<H>{ static constexpr size_t get() { return H; } };
template<size_t H, size_t... T>
struct calc<H, T...>{ static constexpr size_t get() { return H+calc<T...>::get(); } };

template<typename T, size_t n, class C>
struct unwrap;
template<typename... T, size_t n, class C0, class... Ct>
struct unwrap<types<T...>, n, types<C0, Ct...>>: public unwrap<types<T..., typename C0::base>, n-1, types<C0, Ct...>> {};
template<typename... T, class C0, class C1, class... Ct>
struct unwrap<types<T...>, 0, types<C0, C1, Ct...>>: public unwrap<types<T...>, C1::count, types<C1, Ct...>> {};
template<typename... T, class C0>
struct unwrap<types<T...>, 0, types<C0>> { typedef types<T...> type; };


template<typename T, typename R>
union mixHolder;
template<typename... T, typename... R>
union mixHolder<types<T...>, types<R...>> {
	typedef Tuple<T...> t1;
	typedef Tuple<R...> t2;
	t1 _1;
	t2 _2;
	operator t1() { return _1; }
	operator t2() { return _2; }
	void set(T... args) { _1.set(args...); }
	void set(R... args) { _2.set(args...); }
	mixHolder() {}
};

template<size_t i, typename Head, typename... Tail, typename _>
Head& get(mixHolder<types<Head, Tail...>, _>& mx) { return get<i>(mx._1); }
template<size_t i, typename Head, typename... Tail, typename _>
Head& get_(mixHolder<_, types<Head, Tail...>>& mx) { return get<i>(mx._2); }

template<class...  T>
class VertexBuffer {
	private:
		typedef mixHolder<types<typename T::type...>, typename unwrap<types<>, 0, types<bool, T...>>::type> type;
		typedef BasicIterator<type> iterator;
		typedef BasicReverseIterator<type> reverseIterator;

		static constexpr size_t s_sizes[sizeof...(T)] = { T::size... };
		static constexpr size_t s_counts[sizeof...(T)] = { T::count... };
		static constexpr size_t s_types[sizeof...(T)] = { T::GLtype... };
		static constexpr size_t s_stride = calc<T::size...>::get();

		uint32_t m_id;
		type* m_data;
		size_t m_count;

	public:
		VertexBuffer(size_t n): m_data(new type[n]), m_count(n) { glGenBuffers(1, &m_id); }
		~VertexBuffer() {
			delete[] m_data;
			glDeleteBuffers(1, &m_id);
		}

		constexpr size_t getStride() { return s_stride; }
		void* getRaw() { return m_data; }
		void* getCount() { return m_count; }

		type& operator[](size_t i) { return m_data[i]; }
		const type& operator[](size_t i) const { return m_data[i]; }

		iterator begin() { return iterator(m_data); }
		iterator end() { return iterator(m_data+m_count); }
		reverseIterator rbegin() { return reverseIterator(m_data+m_count-1); }
		reverseIterator rend() { return reverseIterator(m_data-1); }
		Reverse<VertexBuffer> reverse() { return Reverse<VertexBuffer>(*this); }

		void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
		void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		void update() { glBufferData(GL_ARRAY_BUFFER, m_count*s_stride, m_data, GL_STATIC_DRAW); }
		void applyLayout() {
			size_t stride = 0;
			for (size_t i = 0 ; i < sizeof...(T) ; i++) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, s_counts[i], s_types[i], GL_FALSE, s_stride, (const void*)(uintptr_t)stride);
				stride += s_sizes[i];
			}
		}
};

template<class...  T>
constexpr size_t VertexBuffer<T...>::s_sizes[];
template<class...  T>
constexpr size_t VertexBuffer<T...>::s_counts[];
template<class...  T>
constexpr size_t VertexBuffer<T...>::s_types[];
template<class...  T>
constexpr size_t VertexBuffer<T...>::s_stride;


#endif
