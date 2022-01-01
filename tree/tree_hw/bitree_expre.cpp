//include the ADT of the binary tree
#include "../mytreeADT/myBiTree.h"

//compare the priority of two operators
//if one of the two inputs is not an operator, we will return 0
//      (as if nothing happens because we don't need to add bracket.)
//if prio: optra > optrb , then return 1 ; 
//if prio: optra < optrb , then return -1 ;
int cmp_priority(char optra,char optrb)
{
    if( ( optra == '+' || optra == '-') && ( optrb == '*' || optrb == '/') )
        return -1;
    else if( ( optra == '*' || optra == '/') && ( optrb == '+' || optrb == '-') )
        return 1;
    else
        return 0;
}

/*  input a binary tree representing an expression, 
    use the inorder way to output it (adding bracket is needed to be done)
*/
void inOrderTraverse_bracket(BiTNode* T)
{
    //note that operator's node has lchild and rchild
    // operand's node's lchild and rchild are both null.
    if(T) 
    {
        int bracketFlag = 0;
        // means that T is an operator
        if(T->lchild)
        {
            //compare the priority of this operator and the operator in its connecting item.
            bracketFlag = cmp_priority(T->data, T->lchild->data);
            // if the prio of the former one is bigger, we need to add bracket for its first item
            //before we cout the item, we cout '(' first
            if(bracketFlag == 1)
                cout << "(";
            inOrderTraverse_bracket(T->lchild);
            //after we cout the item, we cout '(' at last.
            if(bracketFlag == 1)
                cout << ")";
        }//if(T->lchild)

        cout << T->data;
        
        if(T->rchild)
        {
            // the same dealing for rchild
            bracketFlag = cmp_priority(T->data, T->rchild->data);
            if(bracketFlag == 1)
                cout << "(";
            inOrderTraverse_bracket(T->rchild);
            if(bracketFlag == 1)
                cout << ")";
        }//if(T->rchild)
    }//if(T) 
}


// abc##de#g##f###
void test()
{
    string input;
    input = "-+a##*b##-c##d##/e##f##";
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
    cout << "\n now adding the bracket for the inorder expression.\n";
    inOrderTraverse_bracket(t1.get_root());
}

int main()
{
    test();
    cout << "\nDONE!!!\n";
    return 0;
}
