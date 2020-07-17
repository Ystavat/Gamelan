#ifndef __SHADER_H__
#define __SHADER_H__

#include "core.h"
#include <GL/glew.h>
#include "Utils/file.h"
#include "Math/vector.h"


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
		void set(const char* name, vec2& value);
		void set(const char* name, vec3& value);
		void set(const char* name, vec4& value);
};


#endif
