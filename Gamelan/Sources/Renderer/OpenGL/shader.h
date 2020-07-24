#ifndef __SHADER_H__
#define __SHADER_H__

#include "core.h"
#include <GL/glew.h>
#include "Utils/file.h"


class Shader {
	private:
		uint32_t m_id;

		static uint32_t compile(uint32_t type, const char* source);

	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		static Shader* fromFile(const char* vertexFile, const char* fragmentFile);
		~Shader();

		void bind();

		uint32_t getId();
		GLint getLocation(const char* name);

		void set(const char* name, int value);
		void set(const char* name, int* values, uint32_t count);
		void set(const char* name, float value);
		void set(const char* name, const vec2& value);
		void set(const char* name, const vec3& value);
		void set(const char* name, const vec4& value);
		void set(const char* name, const mat2& value);
		void set(const char* name, const mat3& value);
		void set(const char* name, const mat4& value);
};


#endif
