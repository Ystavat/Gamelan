#include "layer.h"


void LayerStack::insertBegin(Layer& layer) {
	layer.onAttach();
	DynamicArray::insert(layer, 0);
}
void LayerStack::insertEnd(Layer& layer) {
	layer.onAttach();
	DynamicArray::insert(layer, this->m_count);
}
Layer LayerStack::popBegin() {
	this->m_data[0].onDettach();
	return DynamicArray::remove(0);
}
Layer LayerStack::popEnd() {
	this->m_data[this->m_count-1].onDettach();
	return DynamicArray::remove(this->m_count-1);
}

void LayerStack::onUpdate(float deltaTime) {
	for (Layer& layer : *this) {
		layer.onUpdate(deltaTime);
	}
}
void LayerStack::onEvent(Event& event) {
	for (Layer& layer : *this) {
		if (event.m_handled) break;
		layer.onEvent(event);
	}
}
