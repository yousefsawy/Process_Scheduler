#ifndef PRI_NODE_H
#define PRI_NODE_H
#include "Node.h"

template<typename T>
class PriNode {

private:

	int prior;
	PriNode<T>* next;
	T data;

public:

	PriNode(const T& data, PriNode<T>* next=nullptr,int pri=-1);
	void setPriority(int);
	T getData() const;
	void setData(const T&);
	int getPriority();
	void setNext(PriNode<T>*);
	PriNode<T>* getNext();

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
 PriNode<T> :: PriNode(const T& data, PriNode<T>* next, int pri)

{
	 this->data = data;
	 this->next = next;
	prior = pri;
}


template<typename T>
void PriNode<T>::setPriority(int pri)
{
	prior = pri;
}

template<typename T>
T PriNode<T>::getData() const
{
	return data;
}

template<typename T>
inline void PriNode<T>::setData(const T& data)
{
	this->data = data;
}


template<typename T>
int PriNode<T>::getPriority()
{
	return prior;
}

template<typename T>
void PriNode<T>::setNext(PriNode<T>* next) {

	this->next = next;

}
template<typename T>
PriNode<T>* PriNode<T>::getNext()
{
	return next;
}

#endif