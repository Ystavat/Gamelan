#ifndef __TESTLAYER_H__
#define __TESTLAYER_H__

#include "gamelan.h"


class TestLayer : public Layer {
	private:
		OrthographicCameraController camera = { 8/6.f };
		Texture* texture;
		Shader* shader;
		Shader* shaderPass;
		VertexArray* vao_p;
		VertexBuffer<lyt::Float2, lyt::Float2>* vbo_p;
		IndexBuffer* ibo_p;
		FrameBuffer* fb;

	public:
		TestLayer(float a) {}
		virtual void onAttach() {
			PROFILE_FUNCTION();

			RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);

			texture = new Texture("../Assets/Images/img.png", 4);
			texture->print();
			fb = new FrameBuffer(0, 100, 100);
			texture->bind(1);

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
			shaderPass = Shader::fromFile("../Assets/Shaders/passVS.shader", "../Assets/Shaders/passFS.shader");
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

			fb->bind();
			RenderingContext::setClearColor(0.0, 1.0, 1.0, 1.0);
			RenderingContext::clear();
			vao_p->bind();
			shader->bind();
			shader->set("u_proj", camera.getCamera().getViewProjection());
			shader->set("u_texture", 1);
			RenderingContext::drawIndexed(6);
			fb->unbind();

			Application::get().autoViewPort();
			RenderingContext::setClearColor(0.0, 1.0, 0.0, 1.0);
			RenderingContext::clear();
			shaderPass->bind();
			shaderPass->set("u_texture", 0);
			fb->pass();
		}
};


#endif
