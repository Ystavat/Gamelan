#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "vector.h"


#define SELF_OP_MAT(n, op) _SELF_OP_MAT(Matrix ## n, n, op)
#define _SELF_OP_MAT(type, n, op)\
	template<typename U>\
	inline type<T>& operator op(const type<U>& m) {\
		lines[0] op static_cast<T>(m[0]);\
		lines[1] op static_cast<T>(m[1]);\
		DO_IF_3 ## n (lines[2] op static_cast<T>(m[2]));\
		DO_IF_4 ## n (lines[3] op static_cast<T>(m[3]));\
		return *this; }\
	template<typename U>\
	inline type<T>& operator op(U scalar) {\
		lines[0] op static_cast<T>(scalar);\
		lines[1] op static_cast<T>(scalar);\
		DO_IF_3 ## n (lines[2] op static_cast<T>(scalar));\
		DO_IF_4 ## n (lines[3] op static_cast<T>(scalar));\
		return *this; }

#define UNARY_OP_MAT(n, op) _UNARY_OP_MAT(Matrix ## n, n, op)
#define _UNARY_OP_MAT(type, n, op)\
	template<typename T>\
	inline type<T> operator op(const type<T>& m) {\
		return type<T>(\
			op m[0], op m[1]\
			DO_IF_3 ## n (COMMA op m[2])\
			DO_IF_4 ## n (COMMA op m[2])); }

#define BINARY_OP_MAT(n, op) _BINARY_OP_MAT(Matrix ## n, n, op)
#define _BINARY_OP_MAT(type, n, op)\
	template<typename T>\
	inline type<T> operator op(const type<T>& m1, const type<T>& m2) {\
		return type<T>(\
			m1[0] op m2[0], m1[1] op m2[1]\
			DO_IF_3 ## n (COMMA m1[2] op m2[2])\
			DO_IF_4 ## n (COMMA m1[3] op m2[3])); }\
	template<typename T, typename U>\
	inline type<T> operator op(const type<T>& m, U scalar) {\
		return type<T>(\
			m[0] op static_cast<T>(scalar), m[1] op static_cast<T>(scalar)\
			DO_IF_3 ## n (COMMA m[2] op static_cast<T>(scalar))\
			DO_IF_4 ## n (COMMA m[3] op static_cast<T>(scalar))); }\
	template<typename T, typename U>\
	inline type<T> operator op(U scalar, const type<T>& m) {\
		return type<T>(\
			static_cast<T>(scalar) op m[0], static_cast<T>(scalar) op m[1]\
			DO_IF_3 ## n (COMMA static_cast<T>(scalar) op m[2])\
			DO_IF_4 ## n (COMMA static_cast<T>(scalar) op m[3])); }

#define ALL_SELF_OP_MAT(n)\
	SELF_OP_MAT(n, +=)\
	SELF_OP_MAT(n, -=)\
	SELF_OP_MAT(n, *=)\
	SELF_OP_MAT(n, /=)\
	SELF_OP_MAT(n, %=)\
	SELF_OP_MAT(n, &=)\
	SELF_OP_MAT(n, |=)\
	SELF_OP_MAT(n, ^=)\
	SELF_OP_MAT(n, <<=)\
	SELF_OP_MAT(n, >>=)\
	inline vec& operator[](const size_t i) { return lines[i]; }\
	inline const vec& operator[](const size_t i) const { return lines[i]; }\
	inline T* raw() { return (T*)lines; }
#define ALL_UNARY_OP_MAT(n)\
	UNARY_OP_MAT(n, +)\
	UNARY_OP_MAT(n, -)\
	UNARY_OP_MAT(n, ~)
#define ALL_BINARY_OP_MAT(n)\
	BINARY_OP_MAT(n, +)\
	BINARY_OP_MAT(n, -)\
	BINARY_OP_MAT(n, *)\
	BINARY_OP_MAT(n, /)\
	BINARY_OP_MAT(n, %)\
	BINARY_OP_MAT(n, &)\
	BINARY_OP_MAT(n, |)\
	BINARY_OP_MAT(n, ^)\
	BINARY_OP_MAT(n, <<)\
	BINARY_OP_MAT(n, >>)\
	template<typename T>\
	std::ostream& operator<<(std::ostream& out, Matrix ## n<T>& m) { return out\
	<< m[0] << std::endl\
	<< m[1] << std::endl\
	DO_IF_3 ## n (<< m[2] << std::endl)\
	DO_IF_4 ## n (<< m[3] << std::endl); }


template<typename T>
struct Matrix2 {
	typedef Vector2<T> vec;
	private:
		vec lines[2];

	public:
		Matrix2(): lines{ vec(1, 0), vec(0, 1) } {}
		Matrix2(T scalar): lines{ vec(scalar), vec(scalar) } {}
		Matrix2(T x1, T y1, T x2, T y2): lines{ vec(x1, y1), vec(x2, y2) } {}
		Matrix2(const vec& v1, const vec& v2): lines{ vec(v1), vec(v2) } {}

		ALL_SELF_OP_MAT(2);
};
ALL_UNARY_OP_MAT(2);
ALL_BINARY_OP_MAT(2);


template<typename T>
struct Matrix3 {
	typedef Vector3<T> vec;
	private:
		vec lines[3];

	public:
		Matrix3(): lines{ vec(1, 0, 0), vec(0, 1, 0), vec(0, 0, 1) } {}
		Matrix3(T scalar): lines{ vec(scalar), vec(scalar), vec(scalar) } {}
		Matrix3(T x1, T y1, T z1, T x2, T y2, T z2, T x3, T y3, T z3): lines{ vec(x1, y1, z1), vec(x2, y2, z2), vec(x3, y3, z3) } {}
		Matrix3(const vec& v1, const vec& v2, const vec& v3): lines{ vec(v1), vec(v2), vec(v3) } {}

		ALL_SELF_OP_MAT(3);
};
ALL_UNARY_OP_MAT(3);
ALL_BINARY_OP_MAT(3);


template<typename T>
struct Matrix4 {
	typedef Vector4<T> vec;
	private:
		vec lines[4];

	public:
		Matrix4(): lines{ vec(1, 0, 0, 0), vec(0, 1, 0, 0), vec(0, 0, 1, 0), vec(0, 0, 0, 1) } {}
		Matrix4(T scalar): lines{ vec(scalar), vec(scalar), vec(scalar), vec(scalar) } {}
		Matrix4(T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3, T x4, T y4, T z4, T w4): lines{ vec(x1, y1, z1, w1), vec(x2, y2, z2, w2), vec(x3, y3, z3, w3), vec(x4, y4, z4, w4) } {}
		Matrix4(const vec& v1, const vec& v2, const vec& v3, const vec& v4): lines{ vec(v1), vec(v2), vec(v3), vec(v4) } {}

		ALL_SELF_OP_MAT(4);
};
ALL_UNARY_OP_MAT(4);
ALL_BINARY_OP_MAT(4);


typedef Matrix2<float> mat2;
typedef Matrix3<float> mat3;
typedef Matrix4<float> mat4;


#endif
