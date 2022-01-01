//in order to suit the expression tree whose node can contain a 
//- multi-digit number, I have to change the data type of the node 
//- from char to string to express that number.
#ifndef MYBITREE
#define MYBITREE
#include <iostream>
#include <string>
#include <queue>
using namespace std;
// the binary tree for the char
struct BiTNode
{
    string data;
    BiTNode *lchild, *rchild;
};

//declaration for those recursive functions
BiTNode *preOrderCreate(const string &inputString, const char &invalidChar);
//BiTNode *levelOrderCreate(const string &inputString, const char &invalidChar);
void preOrderTraverse(BiTNode *T);
void inOrderTraverse(BiTNode *T);
void postOrderTraverse(BiTNode *T);
void levelOrderTraverse(BiTNode *T);
void deleteBiTNode(BiTNode *T);
void getLeafNum(BiTNode *T,int &count);
//trivial functions
/*
void deleteXSubTree(BiTNode *T,const char& X);
bool findPreOrderKnode(BiTNode *T,const int& k, char &element, int &count);
bool judge_complete(BiTNode *T);
*/
class MyBiTree
{
    protected:
        BiTNode *root;
    public:
        /*  since the constructor can not be in a recursive process,
        we need to put another recursive function in it. */
         MyBiTree()
        {
            root = new BiTNode;
        }
        //constructor inputting a string to generate a binary tree in a preorder way.
        MyBiTree(const string &inputString)
        {
            root = preOrderCreate(inputString,'#');
            //root = levelOrderCreate(inputString, '#');
        }
        
        /*copy constructor by inputting the root ptr
        MyBiTree(BiTNode *inputRoot)
        {
            root = new BiTNode;
        }
        */
        void pre_Order_Traverse() const   { preOrderTraverse(root); }
        void in_Order_Traverse() const  { inOrderTraverse(root); }
        void post_Order_Traverse() const  { postOrderTraverse(root); }
        void level_Order_Traverse() const { levelOrderTraverse(root); }
        int leaf_num() const;
        BiTNode *get_root() const { return root; }
        ~MyBiTree()    { deleteBiTNode(root); }
};

//returning the number of the leaf node
int MyBiTree::leaf_num() const
{
    int count = 0;
    getLeafNum(root, count);
    return count;
}

//declaration for some other functions
void visit(string data)
{
    cout << data << " ";
}

/* using recursion to create a binary tree in a preOrder sequence.
a node can store a char, and using ' ' as a separate character.*/
BiTNode* preOrderCreate(const string & inputString,const char & invalidChar = '#')
{
    static int index = 0;
    BiTNode *tempNode = nullptr;
    if(index >= inputString.length())
    {
        return nullptr;
    }
    char ch = inputString[index];
    if(ch != invalidChar)
    {
        tempNode = new BiTNode;
        string s;
        s += ch;
        tempNode->data = s;
        ++index;
        tempNode -> lchild = preOrderCreate(inputString,invalidChar);
        ++index;
        tempNode -> rchild = preOrderCreate(inputString,invalidChar);
    }
    return tempNode;
}

//a recursive function to traverse the tree in a preorder.
//sequence is 1.root    2.left child    3.right child
void preOrderTraverse(BiTNode *T)
{
    if(T)
    {
        visit(T->data);
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

//a recursive function to traverse the tree in an inorder.
//sequence is 1.left child    2.root    3.right child
void inOrderTraverse(BiTNode *T)
{
    if(T)
    {
        inOrderTraverse(T->lchild);
        visit(T->data);
        inOrderTraverse(T->rchild);
    }
}

//a recursive function to traverse the tree in a postorder.
//sequence is 1.left child    2.right child      3.root
void postOrderTraverse(BiTNode *T)
{
    if(T)
    {
        postOrderTraverse(T->lchild);
        postOrderTraverse(T->rchild);
        visit(T->data);
    }
}

//a non-recursive function to traverse the tree in a level order.
//like bfs,we need to use a queue.
void levelOrderTraverse(BiTNode *T)
{
    queue<BiTNode*> nodeQueue;
    if(T != nullptr )
    {
        //firstly,push the root into the queue
        nodeQueue.push(T);
        while( !nodeQueue.empty() )
        {
            /*for each node, 1. visit it
            2.visit its left child  3.visit its right child
            then we can visit its sibling child
            (if that node is the last one of that level, we can
             visit the first node in the next level)
            */
            BiTNode* tempNode = nodeQueue.front();
            visit(tempNode->data);
            nodeQueue.pop();
            if(tempNode->lchild != nullptr)
                nodeQueue.push( tempNode -> lchild );
            if(tempNode->rchild != nullptr)
                nodeQueue.push( tempNode -> rchild );
        }//while( !nodeQueue.empty() )
    }//if(T != nullptr )
}

//using recursion to get the number of leaf node
// a node is a leaf iff its leftchild and rightchild are all null
void getLeafNum(BiTNode *T,int & count)
{
    if( T != nullptr )
    {
        getLeafNum( T -> lchild,count);
        getLeafNum(T -> rchild,count);
        if (T->lchild == nullptr && T->rchild == nullptr)
            ++count;
    }   
}

//delete the the tree in a post order.
void deleteBiTNode(BiTNode *T)
{
    if(T)
    {
        deleteBiTNode(T->lchild);
        deleteBiTNode(T->rchild);
        delete T;
        T = nullptr;
    }
}

/*
//delete the subtree whose root is the node with data X.
//using the preorder traversing
//PAY ATTENTION: if we just delete the T whose data is X,
// then we need to make the childptr of T's parent null.
//so I choose to delete in advance.
void deleteXSubTree(BiTNode *T,const char& X)
{
    //considering that the root is null 
    if(T == nullptr)
        return;
    //considering that root->data = X.
    if(T && T -> data == X )
    {
        deleteBiTNode(T);
        return;
    }
    if(T -> lchild != nullptr)
    {
        if(T->lchild->data == X)
        {
            deleteBiTNode(T->lchild);
            T->lchild = nullptr;
        }
        else
            deleteXSubTree(T->lchild, X);
    }
    if(T->rchild!= nullptr)
    {
        if(T->rchild->data == X)
        {
            deleteBiTNode(T->rchild);
            T->rchild = nullptr;
        }
        else
        {
            deleteXSubTree(T->rchild,X);
        }
    }
}

//find the k th node in pre order.(with recursion)
//if ture, reference variavle element is that data
// if false, the number of node is less than k.
bool findPreOrderKnode(BiTNode *T,const int& k, char &element, int &count)
{
    if( T == nullptr)
        return false;
    ++count;
    if(count > k)
        return false;
    else if(count == k)
    {
        element = T->data;
        return true;
    }
    else// count < k,keep on searching in a preOrder.
    {
        if( !findPreOrderKnode(T->lchild,k,element,count) )
            return findPreOrderKnode(T->rchild, k, element, count);
        return true;
    }
}
*/
/*
bool judge_complete(BiTNode *T)
{

}
*/
#endif