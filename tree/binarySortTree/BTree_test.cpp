#include "BTree.h"
int main()
{
    BTNode *T = nullptr;
    int a[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5;++i)
    {
        cout << "debug00:now enter the for loop and i = " << i << endl;
        Result result = searchBTree(T, a[i]);
        cout << "debug02: after the search, the index is " << result.index << endl;
        cout << "debug03: after the search, the is found is " << ( result.found ? "true" : "false" ) << endl;
        if(result.found == false)
            InsertBTree(T, result.index, a[i], result.ptr);
        cout << "STEP " << i << " : insert element " << a[i] << endl;
        traverseBTree(T);
        cout << "debug01: after the Btree traverse.\n";
    }
    return 0;
}