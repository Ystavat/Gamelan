#include "gamelan.h"


class TestLayer : public Layer {
	private:
		OrthographicCameraController camera = { 8/6.f };
		Texture* texture;
		Shader* shader;
		VertexArray* vao_p;
		VertexBuffer<lyt::Float2, lyt::Float2>* vbo_p;
		IndexBuffer* ibo_p;

	public:
		TestLayer(float a) {
			PROFILE_FUNCTION();
			camera.getCamera().setRotation(a);
			camera.getCamera().setPosition({1, 0, 0});
			CORE_WARN(a);
		}
		virtual void onAttach() {
			PROFILE_FUNCTION();

			RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);

			texture = new Texture("../Assets/Images/img.png", 4);
			texture->print();

			vao_p = new VertexArray();

			vbo_p = new VertexBuffer<lyt::Float2, lyt::Float2>(4);
			VertexBuffer<lyt::Float2, lyt::Float2>& vbo = *vbo_p;
			vbo[0].set(-1.0, -1.0, 0.0, 0.0);
			vbo[1].set( 1.0, -1.0, 1.0, 0.0);
			vbo[2].set( 1.0,  1.0, 1.0, 1.0);
			vbo[3].set(-1.0,  1.0, 0.0, 1.0);
			vbo.bind();
			vbo.update();
			vbo.applyLayout();

			uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
			ibo_p = new IndexBuffer(indices, 6);

			vao_p->unbind();
			vbo_p->unbind();
			ibo_p->unbind();

			shader = Shader::fromFile("../Assets/Shaders/texVS.shader", "../Assets/Shaders/texFS.shader");
			//shader = Shader::fromFile("../Assets/Shaders/basicVS.shader", "../Assets/Shaders/basicFS.shader");
		}
		virtual ~TestLayer() override {
			delete texture;
			delete shader;
			delete vao_p;
			delete vbo_p;
			delete ibo_p;
		}

		virtual void onEvent(Event& event) override {
			//dispatch<KeyPressEvent>(event, [](KeyPressEvent& e) { APP_ERROR(e.getKeyCode()); return true; });
			camera.onEvent(event);
		}

		virtual void onUpdate(float dt) override {
			PROFILE_FUNCTION();
			
			camera.onUpdate(dt);
			if (Inputs::isKeyPressed(256)) {
				Application::get().shutdown();
			}

			vao_p->bind();
			shader->bind();
			shader->set("u_proj", camera.getCamera().getViewProjection());
			RenderingContext::drawIndexed(6);
		}
};
