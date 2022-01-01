#include "myBBST.h"
#include <iostream>
using namespace std;
int main()
{
    bool istaller = false;
    BBSTNode *T = nullptr;
    for (int i = 5; i >=1; --i)
    {
        if( !insertAVL(T,i,istaller) )
            cout << "fail insert.\n";
    }
    cout << "the sequence is : \n";
    inOrderTraverse(T);
    cout << endl;
    cout << "the level order is : \n";
    levelOrderTraverse(T);
    return 0;
}