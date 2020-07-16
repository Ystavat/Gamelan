#include "gamelan.h"


class Sandbox : public Application {
	private:
		Texture* texture;
		Shader* shader;

	public:
		Sandbox(): Application(800, 600, "Sandbox") {
			RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);

			texture = new Texture("Assets/Images/img.png", 4);
			texture->print();

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

			shader = Shader::fromFile("Assets/Shaders/texVS.shader", "Assets/Shaders/texFS.shader");
		}
		~Sandbox() {
			delete texture;
			delete shader;
		}

		virtual void onEvent(Event& event) override {
			CORE_TRACE(event.getType());
		}

		virtual void onUpdate() override {
			shader->bind();
			RenderingContext::drawIndexed(6);
		}
};
GAMELAN_USE(Sandbox);
