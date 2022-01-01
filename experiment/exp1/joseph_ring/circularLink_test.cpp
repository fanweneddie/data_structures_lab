#include <iostream>
#include "circularLink.h"
using namespace std;

int main()
{
    CircularLink<int> cl;
    for (int i = 1; i <= 5;++i)
    {
        cl.push_back(i, i + 10);
    }

    cl.insert(0, 30, 40);
    Node<int> *ptr = cl.get_head() ->next;
    cl.erase(ptr);
    cout << "ok?\n";
    ptr = cl.get_head()->next;
    while (ptr != cl.get_head())
    {
        cout << "the first data of the node is " << ptr->data1 << endl;
        cout << "the second data of the node is " << ptr->data2 << endl;
        ptr = ptr->next;
    }
}