#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include"QueueADT.h"
#include"Node.h"

class Process;

template<typename T>
class LinkedQueue :public QueueADT<T> {

protected:

	Node<T>* front;
	Node<T>* back;
	int size;

public:
	
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T&);
	bool dequeue(T&);
	bool peek(T&)  const;
	void print();
	int getCount() const;
	~LinkedQueue();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
LinkedQueue<T>::LinkedQueue() {

	front = nullptr;
	back = nullptr;
	size = 0;

}

template<typename T>
bool LinkedQueue<T>::isEmpty() const {

	return (front == nullptr && back == nullptr);

}

template<typename T>
bool LinkedQueue<T>::enqueue(const T& data) {

	Node<T>* newNode = new Node<T>(data);

	if (isEmpty()) {

		front = newNode;
		back = newNode;

	}
	else {

		back->setNext(newNode);
		back = newNode;

	}
	size++;
	return true;

}

template<typename T>
bool LinkedQueue<T>::dequeue(T& dequeuedData) {

	if (isEmpty()) {

		return false;

	}
	else if (front == back) {

		dequeuedData = front->getData();
		delete front;
		front = nullptr;
		back = nullptr;
		size--;
		return true;

	}
	else {

		Node<T>* temp = front;
		dequeuedData = front->getData();
		front = front->getNext();
		delete temp;
		size--;
		return true;

	}

}

template<typename T>
bool LinkedQueue<T>::peek(T& frontData)  const {

	if (isEmpty()) {

		return false;

	}
	
	frontData = front->getData();
	return true;

}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {

	T dummy;
	while (dequeue(dummy));

}





template<typename T>
int LinkedQueue<T>::getCount() const {

	return size;

}

template<typename T>
void LinkedQueue<T>::print() {

	Node<T>* current = front;

	while (current) {

		std::cout << current->getData();
		if (current->getNext() != nullptr) {
			std::cout << ", ";
		}
		current = current->getNext();

	}

}



#endif