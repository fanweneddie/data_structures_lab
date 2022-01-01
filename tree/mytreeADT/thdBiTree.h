#ifndef THDBITREE
#define THDBITREE
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// the threading binary tree for the char
enum PointerTag
{
    link,
    thread
};
struct BiThrTNode
{
    char data;
    BiThrTNode *lchild, *rchild;
    PointerTag Ltag, Rtag;
};

BiThrTNode *pre = nullptr;
//declaration for those recursive functions
BiThrTNode *preOrderCreate(const string &inputString, const char &invalidChar);
BiThrTNode *levelOrderCreate(const string &inputString, const char &invalidChar);
void preOrderTraverse(BiThrTNode *T);
void inOrderTraverse(BiThrTNode *T);
void postOrderTraverse(BiThrTNode *T);
void levelOrderTraverse(BiThrTNode *T);
void deleteBiThrTNode(BiThrTNode *T);
void inThreading(BiThrTNode *origPtr);
BiThrTNode *inOrderThreading(BiThrTNode *rootNode, BiThrTNode *headNode);

class MyBiThrTree
{
    private:
        BiThrTNode *root;
        BiThrTNode *thrt;

    public:
        /*  since the constructor can not be in a recursive process,
        we need to put another recursive function in it. */
         MyBiThrTree()
        {
            root = new BiThrTNode;
            thrt = new BiThrTNode;
        }
        MyBiThrTree(const string &inputString)
        {
            root = levelOrderCreate(inputString,'#');
            thrt = new BiThrTNode;
        }
        void pre_Order_Traverse() const   { preOrderTraverse(root);cout << endl;}
        void in_Order_Traverse() const  { inOrderTraverse(root);cout << endl;}
        void post_Order_Traverse() const  { postOrderTraverse(root);cout << endl;}
        void level_Order_Traverse() const { levelOrderTraverse(root);cout << endl;}
        void inOrderThrTraverse();
        BiThrTNode *get_root() const { return root; }
        BiThrTNode *get_thrt() const { return thrt; }
        ~MyBiThrTree()    { deleteBiThrTNode(root); }
};

//declaration for some other functions
void visit(char data)
{
    cout << data << " ";
}

/* using recursion to create a binary tree in a preOrder sequence.
a node can store a char, and using ' ' as a separate character.*/
BiThrTNode* preOrderCreate(const string & inputString,const char & invalidChar = '#')
{
    static int index;
    BiThrTNode *tempNode = nullptr;
    if(index >= inputString.length())
    {
        return nullptr;
    }
    char ch = inputString[index];
    if(ch != invalidChar)
    {
        tempNode = new BiThrTNode;
        tempNode->data = ch;
        ++index;
        tempNode -> lchild = preOrderCreate(inputString,invalidChar);
        ++index;
        tempNode -> rchild = preOrderCreate(inputString,invalidChar);
    }
    return tempNode;
}

/* using recursion to create a binary tree in a levelOrder sequence.
a node can store a char, and using the invalidchar(such as '#') as a separate character.*/
BiThrTNode* levelOrderCreate(const string & inputString,const char & invalidChar = '#')
{
    int index = 0;
    queue<BiThrTNode*> nodeQueue;
    if ( inputString[index]  == invalidChar)
        return nullptr;
    BiThrTNode *tempNode1 = new BiThrTNode;
    tempNode1->Ltag = link;
    tempNode1->Rtag = link;
    BiThrTNode *rootNode = tempNode1;
    tempNode1->data = inputString[index];
    nodeQueue.push(tempNode1);
    while( !nodeQueue.empty() )
    {
        tempNode1 = nodeQueue.front();
        nodeQueue.pop();
        //consider the left child
        ++index;
        if( inputString[index] == invalidChar )
        {
            tempNode1->lchild = nullptr;
        }
        else
        {
            BiThrTNode *tempNode2 = new BiThrTNode;
            tempNode2->Ltag = link;
            tempNode2->Rtag = link;
            tempNode2->data = inputString[index];
            tempNode1->lchild = tempNode2;
            nodeQueue.push(tempNode2);
        }
        //consider the right child
        ++index;
        if( inputString[index] == invalidChar )
        {
            tempNode1->rchild = nullptr;
        }
        else
        {
            BiThrTNode *tempNode2 = new BiThrTNode;
            tempNode2->Ltag = link;
            tempNode2->Rtag = link;
            tempNode2->data = inputString[index];
            tempNode1->rchild = tempNode2;
            nodeQueue.push(tempNode2);
        }
    }//while( !nodeQueue.empty() )
    return rootNode;
}


//using the thread binary tree to inOrder traverse in 
// - a non recursive way.
//once we have let it with thread, it is not ok to use the recursive 
// traverse. since the lchild  and rchild have both changed.
void MyBiThrTree::inOrderThrTraverse()
{
    thrt = inOrderThreading(root,thrt);
    BiThrTNode *tempPtr = thrt -> lchild;
    while( tempPtr != thrt)
    {
        while( tempPtr -> Ltag == link)
        {
            tempPtr = tempPtr -> lchild;
        }
        // go to the bottom of the left child
        visit(tempPtr -> data);
        while(tempPtr -> Rtag == thread && tempPtr -> rchild != thrt)
        {
            tempPtr = tempPtr -> rchild;
            visit(tempPtr->data);
        }
        tempPtr = tempPtr -> rchild;
    }
}

//a recursive function to traverse the tree in a preorder.
//sequence is 1.root    2.left child    3.right child
void preOrderTraverse(BiThrTNode *T)
{
    if(T)
    {
        visit(T->data);
        if(T->Ltag == link )
            preOrderTraverse(T->lchild);
        if(T->Rtag == link)
            preOrderTraverse(T->rchild);
    }
}

//a recursive function to traverse the tree in an inorder.
//sequence is 1.left child    2.root    3.right child
void inOrderTraverse(BiThrTNode *T)
{
    if(T)
    {
        if(T->Ltag == link)
            inOrderTraverse(T->lchild);
        visit(T->data);
        if(T->Rtag == link)
            inOrderTraverse(T->rchild);
    }
}

//a recursive function to traverse the tree in a postorder.
//sequence is 1.left child    2.right child      3.root
void postOrderTraverse(BiThrTNode *T)
{
    if(T)
    {
        if(T->Ltag == link)
            postOrderTraverse(T->lchild);
        if(T->Rtag == link)
            postOrderTraverse(T->rchild);
        visit(T->data);
    }
}

//a non-recursive function to traverse the tree in a level order.
//like bfs,we need to use a queue.
void levelOrderTraverse(BiThrTNode *T)
{
    queue<BiThrTNode*> nodeQueue;
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
            BiThrTNode* tempNode = nodeQueue.front();
            visit(tempNode->data);
            nodeQueue.pop();
            if(tempNode->lchild != nullptr)
                nodeQueue.push( tempNode -> lchild );
            if(tempNode->rchild != nullptr)
                nodeQueue.push( tempNode -> rchild );
        }//while( !nodeQueue.empty() )
    }//if(T != nullptr )
}

//delete the the tree in a post order.
void deleteBiThrTNode(BiThrTNode *T)
{
    if(T)
    {
        deleteBiThrTNode(T->lchild);
        deleteBiThrTNode(T->rchild);
        delete T;
        T = nullptr;
    }
}

// the main recursive function to build the threading
//binary tree.
void inThreading(BiThrTNode *origPtr)
{   
    if(origPtr)
    {
        //firstly, build the threading for the left subtree.
        inThreading(origPtr -> lchild);
        // we can put the prior thread into its leftchild.
        if( origPtr -> lchild == nullptr)
        {
            origPtr -> Ltag = thread;
            origPtr -> lchild = pre;
        }
        // be careful, the initialized value for the Tag may be thread, 
        //so we must change it to link.
        else
        {
            origPtr->Ltag = link;
        }
        //we can put the next thread into its rightchild.
        if( pre->rchild == nullptr)
        {
            pre->Rtag = thread;
            pre->rchild = origPtr;
        }
        pre = origPtr;
        //thirdly, build the threading for the right subtree.
        inThreading(origPtr->rchild);
    }//if(origPtr)
}

//input: a binary tree without being threaded,(seems like a normal one)
//output: a binary tree that has kept its prior and next nodes in inorder traverse 
BiThrTNode* inOrderThreading(BiThrTNode *rootNode,BiThrTNode *headNode)
{
    //setting a head node. its left child points to the root,
    //right child points to the last node in inorder traverse. 
    //ALSO, the first node and the last node in inorder traverse will point to the head.
    headNode->Ltag = link;
    headNode->Rtag = thread;
    headNode->rchild = headNode;
    if(rootNode == nullptr)
    {
        headNode->lchild = headNode;
    }
    else
    {
        //using pre as the global previous node for 
        headNode->lchild = rootNode;
        pre = headNode;
        inThreading(rootNode);
        // a little revise for the last node.
        pre->rchild = headNode;
        pre->Rtag = thread;
        headNode->rchild = pre;
    }
    return headNode;
}

#endif