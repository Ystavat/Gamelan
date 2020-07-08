#include "shader.h"


Shader::Shader(const char* vertexShader, const char* fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = Shader::compile(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = Shader::compile(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	m_id = program;
}

Shader::~Shader() { glDeleteProgram(m_id); }

Shader* Shader::fromFile(const char* vertexFile, const char* fragmentFile) {
	const char* vertexShader = readFile(vertexFile);
	const char* fragmentShader = readFile(fragmentFile);
	Shader* shader = new Shader(vertexShader, fragmentShader);
	delete[] vertexShader;
	delete[] fragmentShader;
	return shader;
}

unsigned int Shader::compile(unsigned int type, const char* source) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length*sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		CORE_ERROR("Failed to compile ", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", " shader\n", message);
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

unsigned int Shader::getId() { return m_id; }

void Shader::bind() { glUseProgram(m_id); }
