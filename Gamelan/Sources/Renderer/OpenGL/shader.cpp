#include "shader.h"


Shader::Shader(const char* vertexShader, const char* fragmentShader) {
	uint32_t program = glCreateProgram();
	uint32_t vs = Shader::compile(GL_VERTEX_SHADER, vertexShader);
	uint32_t fs = Shader::compile(GL_FRAGMENT_SHADER, fragmentShader);
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

uint32_t Shader::compile(uint32_t type, const char* source) {
	uint32_t shader = glCreateShader(type);
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

uint32_t Shader::getId() { return m_id; }

void Shader::bind() { glUseProgram(m_id); }

GLint Shader::getLocation(const char* name) { return glGetUniformLocation(m_id, name); }

void Shader::set(const char* name, int value) { glUniform1i(getLocation(name), value); }
void Shader::set(const char* name, int* value, uint32_t count) { glUniform1iv(getLocation(name), count, value); }
void Shader::set(const char* name, float value) { glUniform1f(getLocation(name), value); }
void Shader::set(const char* name, const vec2& value) { glUniform2f(getLocation(name), value.x, value.y); }
void Shader::set(const char* name, const vec3& value) { glUniform3f(getLocation(name), value.x, value.y, value.z); }
void Shader::set(const char* name, const vec4& value) { glUniform4f(getLocation(name), value.x, value.y, value.z, value.w); }
void Shader::set(const char* name, const mat2& value) { glUniformMatrix2fv(getLocation(name), 1, GL_FALSE, value.raw()); }
void Shader::set(const char* name, const mat3& value) { glUniformMatrix3fv(getLocation(name), 1, GL_FALSE, value.raw()); }
void Shader::set(const char* name, const mat4& value) { glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, value.raw()); }
