#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    vector<string> fruits = {"apple","banana","pear","orange","avacardo"};
    cout << fruits[0] << endl;
    cout << fruits[4] << endl;
    while( !fruits.empty() )
    {
        fruits.pop_back();
        cout << "hi" << endl;
    }
}