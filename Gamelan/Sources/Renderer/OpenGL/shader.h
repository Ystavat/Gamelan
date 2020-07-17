#ifndef __SHADER_H__
#define __SHADER_H__

#include "core.h"
#include <GL/glew.h>
#include "Utils/file.h"


class Shader {
	private:
		uint32_t m_id;

	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		~Shader();

		static Shader* fromFile(const char* vertexFile, const char* fragmentFile);

		static uint32_t compile(uint32_t type, const char* source);

		uint32_t getId();

		void bind();
};


#endif
