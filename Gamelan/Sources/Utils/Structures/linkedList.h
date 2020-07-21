#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "iostream"
#include "iterator.h"


template<typename T>
struct ListElement {
	ListElement<T>* previous;
	T element;
	ListElement<T>* next;
	ListElement(T& _element): previous(nullptr), element(_element), next(nullptr) {}
	ListElement(ListElement<T>* _previous, T& _element, ListElement<T>* next): previous(_previous), element(_element), next(next) {}
};


template<typename T>
struct LinkedIterator: public BasicIterator<ListElement<T>> {
	public:
		typedef ListElement<T> type;
		explicit LinkedIterator(type* ptr): BasicIterator<type>(ptr) {}

		type* operator++() { return this->m_ptr = this->m_ptr->next; }
		type* operator--() { return this->m_ptr = this->m_ptr->previous; }
		T& operator*() { return this->m_ptr->element; }
};
template<typename T>
struct LinkedReverseIterator: public LinkedIterator<T> {
	public:
		typedef ListElement<T> type;
		explicit LinkedReverseIterator(type* ptr): LinkedIterator<T>(ptr) {}

		type* operator++() { return this->m_ptr = this->m_ptr->previous; }
		type* operator--() { return this->m_ptr = this->m_ptr->next; }
};


template<typename T>
class LinkedList {
	protected:
		uint32_t m_count;
		ListElement<T>* tail;
		ListElement<T>* head;
		ListElement<T>* current;

	public:
		LinkedList():m_count(0) {
			head = tail = current = nullptr;
		}
		~LinkedList() {
			ListElement<T>* tmp = tail;
			while (tail) {
				tmp = tail->next;
				delete tail;
				tail = tmp;
			}
		}
		void insertAfter(T&& element) { insertAfter(element); }
		void insertAfter(T& element) {
			if (m_count++) {
				current->next = new ListElement<T>(current, element, current->next);
				if (current == head) {
					head = current->next;
				} else {
					current->next->next->previous = current->next;
				}
			} else {
				head = tail = current = new ListElement<T>(element);
			}
		}
		void insertBefore(T&& element) { insertBefore(element); }
		void insertBefore(T& element) {
			if (m_count++) {
				current->previous = new ListElement<T>(current->previous, element, current);
				if (current == tail) {
					tail = current->previous;
				} else {
					current->previous->previous->next = current->previous;
				}
			} else {
				head = tail = current = new ListElement<T>(element);
			}
		}
		void insertBegin(T&& element) { insertBegin(element); }
		void insertBegin(T& element) {
			if (m_count++) {
				tail->previous = new ListElement<T>(nullptr,element,tail);
				tail = tail->previous;
			} else {
				head = tail = current = new ListElement<T>(element);
			}
		}
		void insertEnd(T&& element) { insertEnd(element); }
		void insertEnd(T& element) {
			if (m_count++) {
				head->next = new ListElement<T>(head,element,nullptr);
				head = head->next;
			} else {
				head = tail = current = new ListElement<T>(element);
			}
		}
		T& next() {
			current = current->next;
			return current->element;
		}
		T& previous() {
			current = current->previous;
			return current->element;
		}
		T& popBegin() {
			ListElement<T>* tmp = tail;
			T& popped = tmp->element;
			tail = tail->next;
			delete tmp;
			if (tail) {
				tail->previous = nullptr;
			} else {
				head = current = nullptr;
			}
			m_count--;
			return popped;
		}
		T& popEnd() {
			ListElement<T>* tmp = head;
			T& popped = tmp->element;
			head = head->previous;
			delete tmp;
			if (head) {
				head->next = nullptr;
			} else {
				tail = current = nullptr;
			}
			m_count--;
			return popped;
		}
		T& pop() {
			ListElement<T>* newCurrent = nullptr;
			T& popped = current->element;
			if (current->previous) {
				current->previous->next = current->next;
				newCurrent = current->previous;
			} else {
				tail = current->next;
			}
			if (current->next) {
				current->next->previous = current->previous;
				newCurrent = current->next;
			} else {
				head = current->previous;
			}
			ListElement<T>* tmp = current;
			current = newCurrent;
			delete tmp;
			m_count--;
			return popped;
		}
		bool isEmpty() {
			return m_count==0;
		}
		inline T& getCurrent() { return current->element; }
		inline ListElement<T>* getTail() { return tail; }
		inline ListElement<T>* getHead() { return head; }
		inline void resetBegin() { current = tail; }
		inline void resetEnd() { current = head; }
		inline uint32_t getCount() { return m_count; }

		inline LinkedIterator<T> begin() { return LinkedIterator<T>(tail); }
		inline LinkedIterator<T> end() { return LinkedIterator<T>(head->next); }
		inline LinkedReverseIterator<T> rbegin() { return LinkedReverseIterator<T>(head); }
		inline LinkedReverseIterator<T> rend() { return LinkedReverseIterator<T>(tail->previous); }

		inline Reverse<LinkedList> reverse() { return Reverse<LinkedList>(*this); }
};


template<typename T>
std::ostream& operator<<(std::ostream& out, LinkedList<T>& list) {
	out << "[ ";
	for (auto element : list.reverse()) {
		out << element << " -> ";
	}
	return out << "null ]";
}


#endif
