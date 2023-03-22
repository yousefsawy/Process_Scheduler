#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {

private:

	T data;
	Node<T>* next;

public:

	Node();
	Node(const T&);
	Node(const T&, Node<T>*);
	void setData(const T&);
	void setNext(Node<T>*);
	T getData() const;
	Node<T>* getNext() const;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
Node<T>::Node() {

	next = nullptr;

}

template<typename T>
Node<T>::Node(const T& data) {

	this->data = data;
	next = nullptr;

}

template<typename T>
Node<T>::Node(const T& data, Node<T>* next) {

	this->data = data;
	this->next = next;

}

template<typename T>
void Node<T>::setData(const T& data) {

	this->data = data;

}

template<typename T>
void Node<T>::setNext(Node<T>* next) {

	this->next = next;

}

template<typename T>
T Node<T>::getData() const {

	return data;

}

template<typename T>
Node<T>* Node<T>::getNext() const {

	return next;

}

#endif