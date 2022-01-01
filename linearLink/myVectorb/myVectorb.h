#ifndef MYVECTORB
#define MYVECTORB
//MAYBE WE NEED TO MEMSET!!!
#include <iostream>
#include <string>
using namespace std;

//the default length of a vector
const int DEFAULT_LEN = 5;
const int ORIGINAL_MEMORY_SIZE = 10;

template <class T>
class MyVectorb
{
    protected:
    /* actually, the memory is arranged in advance
        if the len of the vector is bigger than the memory size, it will 
        arrange a new memory and replicate the previous content.
    */    
        int len;
        int memSize;
        T *head;
    public:
        
        class MyIterator
        {
            protected:
                T *pt;

            public:
                //attention: in the subclass, ' this pointer'
                //- points to MyIterator.

                /*
                    three constructors of the iterator.
                    #################################################             
                */
        
                //first,default constructor requiring no argument
                MyIterator()
                {
                    pt = new T;
                }

                //Second, using the pointer to construct an iterator.
                MyIterator(T *pt)
                {
                    this->pt = pt;
                }

                //third, using the object of MyIterator to copy-construct 
                //-an iterator.
                MyIterator(const MyIterator &it)
                {
                    this->pt = it.pt;
                }
                
                //getting the pointer of this iterator.
                T *get_ptr() const
                {
                    return this->pt;
                }

                //reassignment of some operators
                MyIterator &operator=(const MyIterator &it)
                {
                    this->pt = it.pt;
                    return *this;
                }

                bool operator==(const MyIterator &it)
                {
                    return (this->pt == it.pt);
                }

                bool operator!=(const MyIterator &it)
                {
                    return (this->pt != it.pt);
                }


                //++it;
                MyIterator &operator++()
                {
                    this->pt++;
                    return *this;
                }

                //it++;
                /*ATTENTION: since we return a temporary variable,
                we can't return a reference,
                because the variable will be deleted after the function.
                THE SAME AS "it--"" 
                */
                MyIterator operator++(int)
                {
                    MyIterator temp = *this;
                    this->pt ++;
                    return temp;
                }

                //--it;
                MyIterator &operator--()
                {
                    this->pt--;
                    return *this;
                }

                //it--;
                MyIterator operator--(int)
                {
                    MyIterator temp = *this;
                    this->pt--;
                    return temp;
                }
                //using * as a reference
                T& operator*()
                {
                    return *(this->pt);
                }
        };
        
        /*
        DEFAULT CONSTRUCTOR
        given the length, and it will construct 
        a vector with 0 as default content.
        #####################################################################
        PAY ATTENTION: IF THE DATA IS A STRING
        -IT WILL BE DANGEROUS BECAUSE 0 MEANS NULLSTRING.
        */
        MyVectorb(int vlen = DEFAULT_LEN);

        /*
            REPEATING CONSTRUCTOR
            #####################################################################
            inputing the length and the inputdata,
            and it will construct a vector with inputdata of the number of length.
            ATTENTION: THE reason why I write two constructor functions is because
                the default value of inputData can't be 0(dangerous if T is string)
        */
        MyVectorb(int vlen, T inputData);

        //Third constructor: using the head ptr to construct a vector
        //however, the len is only 1 and needed to resize in the future.
        MyVectorb(T* inputHead)
        {
            head = inputHead;
            len = 1;
            memSize = ORIGINAL_MEMORY_SIZE;
        }

        /*
        allocating twice the size of the original memory to a vector.
        Needed to replicate again.
        ############################################################
        CAN BE USED IN the function push_back()
        */
        void expand_memory()
        {
            int newMemSize = memSize * 2;
            T *newHead = new T[newMemSize];
            T *tempPtr = newHead;
            for (int i = 0; i < len;i++)
            {
                *tempPtr = *(head + i);
                tempPtr++;
            }
            head = newHead;
            memSize = newMemSize;
        }
        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

      
        /*
            Function: changing the size of the vector
            Input: this vector
            Output: a new (maybe)larger vector
            Detail: if newSize is equal or larger than the memory size,
                    expand_memory() (for many times) is required.
                    else, don't need to change anything.
        ##############################################################       
        */
        void resize(int newSize)
        {
            int newMemSize = memSize;
            //expanding the memory space until it is bigger than the newSize.
            while(newSize >= newMemSize )
            {
                expand_memory();
                newMemSize = memSize;
            }
            this->len = newSize;
        }
        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


        //finding the begin position
        MyIterator begin() const
        {
            MyIterator it(head);
            return it;
        }

        //finding the end position
        MyIterator end() const
        {
            MyIterator it = begin();
            //the end position is just after the last content.
            for (int i = 0; i < len;i++)
            {
                it++;
            }
            return it;
        }

        /* 
        index reference
        ATTENTION: 
            We should make use of that the address 
            -of the contents are consecutive.
            don't use iterator to find the index reference,
            if so, why can't we use the same way to the list?
        POLISH:
            I use cerr to warn the invalid index
        */
        T &operator[](int itemOrder) const
        {
            const string INDEX_OUT_OF_RANGE_ERROR 
                = "ERROR: index out of range.";
            if( itemOrder >= len)
                cerr << INDEX_OUT_OF_RANGE_ERROR << endl;
            else
                return *(head + itemOrder);
            
        }


        /*
        getting the vector's head and memorysize and the length.
        A little bit troublesome because of the DATA CONCEALING
        */
        T* get_head() const
        {
            return head;
        }
        int get_memSize() const
        {
            return memSize;
        }

        int get_len() const
        {
            return len;
        }

        //getting the element from the front and the back of the vector
        T get_front() const
        {
            return *head;
        }

        T get_back() const
        {
            return *(head + len - 1);
        }


        //assignment for MyVectorb
        MyVectorb& operator=(const MyVectorb &mv) 
        {
            //replicating the length, memory size and the contents
            MyVectorb newMv( mv.get_len() );//seems unnecessary.
            head = newMv.get_head();
            resize(mv.get_len());

            MyIterator it1 = mv.begin();
            MyIterator it2 = this -> begin();
            while ( it1 != mv.end() )
            {
                *it2 = *it1;
                ++it1;
                ++it2;
            }
            return *this;
        }

        /*This push_back() may need the expand_memory()
        when the memory size is not bigger than the new size.
        And the worstTime is O(n) while the averageTime is O(1).
        #############################################################
        */
        void push_back(const T &inputItem)
        {
            //the memory size is large enough so we don't 
            //-have to allocate more spaces.
            if( len + 1 < memSize )
            {
                *(head + len) = inputItem;
                ++len;
            }
            
            // the memory space is not large enough.
            // so we have to allocate larger memory space
            //-create a new vector
            //-and replicate the original data.
            else
            {
                expand_memory();
                *(head + len) = inputItem;
                ++len;
            }
        }
        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        /*  
            TRAIT:
            compared with the push_back(),it just need to deduct the len by 1 
            to "delete the last element".
            So no space allocation is required.
            ATTENTION_1 :  
            if there is no element in the vector,it will print out
            the error "ERROR: no element in myVectorb, fail to pop back."
        #################################################################
        */
        void pop_back()
        {
            //don't need to use cerr because this error is not that big
            //-and just give out the warning is fine.
            const string LEN_IS_0_WARNING 
                = "ERROR: no element in myVectorb, fail to pop back.";
            if( len == 0 ) 
            {
                cout << LEN_IS_0_WARNING << endl;
            }
            
            //IF this is "pop_backable", let the len-- to make 
            //-visiting the last element illegal
            else
            {
                --len;
            }
        }
        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        friend ostream& operator<<(ostream& out,const MyVectorb& myvector)
        {
            for ( MyVectorb<T>::MyIterator itr = myvector.begin();
                 itr != myvector.end();++itr )
            {
                out << *itr << endl;
            }
            return out;
        }

        //destructor to delete MyVectorb
        ~MyVectorb()
        {
            delete []head;
        } 
       
};

#endif