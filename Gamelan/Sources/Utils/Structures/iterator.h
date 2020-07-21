#ifndef __ITERATOR_H__
#define __ITERATOR_H__


template<typename T>
struct BasicIterator {
	protected:
		T* m_ptr;
	
	public:
		explicit BasicIterator(T* ptr): m_ptr(ptr) {}

		T* getPtr() { return m_ptr; }

		bool operator==(BasicIterator& other) { return m_ptr==other.getPtr(); }
		bool operator!=(BasicIterator& other) { return m_ptr!=other.getPtr(); }
		T* operator++() { return m_ptr++; }
		T* operator--() { return m_ptr--; }
		T& operator*() { return *m_ptr; }
};


template<typename T>
struct BasicReverseIterator: public BasicIterator<T> {
	public:
		explicit BasicReverseIterator(T* ptr): BasicIterator<T>(ptr) {}

		T* operator++() { return this->m_ptr--; }
		T* operator--() { return this->m_ptr++; }
};


template<typename T>
struct Reverse {
	private:
		T& m_iterable;

	public:
		explicit Reverse(T& iterable): m_iterable(iterable) {}

		auto begin() { return m_iterable.rbegin(); }
		auto end() { return m_iterable.rend(); }
};


#endif
