#ifndef __SHADER_H__
#define __SHADER_H__

#include "core.h"
#include <GL/glew.h>
#include "utils/file.h"

class Shader {
	private:
		unsigned int m_id;
	public:
		Shader(const char* vertexShader, const char* fragmentShader);

		~Shader();

		static Shader* fromFile(const char* vertexFile, const char* fragmentFile);

		static unsigned int compile(unsigned int type, const char* source);

		unsigned int getId();

		void bind();
};


#endif