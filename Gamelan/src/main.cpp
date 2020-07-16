#include "core.h"
#include "Window/window.h"
#include "Renderer/OpenGL/shader.h"
#include "Renderer/OpenGL/texture.h"
#include "Renderer/OpenGL/layout.h"


int main() {

	LOG_INIT();
	CORE_LOGGER(setPrompt("[%f(%l)]%N: "));
	APP_LOGGER(setPrompt("[%f(%l)]%N: "));
	PROFILE_SESSION();

	Window window(800, 600, "test");
	RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);

	Texture texture("Assets/Images/img.png", 4);
	texture.print();

	float vertices[4*4] = {
		-1.0, -1.0, 0.0, 0.0,
		 1.0, -1.0, 1.0, 0.0,
		 1.0,  1.0, 1.0, 1.0,
		-1.0,  1.0, 0.0, 1.0
	};
	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	Layout layout({{Float2}, {Float2}});

	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uint32_t abo;
	glGenBuffers(1, &abo);
	glBindBuffer(GL_ARRAY_BUFFER, abo);
	glBufferData(GL_ARRAY_BUFFER, 4*layout.getStride(), vertices, GL_STATIC_DRAW);

	uint32_t ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), indices, GL_STATIC_DRAW);

	layout.bind();

	Shader* shader = Shader::fromFile("Assets/Shaders/texVS.shader", "Assets/Shaders/texFS.shader");
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
