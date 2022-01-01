#include <iostream>
#include "circularQueue.h"
using namespace std;

void test()
{
    CircularQueue<int> cq1;
    for (int i = 0; i < 5;++i)
    {
        cq1.enQueue(i);
    }
    int temp = 0;
    cout << "now printing this queue.\n";
    cout << "the size of the queue is " << cq1.get_size() << endl;
    CircularQueue<int> cq2(cq1);
    while( ! cq2.is_empty() )
    {
        temp = cq2.get_frontElement();
        cq2.deQueue();
        cout << temp << endl;
    }
}

int main()
{
    test();
    return 0;
}