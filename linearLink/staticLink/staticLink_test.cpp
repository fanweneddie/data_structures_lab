#include <iostream>
#include "staticLink.h"
using namespace std;

void test()
{
    StaticLink<int> sl;
    int start = sl.malloc_space();
    int tempPos1 = start, tempPos2;
    for (int i = 0; i < 5;i++)
    {
        tempPos2 = sl.malloc_space();
        sl.head[tempPos1].cursor = tempPos2;
        tempPos1 = tempPos2;
        sl.head[tempPos2].data = 3 * i;
    }
    cout << "the result:\n";
    tempPos1 = sl.head[start].cursor;
    for (int i = 0; i < 5;i++)
    {
        cout << sl.head[tempPos1].data << endl;
        tempPos1 = sl.head[tempPos1].cursor;
    }
}

int main()
{
    test();
}