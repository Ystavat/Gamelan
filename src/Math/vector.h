#ifndef __MATH_H__
#define __MATH_H__

#include "swizzle.h"


#define DO_IF_32(x)
#define DO_IF_33(x) x
#define DO_IF_34(x) x
#define DO_IF_42(x)
#define DO_IF_43(x)
#define DO_IF_44(x) x
#define COMMA ,

#define SELF_OP_VEC(n, op) _SELF_OP_VEC(Vector ## n, n, op)
#define _SELF_OP_VEC(type, n, op)\
	template<typename U>\
	inline type<T>& operator op(const type<U>& v) {\
		x op static_cast<T>(v.x);\
		y op static_cast<T>(v.y);\
		DO_IF_3 ## n (z op static_cast<T>(v.z));\
		DO_IF_4 ## n (w op static_cast<T>(v.w));\
		return *this; }\
	template<typename U>\
	inline type<T>& operator op(U scalar) {\
		x op static_cast<T>(scalar);\
		y op static_cast<T>(scalar);\
		DO_IF_3 ## n (z op static_cast<T>(scalar));\
		DO_IF_4 ## n (w op static_cast<T>(scalar));\
		return *this; }

#define UNARY_OP_VEC(n, op) _UNARY_OP_VEC(Vector ## n, n, op)
#define _UNARY_OP_VEC(type, n, op)\
	template<typename T>\
	inline type<T> operator op(const type<T>& v) {\
		return type<T>(\
			op v.x, op v.y\
			DO_IF_3 ## n (COMMA op v.z)\
			DO_IF_4 ## n (COMMA op v.z)); }

#define BINARY_OP_VEC(n, op) _BINARY_OP_VEC(Vector ## n, n, op)
#define _BINARY_OP_VEC(type, n, op)\
	template<typename T>\
	inline type<T> operator op(const type<T>& v1, const type<T>& v2) {\
		return type<T>(\
			v1.x op v2.x, v1.y op v2.y\
			DO_IF_3 ## n (COMMA v1.z op v2.z)\
			DO_IF_4 ## n (COMMA v1.w op v2.w)); }\
	template<typename T, typename U>\
	inline type<T> operator op(const type<T>& v, U scalar) {\
		return type<T>(\
			v.x op static_cast<T>(scalar), v.y op static_cast<T>(scalar)\
			DO_IF_3 ## n (COMMA v.z op static_cast<T>(scalar))\
			DO_IF_4 ## n (COMMA v.w op static_cast<T>(scalar))); }\
	template<typename T, typename U>\
	inline type<T> operator op(U scalar, const type<T>& v) {\
		return type<T>(\
			static_cast<T>(scalar) op v.x, static_cast<T>(scalar) op v.y\
			DO_IF_3 ## n (COMMA static_cast<T>(scalar) op v.z)\
			DO_IF_4 ## n (COMMA static_cast<T>(scalar) op v.w)); }

#define ALL_SELF_OP_VEC(n)\
	SELF_OP_VEC(n, +=);\
	SELF_OP_VEC(n, -=);\
	SELF_OP_VEC(n, *=);\
	SELF_OP_VEC(n, /=);\
	SELF_OP_VEC(n, %=);\
	SELF_OP_VEC(n, &=);\
	SELF_OP_VEC(n, |=);\
	SELF_OP_VEC(n, ^=);\
	SELF_OP_VEC(n, <<=);\
	SELF_OP_VEC(n, >>=)
#define ALL_UNARY_OP_VEC(n)\
	UNARY_OP_VEC(n, +);\
	UNARY_OP_VEC(n, -);\
	UNARY_OP_VEC(n, ~)
#define ALL_BINARY_OP_VEC(n)\
	BINARY_OP_VEC(n, +);\
	BINARY_OP_VEC(n, -);\
	BINARY_OP_VEC(n, *);\
	BINARY_OP_VEC(n, /);\
	BINARY_OP_VEC(n, %);\
	BINARY_OP_VEC(n, &);\
	BINARY_OP_VEC(n, |);\
	BINARY_OP_VEC(n, ^);\
	BINARY_OP_VEC(n, <<);\
	BINARY_OP_VEC(n, >>)


template<typename T>
struct Vector2 {
	union {
		struct { T x, y; };
		struct { T s, t; };
		struct { T u, v; };
	};

	Vector2(T scalar): x(scalar), y(scalar) {}
	Vector2(T _x, T _y): x(_x), y(_y) {}
	
	ALL_SELF_OP_VEC(2);

	SWIZZLE_2_2
	SWIZZLE_2_3
};
ALL_UNARY_OP_VEC(2);
ALL_BINARY_OP_VEC(2);

template<typename T>
struct Vector3 {
	union {
		struct { T x, y, z; };
		struct { T s, t, p; };
		struct { T r, g, b; };
	};

	Vector3(T scalar): x(scalar), y(scalar), z(scalar) {}
	Vector3(T _x, T _y, T _z): x(_x), y(_y), z(_z) {}
	
	ALL_SELF_OP_VEC(3);

	SWIZZLE_3_2
	SWIZZLE_3_3
};
ALL_UNARY_OP_VEC(3);
ALL_BINARY_OP_VEC(3);


typedef Vector2<float> vec2;
typedef Vector3<float> vec3;


#endif
