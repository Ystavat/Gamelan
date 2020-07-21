#ifndef __LAYER_H__
#define __LAYER_H__

#include "core.h"
#include "Window/Event/event.h"

class Layer {
	protected:
		virtual void onAttach() {}
		virtual void onDettach() {}
		virtual void onUpdate(float deltaTime) {}
		virtual void onEvent(Event& event) {}

	public:
		Layer() {}
		~Layer() {}
};

class LayerStack: LinkedList<Layer> {

};


#endif
