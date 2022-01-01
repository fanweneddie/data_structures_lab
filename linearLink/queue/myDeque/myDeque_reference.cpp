#include "myDeque_iterator.cpp"

/* return the starting place of the deque */
template<class T>
typename MyDeque<T>::MyIterator  MyDeque<T>::begin() const
{
    MyIterator tempItr(*this, firstPos);
    return tempItr;
}

/* return the ending place of the deque */
template<class T>
typename MyDeque<T>::MyIterator  MyDeque<T>::end() const
{
    cout << "enter the end().\n";
    MyIterator tempItr(*this, lastPos);
    cout << "finish the end().\n";
    return tempItr;
}

/* overload operator [] : using index reference */
template<class T>
T & MyDeque<T>::operator[](int indexNum) const
{
    MyDeque<T>::MyIterator itr = begin();
    for( int i = 0 ; i < indexNum;++i )
    {
        ++itr;
    }
    return *( itr.get_currentPtr() );
}

//at 


/* return the element at the front */
template<class T>
T& MyDeque<T>::front() const
{
    MyIterator itr = begin();
    return *itr;
}

/* return the element at the back */
template <class T>
T& MyDeque<T>::back() const
{
    MyIterator itr = end();
    --itr;
    return *itr;
}


/* overload of the '=' assigning operator of mydeque */
template<class T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque &otherDeque)
{
    if(this != &otherDeque)
    {
        cout << "debug10: enter the =\n";
        //delete some pointers of the mydeque
        //HOW ABOUT THE POINTERS IN THE MEMBLOCK?
        delete map;

        // assign the members of the mydeque by copying otherDeque
        len = otherDeque.get_len();
        memSize = otherDeque.get_memSize();
        blockNum = otherDeque.get_blockNum();
        map = new memBlock[blockNum];
        cout << "debug10.1:the new len is " << len << endl;
        cout << "debug10.2:the new memsize is " << memSize << endl;
        cout << "debug10.3: the new blockNum is " << blockNum << endl;

        memBlock *newTempBlockPtr = map, *oldTempBlockPtr = otherDeque.get_start();
        start = newTempBlockPtr + ( otherDeque.get_start() - otherDeque.get_map() );
        finish = newTempBlockPtr + ( otherDeque.get_finish() - otherDeque.get_map() );

        cout << "other's start is " << otherDeque.get_start() << endl;
        cout << "other's finish is " << otherDeque.get_finish() << endl;
        cout << "my start is " << start << endl;
        cout << "my finish is " << finish << endl;
        if( otherDeque.get_finish() -  otherDeque.get_start() == finish - start)
        {
            cout << "yes!\n";
        }
        else
            cout << "no!\n";
        T *newTempItemPtr, *oldTempItemPtr;
        T *oldCurrent = otherDeque.get_current();

        /* ASSIGNING THE CONTENT IN T ARRAY FROM OTHERDEQUE TO THIS 
        ##################################################################################*/
        
        // firstly, assigning the first,and the last ptr in each block
        for (newTempBlockPtr = start; newTempBlockPtr <= finish;
            ++newTempBlockPtr,++oldTempBlockPtr)
        {
            newTempBlockPtr -> first = newTempBlockPtr -> Tarray;
            newTempBlockPtr -> last = newTempBlockPtr -> Tarray + DEFAULT_EACH_BLOCK_SIZE -1;
            cout << " finding the first and last of each block\n";
        }

        //secondly, finding the firstPos and the lastPos of this deque.
        newTempBlockPtr = start;
        newTempItemPtr = start->last;
        MyIterator itr = otherDeque.begin();
        int i = finish - start;
        cout << " the distance between the finish and start is " << i << endl;
        firstPos = newTempItemPtr;
        cout << "the first place of the start block is " << start->first << endl;
        cout << "the first pos is " << firstPos << endl;
        lastPos = finish->first + (len % DEFAULT_EACH_BLOCK_SIZE) ;

        //thirdly, copying the content of the array and finding the currentPtr.
        while( newTempItemPtr != lastPos )
        {
            *newTempItemPtr = *itr;
            if( oldCurrent == newTempItemPtr )
            {
                current = newTempItemPtr;
            }

            // traverse the Tarray
            if( newTempItemPtr != newTempBlockPtr->last )
            {
                ++newTempItemPtr;
            }
            else
            {
                ++newTempBlockPtr;
                newTempItemPtr = newTempBlockPtr->first;   
            }
        }
    }

    return *this;
}

/* if the deque memory of deque is not enough for elongating,
    we need to expand the size of the memory( x2 ) */
// since this ptr is not assignable, it is better to first create an alternate deque, then assign 
// -the value of each members in the orginal deque.
template<class T>
void MyDeque<T>:: expand_memory()
{
    // to make the newLen big enough to help multiply the memory size
    int tempLen = len;
    while(tempLen <= memSize /2 )
        ++tempLen;
    cout << "debug0: tempLen is " << tempLen << endl;
    // construct a deque with a larger size.
    //memsize and blocknum are multiplied, but new len need to be changed to the original one.
    // start is okay but finish, current and lastPos need to be revised.
    MyDeque newDeque(tempLen);
    newDeque.change_len(len);
    int blockInterval =  len  / DEFAULT_EACH_BLOCK_SIZE;
    memBlock *newStart = newDeque.get_start();
    memBlock *newFinish = newStart + blockInterval;
    newDeque.change_finish(newFinish);

    // also need to copy the element from the original deque to the newDeque
    
    MyIterator itr1Temp = begin(), itr1End = end(),
               itr2Temp = newDeque.begin();
    while( itr1Temp != itr1End )
    {
        //copy the value
        *itr2Temp = *itr1Temp;
        if( itr1Temp.get_currentPtr() == current  )
        {
            //revising the current
            newDeque.change_current( itr2Temp.get_currentPtr() );
        }
        ++itr1Temp;
        ++itr2Temp;
    }
    //change the last position
    newDeque.change_lastPos( itr2Temp.get_currentPtr() );
    cout << "debug1: the len of newDeque is " << newDeque.get_len() << endl;
    cout << "debug2: the memsize of newDeque is " << newDeque.get_memSize() << endl;
    cout << "debug3: let's print the newDeque: \n";


    MyIterator it1 = newDeque.begin(), it2 = newDeque.end();
    while(it1 != it2)
    {
        cout << *it1 << endl;
        it1++;
    }

    //NOW I AM TRYING TO COPY THE MEMBERS FROM NEWDEQUE TO THIS* VECTOR.
    //delete map pointer of the mydeque(because I only "new" allocate map pointer)
    //HOW ABOUT THE POINTERS IN THE MEMBLOCK?
    delete map;
    // assign the members of the mydeque by copying otherDeque
    len = newDeque.get_len();
    cout << "debug10.1:the new len is " << len << endl;
    memSize = newDeque.get_memSize();
    blockNum = newDeque.get_blockNum();
    map = new memBlock[blockNum];

    memBlock *newTempBlockPtr = map, *oldTempBlockPtr = newDeque.get_start();
    start = newTempBlockPtr + (newDeque.get_start() - newDeque.get_map());
    finish = newTempBlockPtr + (newDeque.get_finish() - newDeque.get_map());

    T *newTempItemPtr, *oldTempItemPtr;
    int initializedLen = 0;
    T *oldCurrent = newDeque.get_current();

    for (newTempBlockPtr = start; newTempBlockPtr <= finish;
         ++newTempBlockPtr, ++oldTempBlockPtr)
    {
        //initialization for the first,current,last ptr in each memblock in new deque.
        newTempBlockPtr->first = newTempBlockPtr->Tarray;
        newTempBlockPtr->last = newTempBlockPtr->Tarray + DEFAULT_EACH_BLOCK_SIZE -1;

        //traverse every position in a block and initialize the value in the new deque.
        for (newTempItemPtr = newTempBlockPtr->first, oldTempItemPtr = oldTempBlockPtr->first;
             oldTempItemPtr <= oldTempBlockPtr->last && initializedLen < len;
             ++newTempItemPtr, ++oldTempItemPtr, ++initializedLen)
        {
            *newTempItemPtr = *oldTempItemPtr;
            if (oldTempItemPtr == oldCurrent)
            {
                current = newTempItemPtr;
            }
        }
        }
        firstPos = start->first;
        lastPos = finish->first + (len % DEFAULT_EACH_BLOCK_SIZE) ;
        cout << "debug1: finish copying.\n";
}