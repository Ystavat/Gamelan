#ifndef __LAYER_H__
#define __LAYER_H__

#include "core.h"
#include "Window/Event/event.h"


class LayerStack;
class Layer {
	friend LayerStack;
	protected:
		virtual void onAttach() {}
		virtual void onDettach() {}
		virtual void onUpdate(float deltaTime) {}
		virtual void onEvent(Event& event) {}

	public:
		Layer() {}
		virtual ~Layer() {}
};

class LayerStack: DynamicArray<Layer*, 1> {
	public:
		LayerStack() {}
		~LayerStack();

		void insert(Layer* layer, size_t i);
		void insertBegin(Layer* layer);
		void insertEnd(Layer* layer);
		void pop(Layer* layer);
		void pop(size_t i);

		void onUpdate(float deltaTime);
		void onEvent(Event& event);
};


#endif
