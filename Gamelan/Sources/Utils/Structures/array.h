#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "iterator.h"


template<typename T, size_t n>
class Array {
	private:
		typedef BasicIterator<T> iterator;
		typedef BasicReverseIterator<T> reverseIterator;
		T m_data[n];

	public:
		Array() {}

		constexpr size_t getCount() { return n; }

		T& operator[](size_t i) { return m_data[i]; }
		const T& operator[](size_t i) const { return m_data[i]; }

		iterator begin() { return iterator(m_data); }
		iterator end() { return iterator(m_data+n); }
		reverseIterator rbegin() { return reverseIterator(m_data+n-1); }
		reverseIterator rend() { return reverseIterator(m_data-1); }
		Reverse<Array> reverse() { return Reverse<Array>(*this); }
};


#endif
