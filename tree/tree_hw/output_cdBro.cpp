//include the ADT of the binary tree.
#include "../mytreeADT/myBiTree.h"
//before print the data of the node, print blankspace_Num blank spaces.
//at last,print an endl;
void visit_node(BiTNode* nodePtr,int blankSpace_Num)
{
    for (int i = 0; i < blankSpace_Num;++i)
        cout << " ";
    cout << nodePtr->data << endl;
}

//using the preOrder traverse to output an indentation table.
//T is a node of a child_brother binary tree.
void pre_output(BiTNode* T,int blankSpace_Num)
{
    if(T)
    {
        visit_node(T, blankSpace_Num);
        // for the lchild(first child ) the indent is needed
        pre_output(T->lchild, blankSpace_Num + 1);
        //for the rchild(next sibling) the indent is not needed.
        pre_output(T->rchild, blankSpace_Num);
    }
}

void test()
{
    string input;
    //cout << "please input a string.\n";
    input = "ABE#F##CG##D##";
    //cin >> input;
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
    cout << "\nnow output the chart to represent this tree.\n";
    pre_output(t1.get_root(), 0);
}

int main()
{
    test();
    return 0;
}
