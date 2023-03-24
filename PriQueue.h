#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H

#include "QueueADT.h"
#include "PriNode.h"

template<typename T>
class PriQueue :public QueueADT<T> {

private:

	PriNode<T>* front;

public:

	PriQueue();
	bool isEmpty() const;
	bool dequeue(T& dequeuedData);
	bool peek(T& frontData)  const;
	bool enqueue(const T&,int);
	~PriQueue();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
PriQueue<T>::PriQueue() 
{
	front = nullptr;
}



template<typename T>
bool PriQueue<T>::isEmpty() const {

	return (front == nullptr && back == nullptr);

}


template<typename T>
bool PriQueue<T>::enqueue(const T& data,int pri) {

	PriNode<T>* newNode = new PriNode<T>(pri,data);

	if (isEmpty()) {

		front = newNode;

	}
	else 
	{
		if (newNode->getPriority() < front->getPriority())
		{
			newNode->setNext(front);
			front = newNdoe;
		}
		else
		{
			PriNode<T>* prev = front;
			PriNode<T>* temp = front;
			while (newNode->getPriority() >= temp->getPriority())
			{
				prev = temp;
				temp = temp->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(temp);
		}
	}

	return true;

}


template<typename T>
bool PriQueue<T>::dequeue(T& dequeuedData) {

	if (isEmpty()) {

		return false;

	}
	else 
	{
		Node<T>* temp = front;
		dequeuedData = front->getData();
		front = front->getNext();
		delete temp;
		return true;

	}

}

template<typename T>
bool PriQueue<T>::peek(T& frontData)  const {

	if (isEmpty()) {

		return false;

	}

	frontData = front->getData();
	return true;

}



template<typename T>
PriQueue<T>::~PriQueue() {

	T dummy;
	while (dequeue(dummy));

}
#endif