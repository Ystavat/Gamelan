#include "core.h"
#include "Renderer/OpenGL/shader.h"
#include "Window/window.h"


int main() {
	LOG_INIT();
	CORE_LOGGER(setPrompt("[%f(%l)]%N: "));
	APP_LOGGER(setPrompt("[%f(%l)]%N: "));
	PROFILE_SESSION();
	
	Window window(800, 600, "test");
	RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);

	unsigned int stride = 5*sizeof(float);
	float vertices[4*5] = {
		-1.0, -1.0, 1.0, 0.0, 0.0,
		 1.0, -1.0, 0.0, 1.0, 0.0,
		 1.0,  1.0, 0.0, 0.0, 1.0,
		-1.0,  1.0, 1.0, 1.0, 0.0
	};

	unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

	unsigned int vbo;
	glGenVertexArrays(1, &vbo);
	glBindVertexArray(vbo);

	unsigned int abo;
	glGenBuffers(1, &abo);
	glBindBuffer(GL_ARRAY_BUFFER, abo);
	glBufferData(GL_ARRAY_BUFFER, 4*stride, vertices, GL_STATIC_DRAW);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const void*)(uintptr_t)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (const void*)(uintptr_t)(2*sizeof(float)));

	Shader* shader = Shader::fromFile("Assets/Shaders/basicVS.shader", "Assets/Shaders/basicFS.shader");
	shader->bind();

	while(!window.shouldClose()) {
		window.onUpdate();
		window.clear();
		RenderingContext::drawIndexed(6);
	}
	
	delete shader;
	LOG_TERMINATE();
	exit(EXIT_SUCCESS);
}
