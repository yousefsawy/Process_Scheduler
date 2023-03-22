#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include"QueueADT.h"
#include"Node.h"

template<typename T>
class LinkedQueue :public QueueADT<T> {

private:

	Node<T>* front;
	Node<T>* back;

public:

	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T&);
	bool dequeue(T&);
	bool peek(T&)  const;
	~LinkedQueue();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
LinkedQueue<T>::LinkedQueue() {

	front = nullptr;
	back = nullptr;

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
		return true;

	}
	else {

		Node<T>* temp = front;
		dequeuedData = front->getData();
		front = front->getNext();
		delete temp;
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

#endif