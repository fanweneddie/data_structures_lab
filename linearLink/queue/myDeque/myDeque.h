#ifndef MYDEQUE
#define MYDEQUE

const int DEFAULT_LEN = 0;
const int DEFAULT_EACH_BLOCK_SIZE = 10;
const int DEFAULT_BLOCK_NUM = 4;

template <class T>
class MyDeque
{
    protected:
        int len;
        int memSize;
        int blockNum;
        struct memBlock
        {
            // An array of T to store T type variables
            // the Last place is for the last ptr, doesn't store anything.
            T Tarray[DEFAULT_EACH_BLOCK_SIZE];

            //points to the first T element of a memory block
            T* first;
            
            //points to the last T element of a memory block
            T* last;
            
        };

        // an array of memBlock.
        memBlock* map;

        //double pointer pointing at the starting place of the map
        //(actually it is in the middle of the map at first)
        memBlock* start;

        //double pointer pointing at the finishing place of the map
        //(actually it is in the middle of the map at first)
        memBlock* finish;

        //points to the current T element of a deque
        T* current;

        //point to the first position in the begining block. 
        T *firstPos;
        
        //point to the last position in the finish block.
        T *lastPos;

    public:
        //a random iterator for the deque
        class MyIterator
        {
        protected:
            // because the memory is semi-consecutive, not only the currentptr
            //- is required here, the currentBlock that the *currentPtr is in 
            // is also needed to know the first, last ptr in a block.
            T *currentPtr;
            memBlock *currentBlock;

        public:
            /*First,default constructor requiring no argument. */
            MyIterator();

            /*Second, using the current pointer to construct an iterator. */
            // and the deque is also needed to get the currentblock.
            MyIterator(const MyDeque& currentDeque,T *currentPointer);

            /*Third, copy-constructor require a reference of MyIterator. */
            MyIterator(const MyIterator &it);

            /*getting the current pointer of this iterator. */
            T *get_currentPtr() const { return currentPtr; }

            /* getting the current block that the pointer is in */
            memBlock *get_currentBlock() const { return currentBlock; }

            /* reassignment of some operators */
            //#############################################################
            MyIterator &operator=(const MyIterator &it);

            bool operator==(const MyIterator &it);

            bool operator!=(const MyIterator &it);

            //++it;
            MyIterator &operator++();

            //it++
            MyIterator operator++(int);

            //--it;
            MyIterator &operator--();

            //it--;
            MyIterator operator--(int);

            //using * as a reference
            T &operator*();

            //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        };

        /* default constructor for MyDeque */
        MyDeque();

        /* using a size to construct MyDeque */
        MyDeque(int inputSize);

        /* using the number of repetition and the T value to construct */
        MyDeque(int repNum, const T& inputValue);

        /* copy constructor*/
        MyDeque(const MyDeque &fromMyDeque);

        /* getting and changing the value of protected member of the deque. 
        (IN ORDER TO SAVE THE SPACE, I WRITE THE FUNCTION IN ONE LINE IN 
        THE HEADFILE BECAUSE THEY ARE SO SIMPLE)
        ####################################################################*/

        /* getting the value of len, memsize and blockNum */
        int get_len() const { return len; }

        int get_memSize() const { return memSize; }

        int get_blockNum() const { return blockNum; }

        /* changing the value of len, memsize and blockNum */
        void change_len(int newLen) { len = newLen; }

        void change_memSize(int newMemSize) { memSize = newMemSize; }

        void change_blockNum(int newBlockNum) { blockNum = newBlockNum; }

        /* getting the map, starting and finishing block ptr */
        memBlock *get_map() const { return map; }
        
        memBlock *get_start() const { return start; }

        memBlock *get_finish() const { return finish; }

        /* getting the current,firstPos and lastPos T* ptr */
        T *get_current() const { return current; }

        T *get_firstPos() const { return firstPos; }

        T *get_lastPos() const { return lastPos; }

        /* changing the starting and finishing block ptr */
        void change_start(memBlock* newStart) { start = newStart; }

        void change_finish(memBlock* newFinish) { finish = newFinish; }

        /* changing the current,firstPos and lastPos T* ptr */
        void change_current(T* newCurrent) { current = newCurrent; }

        void change_firstPos(T *newFirstPos) { firstPos = newFirstPos; }
        
        void change_lastPos(T* newLastPos) { lastPos = newLastPos; }

        /* getting and changing the value of protected members
        &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
        
        /* return the starting place of the deque */
        MyIterator begin() const;

        /* return the ending place of the deque */
        MyIterator end() const;

        /* overload operator [] : using index reference */
        T &operator[](int indexNum) const;

        /* using at() for reference and can check 
            whether the index is out of range
        */ 
        T &at(int order) const;

        /* return the element at the front */
        T &front() const;

        /* return the element at the back */
        T &back() const;

        /* overload of the '=' assigning operator of mydeque */
        MyDeque &operator=(const MyDeque &otherDeque);

        /* if the deque memory of deque is not enough for elongating,
            we need to expand the size of the memory */
        // since this ptr is not assignable, it is better to return a new deque
        void expand_memory();

        /*insert an item at the order th 
        place of the deque(starting from 0 )*/
        void insert(int order, const T &inputItem);

        /*delete an item at the order th 
        place of the deque(starting from 0 )*/
        void delet(int order, const T &deleteItem);

        // those four functions below are the special circumstances 
        // of insert() and delet().
        void pop_back();

        void pop_front();

        void push_back();

        void push_front();

/*      ~MyDeque()
        {
            delete first;
            delete current;
            delete last;
            delete map;
            delete start;
            delete finish;
            delete node;
        }
*/
};

#endif
