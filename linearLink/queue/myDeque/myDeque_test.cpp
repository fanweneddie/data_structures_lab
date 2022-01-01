#include "myDeque.cpp"
#include <iostream>
using namespace std;


int main()
{
    MyDeque<int> numList1(11,1), numList2;
    cout << "constructor!\n";
    cout << "the len of numList1 is " << numList1.get_len() << endl;
    cout << "the start of numList1 is " << numList1.get_start() << endl;
    cout << "the first of start of numList is " << numList1.get_start()->first << endl;
    cout << "the firstPos of numList1 is " << numList1.get_firstPos() << endl;
    /*
    MyDeque<int>::MyIterator itr1 = numList1.begin();
    cout << "the pos of begin itr is " << itr1.get_currentPtr() << endl;
    cout << "the lastPos of numList1 is " << numList1.get_lastPos() << endl;
*/
    //int i = 0;
    cout << "are you okay?\n";
    /*
    MyDeque<int>::MyIterator itr2 = numList1.end();
    cout << "the lastPos of numList1 is " << numList1.get_lastPos() << endl;
    cout << "the end is " << itr2.get_currentPtr() << endl;
    for (; itr1 != itr2;itr1++)
    {
        *itr1 = i;
        cout << "the " << i << " th element is " << *itr1 << endl;
        cout << "index: the " << i << " th element is "
         << numList1[i] << endl;
        i++;
    }
    //numList2 = numList1;
    cout << "successfully assignment.\n";
    i = 0;
    */
    
    /*    
    cout << "the printing the numList2.\n";
    MyDeque<int>::MyIterator itr3 = numList2.begin(), itr4 = numList2.end();
    for (; i<=7;i++)
    {
        cout << "the " << i << " th element is " << *itr3 << endl;
    }
    */
}
