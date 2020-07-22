#include "layer.h"


LayerStack::~LayerStack() {
	for (Layer* layer : *this) {
		delete layer;
	}
}

void LayerStack::insertBegin(Layer* layer) {
	layer->onAttach();
	DynamicArray::insert(layer, 0);
}
void LayerStack::insertEnd(Layer* layer) {
	layer->onAttach();
	DynamicArray::insert(layer, m_count);
}
void LayerStack::pop(Layer* layer) {
	size_t index = DynamicArray::find(layer);
	if (index < m_count) {
		pop(index);
	}
}
void LayerStack::pop(size_t i) {
	m_data[i]->onDettach();
	DynamicArray::remove(i);
}

void LayerStack::onUpdate(float deltaTime) {
	for (Layer* layer : reverse()) {
		layer->onUpdate(deltaTime);
	}
}
void LayerStack::onEvent(Event& event) {
	for (Layer* layer : *this) {
		if (event.m_handled) break;
		layer->onEvent(event);
	}
}
