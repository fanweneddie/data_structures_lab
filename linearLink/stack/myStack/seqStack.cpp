#include "seqStack.h"

//default constructor
template<class T>
SeqStack<T>::SeqStack()
{
    base = new T[STACK_INITIAL_SIZE];
    top = base;
    size = 0;
    capacity = STACK_INITIAL_SIZE;
}

//constructor that use an array to construct a sequential stack
template<class T>
SeqStack<T>::SeqStack(T* seqList,int listSize)
{
    capacity = STACK_INITIAL_SIZE;
    while( capacity < listSize )
        capacity += STACK_INCREMENT;
    
    size = listSize;
    base = new T[capacity];
    for (int i = 0; i < size;++i)
    {
        *(base + i) = *(seqList + i);
    }
    top = base + size;
    
}

// copy constructor
template<class T>
SeqStack<T>::SeqStack(const SeqStack &otherSeqstack)
{
    capacity = otherSeqstack.capacity;
    size = otherSeqstack.size;
    base = new T[capacity];
    for (int i = 0; i < size;++i)
    {
        *(base + i) = *(otherSeqstack.base + i);
    }
    top = base + size;
}

// clear all the elements in the stack.
template <class T>
void SeqStack<T>::clear()
{
    if( !is_empty() )
    {
        top = base;
        size = 0;
    }
}

//getting the element at the top of the stack.
template <class T>
T& SeqStack<T>::get_top()
{
    //there is no element in the stack.
    if(top == base)
    {
        //throw the exception.
        throw "NO element in the stack.\n";
    }
    else 
        return *(top-1);
}

//pushing the element into the back of the stack
template<class T>
void SeqStack<T>::push(const T &element)
{
    //the stack is full, hence required to expand the memory.
    if(top == base + capacity)
    {
        T *tempPtr = base;
        base = new T[capacity + STACK_INCREMENT];
        for (int i = 0; i < capacity;++i)
        {
            *(base + i) = *(tempPtr + i);
        }
        top = base + capacity;
        delete tempPtr;
        capacity += STACK_INCREMENT;
    }

    *top = element;
    ++top;
    ++size;
   
}

/* pop out the element at the top of the stack
    return the element at the top and erase it.
    if the stack is empty, throw an exception.
*/
template<class T>
T & SeqStack<T>::pop()
{
    if( is_empty() )
    {
        throw "NO element in the stack.\n ";
    }

    --top;
    --size;
    return *top;
}
