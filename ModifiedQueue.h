#ifndef MODIFIED_QUEUE_H
#define MODIFIED_QUEUE_H


#include "LinkedQueue.h"
#include "Node.h"

template <typename T>
class ModifiedQueue :
    public LinkedQueue<T>
{
public:
    bool deleteMid(int, T&); //Deletes from the Queue using the index and returns the Object
    bool deleteMid(T&); //Deletes from the Queue using the objext
};







//-------------------IMPLEMENTATION---------------------------------------

template <typename T>
inline bool ModifiedQueue<T>::deleteMid(int n, T& Object)
{
    int i = 0;
    Node<T>* temp = this->front;
    if (!temp)
        return false;

    if (!temp->getNext())
    {
        if (n == 0)
        {
            Object = temp->getData();
            this->front = nullptr;
            delete temp;
            return true;
        }
        return false;
    }

    while (temp->getNext() && i <= n)
    {
        i++;
        if (n == i)
        {
            Object = temp->getNext()->getData();
            Node<T>* deleteTemp = temp->getNext();
            temp->setNext(deleteTemp->getNext());
            delete deleteTemp;
            return true;
        }
        temp = temp->getNext();
    }
    return false;

}

template <typename T>
inline bool ModifiedQueue<T>::deleteMid(T& Compare)
{
    Node<T>* temp = this->front;
    if (!temp->getNext())
    {
        if (temp->getData() == Compare)
        {
            delete front;
            front = nullptr;
            back = nullptr;
            return true;
        }
        return false;
    }

    while (temp->getNext())
    {
        if (temp->getNext()->getData() == Compare)
        {
            Node<T>* tempDelete = temp->getNext();
            temp->setNext(tempDelete->getNext());
            delete tempDelete->getData();
            return true;
        }
    }
    return false;
}

#endif