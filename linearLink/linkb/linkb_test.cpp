#include "linkb.h"
#include <iostream>
using namespace std;

int main()
{
    Linkb<double> link1(5);
    Linkb<double> link2;
    link2.create();
    cout << "the size of link2 is " << link2.get_size() << endl;
    if( link2.is_full() )
        cout << "link2 is full" << endl;
    else
        cout << "link2 is not full" << endl;
    
    int size2 = link2.get_size();
    for (int i = 0; i < size2;++i)
    {
        cout << link2[i] << endl;
    }
    double num1 = 2.0;
    cout << link2.find_first_of_item(num1)<< endl;
}