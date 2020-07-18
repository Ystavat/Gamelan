template<typename... T>
struct tmp {};
template<typename Tl1, typename Tl2, size_t n, typename Tl3>
struct vertCons;

template<typename... T1, typename... T2, class C0>
struct vertCons<tmp<T1...>, tmp<T2...>, 0, tmp<C0>> {
	void get(T1... args) {}
	void get(T2... args, typename C0::type arg) {}};

template<typename... T1, typename... T2, class C0, class C1, class... Ct>
struct vertCons<tmp<T1...>, tmp<T2...>, 0, tmp<C0, C1, Ct...>>: public vertCons<tmp<T1...>, tmp<typename C0::type, T2...>, C1::count, tmp<C1, Ct...>> {};

template<typename... T1, typename... T2, size_t n, class C0, class... Ct>
struct vertCons<tmp<T1...>, tmp<T2...>, n, tmp<C0, Ct...>>: public vertCons<tmp<T1..., typename C0::base>, tmp<T2...>, n-1, tmp<C0, Ct...>> {};
