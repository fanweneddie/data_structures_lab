#include "thdBiTree.h"

void test()
{
    string input;
    cout << "please input a string.\n";
    //input = "-+a##*b##-c##d##/e##f##";
    //input = "ABC#DEFG##H######";
    cin >> input;
    MyBiThrTree t1(input);
    cout << "finish constructing.\n";
    cout << "now traversing the tree in a preorder way.\n";
    t1.pre_Order_Traverse();
    cout << "\nnow traversing the tree in a inorder way.\n";
    t1.in_Order_Traverse();
    cout << "\nnow traversing the tree in a postorder way.\n";
    t1.post_Order_Traverse();
    cout << "\nnow travsering the tree in a threading inorder sequence.\n";
    t1.inOrderThrTraverse();
}

int main()
{
    test();
    return 0;
}