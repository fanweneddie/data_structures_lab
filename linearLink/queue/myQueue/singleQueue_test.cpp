#include "singleQueue.cpp"
void test()
{
    SingleQueue<int> que1;
    for (int i = 0; i < 10;++i)
    {
        que1.enQueue(i);
        cout << "now the len of que1 is " << que1.get_len() << endl;
        cout << "the front element is " << que1.get_frontEle() << endl;
    }

    while( ! que1.is_empty() )
    {
        que1.deQueue();
        cout << "now the front element is " << que1.get_frontEle() << endl;
    }
}

int main()
{
    test();
    return 0;
}