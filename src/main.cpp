#include "core.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/OpenGL/shader.h"
#include "Window/Event/eventCallback.h"


void error_callback(int code, const char* description) {
	CORE_ERROR("code: ", code, "\n", description);
}

int main() {
	LOG_INIT();
	CORE_LOGGER(setPrompt("[%f(%l)]%N: "));
	APP_LOGGER(setPrompt("[%f(%l)]%N: "));
	PROFILE_SESSION();

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "test", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit()!=GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	CORE_INFO(glGetString(GL_VERSION));
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glViewport(0, 0, width, height);

	GLFWHook hook;
	glfwSetWindowUserPointer(window, &hook);
	setWindowEventsCallback(window);

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

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
	}
	
	delete shader;
	LOG_TERMINATE();
	exit(EXIT_SUCCESS);
}
