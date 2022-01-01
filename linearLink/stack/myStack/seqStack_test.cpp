#include <iostream>
#include "seqStack.cpp"
using namespace std;

void test()
{
    
    int element = 0;
    SeqStack<int> ss1;
    try
    {
        for (int i = 0; i < 30;++i)
        {
            ss1.push(i);
        }
        cout << "now started\n";
        element = ss1.get_top();
        cout << "the top element is " << element << endl;
        cout << "the size is " << ss1.get_size() << endl;
        cout << "the capacity is " << ss1.get_capacity() << endl;
        cout << "now clear the stack.\n";
        ss1.clear();
        element = ss1.pop();
        cout << "end\n";
    }

    catch(const char* s)
    {
        cout << s;
        cout << "haha\n";
    }

}

int main()
{
    test();
    return 0;
}