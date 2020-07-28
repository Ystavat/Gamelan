#include "gamelan.h"
#include "testLayer.h"


class Sandbox : public Application {
	public:
		Sandbox(): Application(800, 600, "Sandbox") {
			PROFILE_FUNCTION();

			m_layerStack.insertBegin(new TestLayer(0.5));
		}
};

GAMELAN_USE(Sandbox);
