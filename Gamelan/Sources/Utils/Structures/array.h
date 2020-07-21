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
		~Array() {}

		constexpr size_t getCount() { return n; }
		T* raw() { return m_data; }

		T& operator[](size_t i) { return m_data[i]; }
		const T& operator[](size_t i) const { return m_data[i]; }

		iterator begin() { return iterator(m_data); }
		iterator end() { return iterator(m_data+n); }
		reverseIterator rbegin() { return reverseIterator(m_data+n-1); }
		reverseIterator rend() { return reverseIterator(m_data-1); }
		Reverse<Array> reverse() { return Reverse<Array>(*this); }
};

template<typename T, size_t n>
std::ostream& operator<<(std::ostream out, Array<T, n>& array) {
	out << "[ ";
	for (size_t i ; i < n ; i++) {
		out << array[i];
		if (i < n-1) {
			out << " ,";
		}
	}
	return out << " ]";
}


template<typename T, size_t slack=0>
class DynamicArray {
	protected:
		typedef BasicIterator<T> iterator;
		typedef BasicReverseIterator<T> reverseIterator;
		size_t m_count;
		size_t m_countM;
		T* m_data;

	public:
		DynamicArray(): m_count(0), m_countM(slack) { m_data = new T[m_countM]; }
		~DynamicArray() { delete[] m_data; }

		size_t getCount() { return m_count; }
		size_t getCountM() { return m_countM; }
		bool isEmpty() { return m_count == 0; }
		T* raw() { return m_data; }

		T& operator[](size_t i) { return m_data[i]; }
		const T& operator[](size_t i) const { return m_data[i]; }

		void insert(T&& e, size_t i) { insert(e, i); }
		void insert(T& e, size_t i) {
			if (m_count == m_countM) {
				m_countM = m_count+slack+1;
				T* tmp = new T[m_countM];
				size_t j = 0;
				for (; j < i ; j++)
					tmp[j] = m_data[j];
				tmp[j] = e;
				for (; j < m_count ; j++) {
					tmp[j+1] = m_data[j];
				}
				delete[] m_data;
				m_data = tmp;
			} else {
				for (size_t j = m_count ; j > i ; j--) {
					m_data[j] = m_data[j-1];
				}
				m_data[i] = e;
			}
			m_count++;
		}

		T remove(size_t i) {
			T& e = m_data[i];
			if (m_countM > m_count+2*slack-1) {
				m_countM = m_count+slack-1;
				T* tmp = new T[m_countM];
				size_t j = 0;
				for (; j < i ; j++)
					tmp[j] = m_data[j];
				for (j++ ; j < m_count ; j++)
					tmp[j-1] = m_data[j];
				delete[] m_data;
				m_data = tmp;
			} else {
				for (size_t j = i ; j < m_count-1 ; j++) {
					m_data[j] = m_data[j+1];
				}
			}
			m_count--;
			return e;
		}

		iterator begin() { return iterator(m_data); }
		iterator end() { return iterator(m_data+m_count); }
		reverseIterator rbegin() { return reverseIterator(m_data+m_count-1); }
		reverseIterator rend() { return reverseIterator(m_data-1); }
		Reverse<DynamicArray> reverse() { return Reverse<DynamicArray>(*this); }
};

template<typename T, size_t slack>
std::ostream& operator<<(std::ostream& out, DynamicArray<T, slack>& array) {
	const size_t count = array.getCount();
	out << "(" << array.getCountM()-2*slack << ", " << count << ", " << array.getCountM() << ")[ ";
	for (size_t i ; i < count ; i++) {
		out << array[i];
		if (i < count-1) {
			out << " ,";
		}
	}
	return out << " ]";
}


#endif
