#include "myBiTree.h"

// abc##de#g##f###
void test()
{
    string input;
    cout << "please input a string.\n";
    //input = "-+a##*b##-c##d##/e##f##";
    cin >> input;
    MyBiTree t1(input);
    cout << "finish constructing.\n";
    
    cout << "now traversing the tree in a preorder way.\n";
    t1.pre_Order_Traverse();
    cout << "\nnow traversing the tree in a inorder way.\n";
    t1.in_Order_Traverse();
    cout << "\nnow traversing the tree in a postorder way.\n";
    t1.post_Order_Traverse();
    cout << "\nnow traversing the tree in a levelorder way.\n";
    t1.level_Order_Traverse();
    /*
    cout << "\nthere are " << t1.leaf_num() << " leaves in t1.\n";
    cout << "now traversing the tree in a preorder way.\n";
    t1.pre_Order_Traverse();
    deleteXSubTree(t1.get_root(), '*');
    cout << "\nafter deleting a subtree.\n";
    cout << "now traversing the tree in a preorder way.\n";
    t1.pre_Order_Traverse();
*/
}

int main()
{
    test();
    cout << "\nDONE!!!\n";
    return 0;
}