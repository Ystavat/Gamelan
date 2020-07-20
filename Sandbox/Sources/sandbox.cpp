#include "gamelan.h"


class Sandbox : public Application {
	private:
		Texture* texture; 
		Shader* shader;
		OrthographicCamera camera = {-8/6.,8/6.,-1.,1};
		IndexBuffer* ibo;
		VertexArray* vao;

	public:
		Sandbox(): Application(800, 600, "Sandbox") {
			PROFILE_FUNCTION();

			RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);

			texture = new Texture("../Assets/Images/img.png", 4);
			texture->print();

			CORE_DEBUG(camera.getProjection());

			VertexBuffer<lyt::Float2, lyt::Float2> vbo(4);
			//vbo[0].set({-1.0, -1.0}, {0.0, 0.0});
			vbo[0].set(-1.0, -1.0, 0.0, 0.0);
			get<0>(vbo[1]) = { 1.0, -1.0};
			get<1>(vbo[1]) = { 1.0,  0.0};
			get<0>(vbo[2]) = { 1.0,  1.0};
			get<1>(vbo[2]) = { 1.0,  1.0};
			get<0>(vbo[3]) = {-1.0,  1.0};
			get<1>(vbo[3]) = { 0.0,  1.0};
			
			uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

			/*uint32_t vao;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);*/
			vao = new VertexArray();

			vbo.bind();
			vbo.update();

			/*uint32_t ibo;
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), indices, GL_STATIC_DRAW);
			
			vbo.applyLayout();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), indices, GL_STATIC_DRAW);*/
			ibo = new IndexBuffer(indices, 6);

			layout.bind();

			shader = Shader::fromFile("../Assets/Shaders/texVS.shader", "../Assets/Shaders/texFS.shader");
			//shader = Shader::fromFile("../Assets/Shaders/basicVS.shader", "../Assets/Shaders/basicFS.shader");
		}
		~Sandbox() {
			delete texture;
			delete shader;
			delete ibo;
			delete vao;
		}

		virtual void onEvent(Event& event) override {
			APP_TRACE(event.getType());
		}

		virtual void onUpdate(float deltaTime) override {
			PROFILE_FUNCTION();

			shader->bind();
			shader->set("u_proj", camera.getProjection());
			RenderingContext::drawIndexed(6);
		}
};

GAMELAN_USE(Sandbox);
