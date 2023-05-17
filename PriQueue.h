#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H

#include "QueueADT.h"
#include "PriNode.h"

template<typename T>
class PriQueue : public QueueADT<T> {

private:

	PriNode<T>* front;
	int size;

public:

	PriQueue();
	bool isEmpty() const;
	bool dequeue(T& dequeuedData);
	bool peek(T& frontData)  const;
	bool enqueue(const T&, int);
	void print();
	int getCount() const;
	~PriQueue();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
PriQueue<T>::PriQueue()
{
	front = nullptr;
	size = 0;
}



template<typename T>
bool PriQueue<T>::isEmpty() const {

	return (front == nullptr);

}


template<typename T>
bool PriQueue<T>::enqueue(const T& data, int pri)
{
	PriNode<T>* newNode = new PriNode<T>(data, nullptr, pri);

	if (isEmpty()) {

		front = newNode;

	}
	else
	{
		if (newNode->getPriority() < front->getPriority())
		{
			newNode->setNext(front);
			front = newNode;
		}
		else
		{
			PriNode<T>* prev = front;
			PriNode<T>* temp = front;
			while (temp && newNode->getPriority() >= temp->getPriority())
			{
				prev = temp;
				temp = temp->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(temp);

		}
	}
	size++;
	return true;

}


template<typename T>
bool PriQueue<T>::dequeue(T& dequeuedData) {

	if (isEmpty()) {

		return false;

	}
	else
	{
		PriNode<T>* temp = front;
		dequeuedData = front->getData();
		front = front->getNext();
		delete temp;
		size--;
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


template<typename T>
int PriQueue<T>::getCount() const {

	return size;

}

template<typename T>
void PriQueue<T>::print() {

	PriNode<T>* current = front;

	while (current) {



		std::cout << current->getData();
		if (current->getNext() != nullptr) {
			std::cout << ", ";
		}
		current = current->getNext();

	}

}

#endif