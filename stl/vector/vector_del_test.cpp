#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    vector<int> v1{1,2,3,4,5};
    vector<int> v2{11, 12, 13, 14, 15};
    cout << "v1.data: " << v1.data() << endl;
    for (auto iter1 = v1.begin(); iter1 != v1.end();iter1++)
    {
        cout << *iter1 << " ";
    }
    cout << endl;

    cout << "v2.data: " << v2.data() << endl;
    for (auto iter2 = v2.begin(); iter2 != v2.end();iter2++)
    {
        cout << *iter2 << " ";
    }
    
    cout << endl <<endl;
    v1.swap(v2);
    cout << "after swap:" ;
    cout << "v1.data: " << v1.data() << endl;
    for (auto iter1 = v1.begin(); iter1 != v1.end();iter1++)
    {
        cout << *iter1 << " ";
    }
    cout << endl;

    cout << "v2.data: " << v2.data() << endl;
    for (auto iter2 = v2.begin(); iter2 != v2.end();iter2++)
    {
        cout << *iter2 << " ";
    }
    cout << "\nthis is index reference " << v2[1] << endl;
    return 0;
}