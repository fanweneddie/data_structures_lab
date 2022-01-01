#include <queue>
#include <iostream>
using namespace std;

int main()
{
    queue<int> nums;
    for (int i = 0; i < 5;i++)
        nums.push(i);

    for (int i = 0; i < 5;i++)
    {
        cout << nums.front() << endl;
        nums.pop();
    }
}