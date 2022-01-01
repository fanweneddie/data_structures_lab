#include <iostream>
#include <array>
using namespace std;

int main()
{
    array<int,3> myInt = {1,2,3};
    array<int, 3>::reverse_iterator itrBegin, itrEnd;
    for (itrBegin = myInt.rbegin(), itrEnd = myInt.rend();
         itrBegin != itrEnd;itrBegin++)
        cout << *itrBegin << endl;
    return 0;
}