#include "myVectorb.h"

 /*
        DEFAULT CONSTRUCTOR
        given the length, and it will construct 
        a vector with 0 as default content.
        #####################################################################
        PAY ATTENTION: IF THE DATA IS A STRING
        -IT WILL BE DANGEROUS BECAUSE 0 MEANS NULLSTRING.
        */

//HAVING SOME PROBLEMS THAT I CAN'T DIRECTLT USE THIS FUNCTION!!!!!
template<class T>
MyVectorb<T>::MyVectorb(int vlen)
{
    // In this situation, we don't have to expand the memory size.
    if( vlen < ORIGINAL_MEMORY_SIZE )
    {
        memSize = ORIGINAL_MEMORY_SIZE;
        T *array = new T[memSize];
        head = array;
        len = vlen;
    }

    // if the length is too big, multiply the memory size continuously
    //-until it is bigger than the length.
    else
    {
        int tempMemSize = ORIGINAL_MEMORY_SIZE;
        while(vlen >= tempMemSize )
            tempMemSize *= 2;
        memSize = tempMemSize;
        T *array = new T[memSize];
        head = array;
        len = vlen;
    }
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

/*
    REPEATING CONSTRUCTOR
    #####################################################################
    inputing the length and the inputdata,
    and it will construct a vector with inputdata of the number of length.
    ATTENTION: THE reason why I write two constructor functions is because
            the default value of inputData can't be 0(dangerous if T is string)
*/
template<class T>
MyVectorb<T>::MyVectorb(int vlen, T inputData)
{
    // In this situation, we don't have to expand the memory size.
    if( vlen < ORIGINAL_MEMORY_SIZE )
    {
        memSize = ORIGINAL_MEMORY_SIZE;
        T * newHead = new T[memSize];
        head = newHead;
        len = vlen;
        T* tempPtr = newHead;
        for (int i = 0; i < vlen;i++)
        {
            *tempPtr = inputData;
            tempPtr++;
        }
    }

    // if the length is too big, multiply the memory size continuously
    //-until it is bigger than the length.
    else
    {
        int tempMemSize = ORIGINAL_MEMORY_SIZE;
        while(vlen >= tempMemSize )
            tempMemSize *= 2;
        memSize = tempMemSize;
        T * newHead = new T[memSize];
        head = newHead;
        len = vlen;
        T* tempPtr = newHead;
        for (int i = 0; i < vlen;i++)
        {
            *tempPtr = inputData;
            tempPtr++;
        }
    }
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$