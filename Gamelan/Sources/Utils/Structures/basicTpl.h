#ifndef __BASIC_TPL_H__
#define __BASIC_TPL_H__


template<typename... n>
struct types{};
template<size_t... n>
struct seq {};
template<size_t n0, size_t ...nt>
struct gen_index: public gen_index<n0-1, n0-1, nt...> {};
template<size_t... n>
struct gen_index<0, n...>{ typedef seq<n...> type; };


#endif
