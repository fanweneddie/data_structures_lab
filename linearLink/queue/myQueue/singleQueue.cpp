#include <iostream>
using namespace std;
#include "singleQueue.h"

template<class T>
SingleQueue<T>::SingleQueue()
{
    front = new Node<T>;
    rear = front;
    front->next = nullptr;
    len = 0;
}

template<class T>
SingleQueue<T>::SingleQueue(const SingleQueue &otherQue )
{
    front = new Node<T>;
    len = 0;

    Node<T> *thisTempPtr1 = front, *thisTempPtr2 = front;
    Node<T> *otherTempPtr = otherQue.front->next;
    while (otherTempPtr != nullptr)
    {
        thisTempPtr2 = new Node<T>;
        thisTempPtr1->next = thisTempPtr2;
        thisTempPtr1 = thisTempPtr2;
        thisTempPtr1->data = otherTempPtr->data;
        otherTempPtr = otherTempPtr->next;
        ++len;
    }
        rear = thisTempPtr1;
        rear->next = nullptr;
}

//clear the queue to the empty one, but without destructing it.
template<class T>
void SingleQueue<T>::clear()
{
    while( front->next )
    {
        rear = front -> next;
        delete front;
        front = rear;
    }
    len = 0;
}

template<class T>
T& SingleQueue<T>::get_frontEle() const
{
    if( len == 0)
        throw "empty queue can't get the element.\n";
    else
        return (front->next) ->data;
}

template<class T>
void SingleQueue<T>::enQueue(const T &ele)
{
    Node<T>* tempPtr = new Node<T>;
    tempPtr -> data = ele;
    tempPtr -> next = nullptr;
    rear -> next = tempPtr;
    rear = tempPtr;
    ++len;
}

template<class T>
void SingleQueue<T>::deQueue()
{
    if( front == rear )
        throw " the queue is empty.fail to pop out the element.\n";
    else
    {
        Node<T> *tempPtr = front->next;
        front->next = tempPtr->next;
        if (rear == tempPtr)
        {
            rear = front;
        }
        delete tempPtr;
        --len;
    }
}

template<class T>
SingleQueue<T>::~SingleQueue()
{
    while( front)
    {
        rear = front -> next;
        delete front;
        front = rear;
    }
}