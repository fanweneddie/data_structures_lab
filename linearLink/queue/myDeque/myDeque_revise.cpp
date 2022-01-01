#include "myDeque_reference.cpp"
/*insert an item at the order th 
place of the deque(starting from 0 )*/

template <class T>
void MyDeque<T>::insert(int order, const T&inputItem)
{
    len += 1;
    //unlucky, we need to expand the memory size 
    //-and copy the previous items into a new deque
    if( len >= memSize/2 )
    {
        expand_memory();
    }
    //if order is lower than len/2 , expand the left side.
    if(order < len/2)
    {
        
    }

}
*/