#include "../mytreeADT/myBiTree.h"
#include <iostream>
using namespace std;
//searching the key in the binary sorting tree
// return the node whose data == key
// if the searching is failed, return a nullptr
BiTNode* searchBST_alone(BiTNode* Tptr,char key)
{
    if( !Tptr || Tptr -> data == key )
        return Tptr;
    else if( key < Tptr->data )
        return searchBST_alone( Tptr -> lchild, key );
    else // key > Tptr->data;
        return searchBST_alone( Tptr -> rchild, key );
}

// Tptr is the root of this subtree, Fptr is Tptr's father,key is to be searched.
// insertPtr is a reference ptr that saves the ptr to insert a new key node.
bool searchBST_for_insert(BiTNode* Tptr, BiTNode* Fptr,char key,BiTNode*& insertPtr)
{
    //search is failed
    if( !Tptr )
    {
        insertPtr = Fptr;
        return false;
    }
    else if ( key == Tptr->data )
    {
        insertPtr = Fptr;
        return true;
    }
    else if( key < Tptr->data )
        return searchBST_for_insert(Tptr->lchild, Tptr, key, insertPtr);
    else // ( key > Tptr->data)
        return searchBST_for_insert(Tptr->rchild, Tptr, key, insertPtr);
}

//if the elem is not in the BST, it will insert this elem
// into a new NODE and maintain it as a BST
bool insertBST(BiTNode*& Tptr, char elem)
{
    BiTNode *insertPtr = nullptr;
    if( !searchBST_for_insert(Tptr,nullptr,elem, insertPtr) )
    {
        //after the change, insertPtr will be the father of the new node.
        BiTNode *newNode = new BiTNode;
        newNode->data = elem;
        newNode->lchild = nullptr;
        newNode->rchild = nullptr;
        if( !insertPtr )
            Tptr = newNode;
        else if( elem < insertPtr -> data )
            insertPtr -> lchild = newNode;
        else //elem > insertPtr -> data
            insertPtr -> rchild = newNode;
        return true;
    }
    // the elem is in the BST, don't need to insert.
    else
        return false;
}

bool deleteNode(BiTNode*&ptr1)
{
    // this node does not have a right subtree,
    // we just need to connect its lchild
    if(!ptr1 -> rchild)
    {
        BiTNode *ptr2 = ptr1;
        ptr1 = ptr1 -> lchild;
        delete ptr2;
    }
    // this node does not have a left subtree
    // we just need to connect its rchild
    else if(!ptr1 -> lchild)
    {
        BiTNode *ptr2 = ptr1;
        ptr1 = ptr1 -> rchild;
        delete ptr2;
    }
    else // the lchild and rchild are not nullptr
    {
        BiTNode* ptr2 = ptr1;
        BiTNode* ptr3 = ptr1->lchild;
        while( ptr3-> rchild )
        {
            ptr2 = ptr3;
            ptr3 = ptr3->rchild;
        }// let ptr3 = the right most node in root's left subtree.
        ptr1->data = ptr3->data;
        if( ptr1 != ptr2) // the root's leftchild has right child.
            ptr2->rchild = ptr3->lchild;
        else // the root's leftchild doesn't have right child.
            ptr1->lchild = ptr3->lchild;
        delete ptr3;
    }//else
    return true;
}

//delete a node whose data == key(first we need to search that node)
//if can't find that node, return false;
bool deleteBST(BiTNode*& Tptr, char key)
{
    if(!Tptr)
    {
        return false;
    }
    if( Tptr->data == key )
    {
        return deleteNode(Tptr);
    }
    else if( key < Tptr->data )
    {
        return deleteBST(Tptr->lchild, key);
    }
    else //Tptr->data > key
    {    
        return deleteBST(Tptr->rchild,key);
    }
}

int main()
{
    MyBiTree Tree;
    BiTNode *Tptr = Tree.get_root();
    for (int i = 0; i < 8;++i)
    {
        insertBST(Tptr, (char)(i + '0') );
    }
    // cautious: since Tptr has been changed from a nullptr to another new Ptr
    // we need to assign the new tptr to the Tree's root. 
    Tree.change_root(Tptr);
    // usintg in order traverse to check whether it is a BST.
    cout << "now, print the input elem.\n";
    Tree.in_Order_Traverse();
    cout << endl;
    /*
    Tptr = searchBST_alone(Tree.get_root(), '8');
    if(Tptr)
        cout << "yes!!!\n";
    else
        cout << "no!!!\n";
    */
    Tptr = Tree.get_root();
    deleteBST(Tptr, '2');
    cout << "now, print the input elem again.\n";
    inOrderTraverse(Tptr);
    cout << endl;
    return 0;
}