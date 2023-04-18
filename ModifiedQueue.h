#ifndef MODIFIED_QUEUE_H
#define MODIFIED_QUEUE_H

#include "Process.h"
#include "LinkedQueue.h"
#include "Node.h"

template <typename T>
class ModifiedQueue :
    public LinkedQueue<T>
{
public:
    bool deleteMid(int, T&); //Deletes from the Queue using the index and returns the Object
};







//-------------------IMPLEMENTATION---------------------------------------

template <typename T>
inline bool ModifiedQueue<T>::deleteMid(int n, T& Object)
{
    int i = 0;
    Node<T>* temp = this->front;
    if (!temp)
        return false;

    if (n == i)
    {
        Object = temp->getData();
        if (!temp->getNext())
        {
            this->front = nullptr;
            this->back = nullptr;
        }
        else
        {
            this->front = temp->getNext();
        }
        delete temp;
        return true;
    }

    i++;
    while (temp->getNext() && i <= n)
    {
        if (n == i)
        {
            Object = temp->getNext()->getData();
            Node<T>* deleteTemp = temp->getNext();
            temp->setNext(deleteTemp->getNext());


            if (!temp->getNext()) //Used when deleting last element
            {
                this->back = temp;
            }

            delete deleteTemp; //ET3ADEL
            return true;
        }
        temp = temp->getNext();
        i++;
    }
    return false;

}



#endif
