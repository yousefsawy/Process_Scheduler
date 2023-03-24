#ifndef PRI_NODE_H
#define PRI_NODE_H
#include "Node.h"

template<typename T>
class PriNode: public Node<T> {

private:

	int prior;

public:

	PriNode(const T& data, PriNode<T>* next,int pri=-1);
	void setPriority(int);
	int getPriority();
	void setNext(PriNode<T>*);

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATIONS

template<typename T>
 PriNode<T> :: PriNode(const T& data, PriNode<T>* next, int pri) :(data,next)

{
	prior = pri;
}


template<typename T>
void PriNode<T>::setPriority(int pri)
{
	prior=pri
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


#endif