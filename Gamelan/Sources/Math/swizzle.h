#ifndef __SWIZZLE_H__
#define __SWIZZLE_H__

#include "core.h"


template<typename T>
struct Vector2;
template<typename T>
struct Vector3;
template<typename T>
struct Vector4;


#define SWIZZLE_COUNT(_1, _2, _3, _4, COUNT, ...) SWIZZLE_ ## COUNT
#define SWIZZLE(...) SWIZZLE_COUNT(__VA_ARGS__, 4, 3, 2) (__VA_ARGS__)
#define SWIZZLE_2(E0, E1) Vector2<T> E0 ## E1() { return Vector2<T>(E0, E1); }
#define SWIZZLE_3(E0, E1, E2) Vector3<T> E0 ## E1 ## E2() { return Vector3<T>(E0, E1, E2); }
#define SWIZZLE_4(E0, E1, E2, E3) Vector4<T> E0 ## E1 ## E2 ## E3() { return Vector4<T>(E0, E1, E2, E3); }

#define BRANCH_IF_21(A, B) B
#define BRANCH_IF_22(A, B) A
#define BRANCH_IF_31(A, B) B
#define BRANCH_IF_32(A, B) B
#define BRANCH_IF_33(A, B) A
#define BRANCH_IF_41(A, B) B
#define BRANCH_IF_42(A, B) B
#define BRANCH_IF_43(A, B) B
#define BRANCH_IF_44(A, B) A

#define DO_MUL_1(A, B, C, D) A
#define DO_MUL_2(A, B, C, D) A B
#define DO_MUL_3(A, B, C, D) A B C
#define DO_MUL_4(A, B, C, D) A B C D

#define MUL_1(n, m) BRANCH_IF_ ## n ## 1 (\
	DO_MUL_ ## m (SWIZZLE(x), SWIZZLE(y), SWIZZLE(z), SWIZZLE(w)),\
	DO_MUL_ ## m (MUL_2(n, m, x), MUL_2(n, m, y), MUL_2(n, m, z), MUL_2(n, m, w))\
)
#define MUL_2(n, m, E0) BRANCH_IF_ ## n ## 2 (\
	DO_MUL_ ## m (SWIZZLE(E0, x), SWIZZLE(E0, y), SWIZZLE(E0, z), SWIZZLE(E0, w)),\
	DO_MUL_ ## m (MUL_3(n, m, E0, x), MUL_3(n, m, E0, y), MUL_3(n, m, E0, z), MUL_3(n, m, E0, w))\
)
#define MUL_3(n, m, E0, E1) BRANCH_IF_ ## n ## 3 (\
	DO_MUL_ ## m (SWIZZLE(E0, E1, x), SWIZZLE(E0, E1, y), SWIZZLE(E0, E1, z), SWIZZLE(E0, E1, w)),\
	DO_MUL_ ## m (MUL_4(n, m, E0, E1, x), MUL_4(n, m, E0, E1, y), MUL_4(n, m, E0, E1, z), MUL_4(n, m, E0, E1, w))\
)
#define MUL_4(n, m, E0, E1, E2) BRANCH_IF_ ## n ## 4 (\
	DO_MUL_ ## m (SWIZZLE(E0, E1, E2, x), SWIZZLE(E0, E1, E2, y), SWIZZLE(E0, E1, E2, z), SWIZZLE(E0, E1, E2, w)),\
	DO_MUL_ ## m (MUL_5(n, m, E0, E1, E2, x), MUL_5(n, m, E0, E1, E2, y), MUL_5(n, m, E0, E1, E2, z), MUL_5(n, m, E0, E1, E2, w))\
)

#define ALL_SWIZZLE(m) MUL_1(2, m) MUL_1(3, m) MUL_1(4, m)


#endif
