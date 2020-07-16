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

#define SWIZZLE_2_2\
	SWIZZLE(x, x)\
	SWIZZLE(y, x)\
	SWIZZLE(x, y)\
	SWIZZLE(y, y)

#define SWIZZLE_2_3\
	SWIZZLE(x, x, x)\
	SWIZZLE(y, x, x)\
	SWIZZLE(x, y, x)\
	SWIZZLE(y, y, x)\
	SWIZZLE(x, x, y)\
	SWIZZLE(y, x, y)\
	SWIZZLE(x, y, y)\
	SWIZZLE(y, y, y)

#define SWIZZLE_3_2\
	SWIZZLE(x, x)\
	SWIZZLE(y, x)\
	SWIZZLE(z, x)\
	SWIZZLE(x, y)\
	SWIZZLE(y, y)\
	SWIZZLE(z, y)\
	SWIZZLE(x, z)\
	SWIZZLE(y, z)\
	SWIZZLE(z, z)

#define SWIZZLE_3_3\
	SWIZZLE(x, x, x)\
	SWIZZLE(y, x, x)\
	SWIZZLE(z, x, x)\
	SWIZZLE(x, y, x)\
	SWIZZLE(y, y, x)\
	SWIZZLE(z, y, x)\
	SWIZZLE(x, z, x)\
	SWIZZLE(y, z, x)\
	SWIZZLE(z, z, x)\
	SWIZZLE(x, x, y)\
	SWIZZLE(y, x, y)\
	SWIZZLE(z, x, y)\
	SWIZZLE(x, y, y)\
	SWIZZLE(y, y, y)\
	SWIZZLE(z, y, y)\
	SWIZZLE(x, z, y)\
	SWIZZLE(y, z, y)\
	SWIZZLE(z, z, y)\
	SWIZZLE(x, x, z)\
	SWIZZLE(y, x, z)\
	SWIZZLE(z, x, z)\
	SWIZZLE(x, y, z)\
	SWIZZLE(y, y, z)\
	SWIZZLE(z, y, z)\
	SWIZZLE(x, z, z)\
	SWIZZLE(y, z, z)\
	SWIZZLE(z, z, z)
