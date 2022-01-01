#ifndef ARRAY
#define ARRAY

#include <cassert>

template<class T>
class Array
{
    protected:
        T* aList;
        int aSize;
    public:
        //general constructor
        Array(int size = 10);
        //copy constructor
        Array(const Array<T> &arr1);
        ~Array();

        // using "=" to value as a whole
        Array<T>& operator=(const Array<T> &arr1); 
        
        //using index to get the value
        T &operator[](int k);
        
        //comparing two arrays
        bool operator > (const Array<T> &array) const;
        bool operator < (const Array<T> &array) const;
        bool operator==(const Array<T> &array) const;
    
        //getting and changing the size of the array.
        int get_size() const;
        void resize(int newSize);
       
        bool is_empty() const;
        /*actually, for an array, it is hard to check whether 
        empty or full because the size is fixed 
        and the value is not certain. 
        */
};

#endif
