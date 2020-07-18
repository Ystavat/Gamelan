#ifndef __TUPLE_H__


template<size_t i, typename T>
struct Base {
	private:
		T element;
	public:
		T& get() { return element; }
		const T& get() const { return element; }
};

template<size_t i, typename... Elements>
struct _Tuple;

template<size_t i>
struct _Tuple<i> {};

template<size_t i, typename Head, typename... Tail>
struct _Tuple<i, Head, Tail...>: public _Tuple<i+1, Tail...>, private Base<i, Head> {
	_Tuple() {}
	Head& get() { return Base<i, Head>::get(); }
	const Head& get() const { return Base<i, Head>::get(); }
};

template<size_t i, typename Head, typename... Tail>
Head& get(_Tuple<i, Head, Tail...>& t) { return t.get(); }

template<typename... Elements>
struct Tuple: public _Tuple<0, Elements...> {};


#endif
