#ifndef MYBBST
#define MYBBST
#include <iostream>
#include <queue>
using namespace std;
#define LH 1
#define RH -1
#define EH 0 
struct BBSTNode
{
    int data;
    int bf = EH ; // bf = leftSubtree_height - rightSubtree_height
    BBSTNode *lchild, *rchild;
};

void leftBalance(BBSTNode *&Tptr);
void rightBalance(BBSTNode *&Tptr);
//ptr is inbalanced because its leftsubtree_height - rightsubtree_height == 2
//the height of left subtree of the left subtree = leftsubtree_height. 
void R_rotate(BBSTNode *&ptr)
{
    BBSTNode *lc = ptr->lchild;
    ptr->lchild = lc->rchild;
    lc->rchild = ptr;
    ptr = lc;
}

//ptr is inbalanced because its rightsubtree_height - leftsubtree_height == 2
//the height of right subtree of the right subtree = rightsubtree_height. 
void L_rotate(BBSTNode *&ptr)
{
    BBSTNode* rc = ptr->rchild;
    ptr->rchild = rc->lchild;
    rc->lchild = ptr;
    ptr = rc;
}

/*  Tptr points to the root node of the balanced binary sorting tree.
    if the height of the binary sorting tree increase, istaller = true;
    else, istaller = false.   */
bool insertAVL(BBSTNode *& Tptr, int elem, bool& isTaller)
{
    //create and insert a new node.
    if(!Tptr)
    {
        Tptr = new BBSTNode;
        Tptr->data = elem;
        Tptr->lchild = nullptr;
        Tptr->rchild = nullptr;
        Tptr->bf = EH;
        isTaller = true;
    }
    else //Tptr != nullptr
    {
        //the elem exists in the tree,so we don't need to insert.
        if( elem == Tptr->data )
        {
            isTaller = false;
            return false;
        }
        else if ( elem < Tptr->data )
        {
            if( !insertAVL(Tptr->lchild,elem,isTaller) )
            {
                return false;
            }
            //the insert to the left subtree is successful
            // if after the insertion to the left subtree, the left tree is taller
            // we need to check the original bf of the Tptr.
            if(isTaller)
            {
                switch(Tptr->bf)
                {
                    case LH:
                        leftBalance(Tptr);
                        isTaller = false;
                        break;
                    case EH:
                        Tptr->bf = LH;
                        isTaller = true;
                        break;
                    case RH:
                        Tptr->bf = EH;
                        isTaller = false;
                        break;
                }//switch
            }//if(isTaller)
        } //else if ( elem < Tptr->data )
        else // elem > Tptr->data
        {
            if( !insertAVL(Tptr->rchild,elem,isTaller) )
                return false;
            if( isTaller )
            {
                switch(Tptr->bf)
                {
                    case LH:
                        Tptr->bf = EH;
                        isTaller = false;
                        break;
                    case EH:
                        Tptr->bf = RH;
                        isTaller = true;
                        break;
                    case RH:
                        rightBalance(Tptr);
                        isTaller = false;
                        break;
                }//switch
            } //if( isTaller )
        } //else elem > Tptr->data
    } //else Tptr != nullptr
    return true;
}

//Tptr's left subtree is inbalanced,so we need to rebalance it.
//Tptr is still the root node after the adjust.
//revise the bf of every node after the change if necessary
void leftBalance(BBSTNode *&Tptr)
{
    BBSTNode *lc = Tptr->lchild;
    switch(lc->bf)
    {
        //the left part of Tptr's left subtree protrudes,so just R_rotate for once.
        case LH:
        {
            Tptr->bf = EH;
            lc->bf = EH;
            R_rotate(Tptr);
            break;
        }
        //the right part of Tptr's right subtree protrudes, so it depends on that right subtree
        case RH:
        {
            BBSTNode *rd = lc->rchild;
            switch(rd->bf)
            {
                case LH:            //            a                    a                e                
                    Tptr->bf = RH;  //     b         c   =>       e       c   =>   b        a
                    lc->bf = EH;    //  d      e               b                 d   f         c
                    rd->bf = EH;    //       f              d   f
                    break;
                case EH:
                    Tptr->bf = EH;  //             a                  a                   e
                    lc->bf = EH;    //     b          c  =>      e        c    =>     b       a
                    rd->bf = EH;    //  d      e             b     g                d   f   g   c
                    break;          //       f   g         d   f
                
                case RH:            //             a                   a                 e
                    Tptr->bf = EH;  //     b         c    =>      e        c  =>     b         a
                    lc->bf = LH;    // d     e                 b     f             d         f     c
                    rd->bf = EH;    //         f             d
                    break;
            } //switch(rd->bf)
            L_rotate(Tptr->lchild);
            R_rotate(Tptr);
        } //case RH:
    } //switch(lc->bf)  
}

//Tptr's right subtree is inbalanced,so we need to rebalance it.
//Tptr is still the root node after the adjust.
//revise the bf of every node after the change if necessary
// almost symmetrical to the function of leftbalance.
void rightBalance(BBSTNode *&Tptr)
{
    BBSTNode *rc = Tptr->rchild;
    switch(rc->bf)
    {
        //the right part of Tptr's right subtree protrudes,so just L_rotate for once.
        case RH:
        {
            Tptr->bf = EH;
            rc->bf = EH;
            L_rotate(Tptr);
            break;
        }
        //the left part of Tptr's right subtree protrudes, so it depends on that left subtree
        case LH:
        {
            BBSTNode *ld = rc->lchild;
            switch(ld->bf)
            {
                case LH:                //      a                        a                        d
                    Tptr->bf = EH;      //   b       c     R        b         d        L      a       c
                    ld->bf = RH;        //         d   e   =>               f   c     =>    b   f        e
                    rc->bf = EH;        //        f                               e
                    break;
                case EH:                //      a            R            a            L            d
                    Tptr->bf = EH;      //  b           c    =>     b            d     =>      a          c
                    ld->bf = EH;        //          d      e                  f      c       b   f      g   e
                    rc->bf = EH;        //        f   g                            g   e
                    break;
                case RH:                //      a             R          a             L            d
                    Tptr->bf = LH;      // b           c     =>     b           d      =>     a          c
                    ld->bf = EH;        //         d       e                         c      b           f   e
                    rc->bf = EH;        //           f                              f  e
                    break;
            } //switch(rd->bf)
            R_rotate(Tptr->lchild);
            L_rotate(Tptr);
        } //case RH:
    } //switch(ld->bf)  
}

//a recursive function to traverse the tree in an inorder.
//sequence is 1.left child    2.root    3.right child
void inOrderTraverse(BBSTNode *T)
{
    if(T)
    {
        inOrderTraverse(T->lchild);
        cout << T->data << " ";
        inOrderTraverse(T->rchild);
    }
}

//a non-recursive function to traverse the tree in a level order.
//like bfs,we need to use a queue.
void levelOrderTraverse(BBSTNode *T)
{
    queue<BBSTNode*> nodeQueue;
    if(T != nullptr )
    {
        //firstly,push the root into the queue
        nodeQueue.push(T);
        while( !nodeQueue.empty() )
        {
            /*for each node, 1. visit it
            2.push its left child into the queue
            3.push its right child into the queue
            then we can visit its sibling child
            (if that node is the last one of that level, we can
             visit the first node in the next level)
            */
            BBSTNode* tempNode = nodeQueue.front();
            cout << tempNode->data << " ";
            nodeQueue.pop();
            if(tempNode->lchild != nullptr)
                nodeQueue.push( tempNode -> lchild );
            if(tempNode->rchild != nullptr)
                nodeQueue.push( tempNode -> rchild );
        }//while( !nodeQueue.empty() )
    }//if(T != nullptr )
}

#endif
