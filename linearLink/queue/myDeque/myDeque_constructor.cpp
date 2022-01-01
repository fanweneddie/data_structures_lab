#include "myDeque.h"
#include <iostream>
using namespace std;
/*
const int DEFAULT_LEN = 0;
const int EACH_BLOCK_SIZE = 10;
const int DEFAULT_BLOCK_NUM = 4;
*/

/*
FOUR TYPES OF CONSTRUCTORS FOR MYDEQUE
############################################################################
*/

/* default constructor for MyDeque */
template <class T>
MyDeque<T>:: MyDeque()
{
    //Initialization, making the values 0 or null.
    len = DEFAULT_LEN; // =0
    memSize = DEFAULT_EACH_BLOCK_SIZE * DEFAULT_BLOCK_NUM ;
    blockNum = DEFAULT_BLOCK_NUM;
    map = new memBlock[DEFAULT_BLOCK_NUM];

    //putting start in the middle of the map.
    start = map + DEFAULT_BLOCK_NUM / 2;
    finish = start;

    //in each block, initialize the first and last ptr.
    //(in this case, only start and finish two blocks)
    start -> first = start -> Tarray;
    start -> last = start -> first + DEFAULT_EACH_BLOCK_SIZE - 1;
    finish -> first = start -> first;
    start -> last = start -> last;

    //initially, current ptr points to the first element in a deque.
    current = start -> first;
    //initialize the first and last position of the last block.( lastPos can't be visited )
    firstPos = current;
    lastPos = current;
}

/* using a size to construct MyDeque */
template<class T>
MyDeque<T>::MyDeque(int inputSize)
{
    len = inputSize;
    memSize = DEFAULT_EACH_BLOCK_SIZE * DEFAULT_BLOCK_NUM ;
    //letting the memSize is bigger than twice of the input size.
    while(inputSize*2 > memSize)
        memSize *= 2;

    blockNum = memSize / DEFAULT_EACH_BLOCK_SIZE;
    map = new memBlock [blockNum];
    start = map + blockNum / 2;
    //putting start in the middle of the map.
    int blockInterval = inputSize / DEFAULT_EACH_BLOCK_SIZE;
    //ATTENTION: if inputsize % DEFAULT_EACH_BLOCK_SIZE == 0
    // that means the lastPos will be at the first place of the block
    //-after the last block.(In order to make end() visited 
    // but to make the content of lastPos unable to be visited )
    finish = start + blockInterval;
    
    //in each block, initialize the first, current and last ptr.
    for (memBlock *tempBlockPtr = start; 
            tempBlockPtr <= finish; tempBlockPtr++)
    {
        tempBlockPtr -> first = tempBlockPtr -> Tarray;
        tempBlockPtr -> last = (tempBlockPtr -> first) 
                            + DEFAULT_EACH_BLOCK_SIZE - 1;
    }
    //initially, current ptr points to the first element in a deque.
    current = start -> first;
    //initialize the last position of the last block.
    //(the content of lastPos can't be visited)
    /* ATTENTION: if inputsize % DEFAULT_EACH_BLOCK_SIZE == 0
    that means the lastPos will be at the first place of the block
    after the last block.(In order to make end() visited 
    but to make the content of lastPos unable to be visited )*/
    firstPos = start->first;
    lastPos = finish->first + (len % DEFAULT_EACH_BLOCK_SIZE) ;
}

/* using the number of repetition and the T value to construct */
template <class T>
MyDeque<T>::MyDeque(int repNum, const T& inputValue)
{
    len = repNum;
    memSize = DEFAULT_EACH_BLOCK_SIZE * DEFAULT_BLOCK_NUM ;
    //letting the memSize is bigger than twice of the input size.
    while( repNum * 2 > memSize)
        memSize *= 2;

    blockNum = memSize / DEFAULT_EACH_BLOCK_SIZE;
    map = new memBlock[blockNum];
    start = map + blockNum / 2;
    //putting start in the middle of the map.
    int blockInterval =  len  / DEFAULT_EACH_BLOCK_SIZE;
    //ATTENTION: if inputsize % DEFAULT_EACH_BLOCK_SIZE == 0
    // that means the lastPos will be at the first place of the block
    //-after the last block.(In order to make end() visited 
    // but to make the content of lastPos unable to be visited )
    finish = start + blockInterval;
    cout << "debug: the start is" << start << endl;
    cout << "debug: the finish is " << finish << endl;

    //in each block, initialize the first, current and last ptr.
    //also need to initialize the Tarray.
    //don't use memset() to initialize the non zero value.
    int initializedNum = 0;
    for (memBlock *tempBlockPtr = start; 
            tempBlockPtr <= finish; ++tempBlockPtr)
    {
        cout << "debug4: the address of T array is " << tempBlockPtr->Tarray << endl;
        tempBlockPtr -> first = tempBlockPtr -> Tarray;      
        tempBlockPtr -> last = (tempBlockPtr -> first) 
                            + DEFAULT_EACH_BLOCK_SIZE;
        cout << "debug4: the first ptr of the block is " << tempBlockPtr->first << endl;
        cout << "debug4: the last ptr of the block is " << tempBlockPtr -> last << endl;
        cout << "the distance " << tempBlockPtr->last - tempBlockPtr->first << endl;
        T *tempIntemPtr = tempBlockPtr->first;
        //initialize each space in the block with the inputItem
        while( initializedNum < len && tempIntemPtr <= tempBlockPtr -> last)
        {
            *tempIntemPtr = inputValue;
            initializedNum += 1;
            ++tempIntemPtr;
        }
    }
    //initially, current ptr points to the first element in a deque.
    current = start -> first;
    //initialize the last position of the last block.
    //(the content of lastPos can't be visited)
    /* ATTENTION: if inputsize % DEFAULT_EACH_BLOCK_SIZE == 0
    that means the lastPos will be at the first place of the block
    after the last block.(In order to make end() visited 
    but to make the content of lastPos unable to be visited )*/
    firstPos = start->first;
    lastPos = finish->first + (len % DEFAULT_EACH_BLOCK_SIZE) ;

    cout << "debug3: the firstPos is " << firstPos << endl;
    cout << "debug3: the lastPos is " << lastPos << endl;
}

/* copy constructor*/
template < class T>
MyDeque<T>::MyDeque(const MyDeque &fromMyDeque)
{
    //initialize the len, memsize, blocknum and map
    len = fromMyDeque.len;
    memSize = fromMyDeque.memSize;
    blockNum = fromMyDeque.blockNum;
    map = new memBlock[blockNum];
    
    //finding the comparative position of the start and finish
    memBlock *newTempBlockPtr = map, *oldTempBlockPtr = fromMyDeque.start;
    start = newTempBlockPtr + (fromMyDeque.start - fromMyDeque.map);
    finish = newTempBlockPtr + (fromMyDeque.finish - fromMyDeque.map);

    //copying the item from the FROMMYDEQUE to this deque
    //---------------------------------------------------------------------
    
    T *newTempItemPtr, *oldTempItemPtr;
    //recording the number of elements that have been copy-initialized
    int initializedLen = 0;
    
    //traverse every block in the memory of two deques
    for (newTempBlockPtr = start; newTempBlockPtr <= finish;
            ++newTempBlockPtr,++oldTempBlockPtr)
    {
        //initialization for the first,current,last ptr in each memblock in new deque.
        newTempBlockPtr -> first = newTempBlockPtr -> Tarray;
        newTempBlockPtr -> last = newTempBlockPtr -> Tarray + DEFAULT_EACH_BLOCK_SIZE-1;
        
        //traverse every position in a block and initialize the value in the new deque.
        for(newTempItemPtr = newTempBlockPtr->first,oldTempItemPtr = oldTempBlockPtr->first; 
            oldTempItemPtr <= oldTempBlockPtr->last && initializedLen < len;
            ++newTempItemPtr,++oldTempItemPtr,++initializedLen)
        {
            *newTempItemPtr = *oldTempItemPtr;
        }
    }

    //initially, current ptr points to the first element in a deque.
    current = start -> first;
    //initialize the last position of the last block.
    //(the content of lastPos can't be visited)
    /* ATTENTION: if inputsize % DEFAULT_EACH_BLOCK_SIZE == 0
    that means the lastPos will be at the first place of the block
    after the last block.(In order to make end() visited 
    but to make the content of lastPos unable to be visited )*/
    firstPos = start->first;
    lastPos = finish->first + (len % DEFAULT_EACH_BLOCK_SIZE) ;
    //finish copying------------------------------------------------------------
}

//FOUR CONSTRUCTORS FOR MYDEQUE $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
