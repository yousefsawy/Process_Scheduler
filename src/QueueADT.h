#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H

#include<iostream>

template<typename T>
class QueueADT {

public:

	virtual bool isEmpty() const = 0;
	virtual bool dequeue(T&) = 0;
	virtual bool peek(T&) const = 0;
	virtual void print() = 0;
	virtual int getCount() const = 0;

};

#endif