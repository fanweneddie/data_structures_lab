#include "myDeque_constructor.cpp"
/*
const int DEFAULT_LEN = 0;
const int EACH_BLOCK_SIZE = 10;
const int DEFAULT_BLOCK_NUM = 4;
*/

/*
THREE CONSTRUCTORS FOR MYITERATOR
#####################################################################################
*/

/*First,default constructor requiring no argument. */
template<class T>
MyDeque<T>::MyIterator::MyIterator()
{
    currentPtr = new T;
    currentPtr = nullptr;
    currentBlock = new memBlock;
    currentBlock = nullptr;
}

/*Second, using the current pointer to construct an iterator. */
template<class T>
MyDeque<T>::MyIterator::MyIterator(const MyDeque& currentDeque ,T *currentPointer)
{
    currentPtr = currentPointer;
    memBlock *tempBlockPtr = currentDeque.get_start();
    T *tempItemPtr = currentDeque.get_firstPos();
    T *oldLastItemPtr = currentDeque.get_lastPos();
    cout << "debug0.8: the len of the currentDeque is " << currentDeque.get_len() << endl;
    cout << "debug 0.9 : the currentPtr is " << currentPointer << endl;
    cout << "debug0.91 : the lastPos of the currentDeque is " << currentDeque.get_lastPos() << endl;
    cout << "debug1.0: the start of currentDeque is " << tempBlockPtr << endl;
    cout << "debug1.1: the first Pos of currentDeque is " << tempItemPtr << endl;
    cout << "debug1.2: the last Pos of the currentDeque is " << oldLastItemPtr << endl;
    bool flagNotFindingBlock = true;
    bool goToNextBlock = false;
    int i = 0;
    
    //finding the block that the content currentptr points to is in
    //while( flagNotFindingBlock && !goToNextBlock)
    while( i < 20)
    {
        cout << "debug 2.0 : the currentPtr is " << currentPointer << endl;
        cout << "debug 2.1 : the tempItemPtr is " << tempItemPtr << endl;
        //having found the right currentPtr, and thereby find the block
        if( currentPointer == tempItemPtr )
            {
                cout << "finding the right block!\n";
                currentBlock = tempBlockPtr;
                flagNotFindingBlock = true;
                break;
            }
        //haven't found the currentPtr, go on searching
        else
        {
            if( tempItemPtr == tempBlockPtr -> last )
            {
                ++tempBlockPtr;
                tempItemPtr = tempBlockPtr -> first;
                cout << "go to the next block\n";
                goToNextBlock = true;
            }        
            else
            {
                ++tempItemPtr;
                //cout << "go to the next place.\n";
                //cout << i << endl;
            }
        }
        i++;
    }
    currentBlock->first = currentBlock->Tarray;
    currentBlock->last = currentBlock->first + DEFAULT_EACH_BLOCK_SIZE - 1;
}

/*Third, copy-constructor require a reference of MyIterator. */
template<class T>
MyDeque<T>::MyIterator::MyIterator(const MyIterator &it)
{
    currentPtr = it.currentPtr;
    currentBlock = it.currentBlock;
}


/* REASSIGNMENT OF SOME OPERATORS */
//#############################################################

/* overload for the '=' operator. */
//remember to add 'typename' before the returning type 
//in case the compiler can't recognize MyDeque<T>::MyIterator
template<class T>
typename MyDeque<T>::MyIterator& MyDeque<T>::MyIterator::operator=(const MyIterator &it)
{
    if( this->currentPtr != it.get_currentPtr() )
    {
        currentPtr = it.get_currentPtr();
        memBlock* tempBlockPtr = it.get_currentBlock();
        currentBlock = tempBlockPtr;
        currentBlock->first = tempBlockPtr->first;
        currentBlock->last = tempBlockPtr->last;
    }
    return *this;
}

/* overload for '==' operators */
template<class T>
bool MyDeque<T>::MyIterator::operator==(const MyIterator &it)
{
    return this->currentPtr == it.get_currentPtr();
}

/* overload for '!=' operators */
template<class T>
bool MyDeque<T>::MyIterator::operator!=(const MyIterator &it)
{
    return this->currentPtr != it.get_currentPtr();
}

/* overload for ++it operator */
//++it;
//if successful, it will raise the efficiency of traversing 
//in a "comparatively discrete" memory space.
template<class T>
typename MyDeque<T>::MyIterator& MyDeque<T>::MyIterator::operator++()
{
    //if the currentptr is not the left one of the last position of the block
    if( currentPtr < currentBlock -> last )
    {
        ++currentPtr;
    }
    //or we need to let the currentPtr jump into the next block
    //(we don't consider being out of range in the iterator)
    else
    {
        ++currentBlock;
        currentBlock->first = currentBlock->Tarray;
        currentBlock->last = currentBlock->Tarray + DEFAULT_EACH_BLOCK_SIZE -1 ;
        currentPtr = currentBlock->first;
    }
    return *this;
}

/*overload for it++ operator */
//it++
template<class T>
typename MyDeque<T>::MyIterator MyDeque<T>::MyIterator::operator++(int)
{
    MyIterator tempIterator = *this;
      if( currentPtr < currentBlock -> last )
    {
        ++currentPtr;
    }
    else
    {
        ++currentBlock;
        currentBlock->first = currentBlock->Tarray;
        currentBlock->last = currentBlock->Tarray + DEFAULT_EACH_BLOCK_SIZE - 1;
        currentPtr = currentBlock->first;
    }
    return tempIterator;
}

/* overload for --it opeartor */
//--it;
template<class T>
typename MyDeque<T>::MyIterator& MyDeque<T>::MyIterator::operator--()
{
    cout << "debug3: the address of currentblock is " << currentBlock << endl;
    //if the currentptr is not at the first position of the block
    cout << "debug3.1: the address of currentPtr is " << currentPtr << endl;
    cout << "debug3.2: the address of the currentBlock->first is " << currentBlock->first << endl;
    if( currentPtr > currentBlock -> first )
    {
        --currentPtr;
    }
    //or we need to let the currentPtr jump into the last block
    //(we don't consider being out of range in the iterator)
    else
    {
        --currentBlock;
        cout << "debug4: the address of currentblock is " << currentBlock << endl;
        currentBlock->first = currentBlock->Tarray;
        currentBlock->last = currentBlock->Tarray + DEFAULT_EACH_BLOCK_SIZE -1 ;
        currentPtr = currentBlock->last ;
    }
    cout << "debug4.1: now the address of the currentPtr is " << currentPtr << endl;
    cout << "the value of currentPtr is " << *currentPtr << endl;
    return *this;
}

/*overload for it-- operator */
//it--
template<class T>
typename MyDeque<T>::MyIterator MyDeque<T>::MyIterator::operator--(int)
{
    MyIterator tempIterator = *this;
      if( currentPtr > currentBlock -> first)
    {
        --currentPtr;
    }
    else
    {
        --currentBlock;
        currentBlock->first = currentBlock->Tarray;
        currentBlock->last = currentBlock->Tarray + DEFAULT_EACH_BLOCK_SIZE -1;
        currentPtr = currentBlock->last;
    }
    return tempIterator;
}

/* overload '*' operator. using * as a reference */
template<class T>
T & MyDeque<T>::MyIterator::operator*()
{
    return *currentPtr;
}