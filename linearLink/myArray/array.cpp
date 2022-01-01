#include "array.h"
#include <iostream>

//general constructor
template<class T>
Array<T>::Array(int size)
{
    assert(size);
    // if size is 0, then it will exit
    aSize = size;
    aList = new T[size];
}

//copying constructor(deep replication)
template <class T>
Array<T>::Array(const Array<T>& arr1)
{
    aSize = arr1.aSize;
    aList = new T[aSize];
    for (int i = 0;i<aSize;++i)
    {
        aList[i] = arr1.aList[i];
    }
}

//destructor
template <class T>
Array<T>::~Array()
{
    delete[] aList;
}

// using "=" to value as a whole
template <class T>
Array<T>& Array<T>::operator=(const Array<T> &array)
{   
    if( &array != this )
    {
        if(array.aSize != this->aSize)
        {
            delete[] aList;
            aSize = array.aSize;
            aList = new T[aSize];
        }
        for (int i = 0; i < aSize;i++)
        {
            this->aList[i] = array.aList[i];
        }
    }
    return *this;
}
       
//using index to get the value
template <class T>
T& Array<T>::operator[](int k)
{
    assert(k>=0);
    assert(k < aSize);
    return aList[k];
}

//comparing two arrays
template <class T>
bool Array<T>::operator>(const Array<T> &array) const
{
    int size1 = this->get_size();
    int size2 = array.get_size();
    int minSize = size1 < size2 ? size1 : size2;
    for (int i = 0; i < minSize;i++)
    {
        if (this->aList[i] > array.aList[i])
            return true;
    
        if( this->aList[i] < array.aList[i] )
            return false;
    }
    if(size1>size2)
        return true;
    else
        return false;
}

template <class T>
bool Array<T>::operator<(const Array<T> &array) const
{
    int size1 = this->get_size();
    int size2 = array.get_size();
    int minSize = size1 < size2 ? size1 : size2;
    for (int i = 0; i < minSize;i++)
    {
        if( this->aList[i] < array.aList[i] )
            return true;
    
        if( this->aList[i] > array.aList[i] )
            return false;
    }
    if(size1<size2)
        return true;
    else
        return false;
}

template <class T>
bool Array<T>::operator == (const Array<T> &array) const
{
    int size1 = this->get_size();
    int size2 = array.get_size();
    if(size1 != size2)
        return false;
    for (int i = 0; i < size1;i++)
    {
        if( this->aList[i] != array.aList[i] )
            return false;
    }
    return true;
}

//getting the size
template <class T>
int Array<T>::get_size()const
{
    return aSize;
}       


//changing the size of the array.
template <class T>
void Array<T>::resize(int newSize) 
{
    assert(newSize >= 0);
    if(newSize != aSize)
    {
        int minSize = newSize < aSize ? newSize : aSize;
        T* newList = new T[newSize];
        for (int i = 0; i < minSize;++i)
        {
            newList[i] = aList[i];
        }
        delete[] aList;
        aList = newList;
        aSize = newSize;        
    }   
}

template <class T>
bool Array<T>::is_empty()const
{
    if(this->get_size() == 0)
        return true;
    else
        return false;
}


int main()
{
    using namespace std;
    Array<int> arr1(5);
     Array<int> arr2(5);
    for (int i = 0; i < 5;i++)
    {
        arr1[i] = i;
    }

    int size1= arr1.get_size();

    for (int i = 0; i < size1;i++)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;
    arr2 = arr1;
    
    arr2.resize(4);
    int size2 = arr2.get_size();
    for (int i = 0; i < size2;i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    if(arr1 > arr2 )
        cout << "arr1 > arr2" << endl;
    if(arr1 < arr2 )
        cout << "arr1 < arr2 " << endl;
}
