#include "myVectorb.h"

void test()
{
    //check the constructor
    MyVectorb vector1(3,1);
    /*
    however, one constructor is invalid 
     that is   MyVectorb vector2(4);
    */

    //check get_len()
    int length1 = vector1.get_len();
    cout << "the length of vector1 is " 
        << length1 << endl;
   
    //check get_memSize()
    int memorySize = vector1.get_memSize();
    cout << "the memory size of vector1 is " 
        << memorySize << endl;
    
    //check expand_memory()
    vector1.expand_memory();
    memorySize = vector1.get_memSize();
    cout << "after the memory expansion, \n";
    cout << "the memory size of vector1 is " 
        << memorySize << endl;

    //check the [] operator
    cout << "\nnow outputting the vector1:\n";
    for (int i = 0; i < length1;i++)
    {
        cout << "the " << i <<" th element is: "
             << vector1[i] << endl;
    }

    //make sure the [] reference is fine
    cout << "\nnow outputting the vector1 after a change:\n";
    for (int i = 0; i < length1;i++)
    {
        vector1[i]  = vector1[i] + i;
    }

    for (int i = 0; i < length1;i++)
    {
        cout << "the " << i <<" th element is: "
             << vector1[i] << endl;
    }
    //check the friend operator<<
    cout << "ANOTHER WAY TO OUTPUT." << endl;
    cout << vector1 ;
    //check the iterator
    
    cout << "output the vector1 by iterator\n";
    MyVectorb<int>::MyIterator itr = vector1.begin();
    cout << "debug1 " << endl;
    cout << (vector1.begin().get_ptr()) << endl;

    cout << "DEBUG1.1: the value of itr : " << *itr << endl;
    cout << "DEBUG1.2: itr's pointer: " << itr.get_ptr() << endl;
    itr++;
    cout << "DEBUG1.3: the value: " << *itr << endl;
    cout << "DEBUG1.4: itr's pointer: " << itr.get_ptr() << endl;
    
    cout << "debug2 " << endl;
    
    length1 = vector1.get_len();
    cout << "debug0: the length1 is " << length1 << endl;
    while(itr != vector1.end() )
    {
        cout << "the element of vector1 is " << *itr << endl;
        itr++;
    }
    
    //check resize
    vector1.resize(20);
    cout << "after resize:" << endl;
    itr = vector1.begin();
    while(itr != vector1.end() )
    {
        cout << "the element of vector1 is " << *itr << endl;
        itr++;
    }

    length1 = vector1.get_len();
    memorySize = vector1.get_memSize();
    cout << "later, the length is " << length1 << endl;
    cout << "later, the memory size is " << memorySize << endl;

    while(itr != vector1.end())
    {
        cout <<  *itr << endl;
        cout << "debug4" << endl;
        ++itr;
    }
    
    //check get_front() and get_back()
    cout << "the first element of vector1 is: "
         << vector1.get_front() << endl;

     cout << "the last element of vector1 is: "
         << vector1.get_back() << endl;


    //check assignment operator= 
    MyVectorb vector2(2, 2);
    int length2 = vector2.get_len();
    cout << "originally, the length of vector2 is: "
         << length2 << endl;
    vector2 = vector1;
    length2 = vector2.get_len();
    cout << "after the assignment, the length of vector2 is: "
         << length2 << endl;
    for (int i = 0; i < length2;i++)
    {
        cout << "the " << i <<" th element of vector2 is: "
             << vector1[i] << endl;
    }
    
    //check push_back()
    for (int i = 0; i < 4; i++)
    {
        vector1.push_back(i);
    }
    length1 = vector1.get_len();
    cout << "after the push_back(), the length of vector1 is: "
         << length1 << endl;
    for (int i = 0; i < length1;i++)
    {
        cout << "the " << i <<" th element of vector1 is: "
             << vector1[i] << endl;
    }

    //checking pop_back()
    for (int i = 0; i < 2; i++)
    {
        vector1.pop_back();
    }
    length1 = vector1.get_len();
    cout << "after the pop_back(), the length of vector1 is: "
         << length1 << endl;
    for (int i = 0; i < length1;i++)
    {
        cout << "the " << i <<" th element of vector1 is: "
             << vector1[i] << endl;
    }
    //destructor has been checked!!
}

int main()
{
    test();
    return 0;
}        