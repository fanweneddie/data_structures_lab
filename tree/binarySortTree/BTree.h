#ifndef BTREE
#define BTREE
#include <queue>
#include <iostream>
using namespace std;
const int M = 4;
const int MAX_KEY_NUM = M-1;
const int MIN_KEY_NUM = (M - 1) / 2;
const int NEG_INF = -999;
struct BTNode
{
    int keyNum;
    int keyArray[M+1]; //key[0] = NEG_INF
    BTNode *ptrArray[M];
    BTNode *parent;
};

enum Status{
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
};

struct Result
{
    BTNode *ptr; // the node that I have found.
    int index;  // the index of key in the ptr.
    bool found; // true means success; false means failure.
};

//THE INITIALIZATION OF A B-TREE
Status initBTree( BTNode*& T)
{
    T = new BTNode;
    T = nullptr;
    return OK;
}

//searching the location of the key in node T.
// return i such that key[i] <= key < key[i+1] 
int searchBTNode(BTNode* T, int key)
{
    if(!T)
        cout << "debug50:no\n";
    cout << "Debug51: the keyNum is " << T->keyNum << endl;
    cout << "debug52: the key is " << key << endl;
    if(T->keyNum == 0)
        return -1;
    for (int i = 0; i < T->keyNum; ++i)
    {
        if( T->keyArray[i] <= key  && key < T->keyArray[i+1] )
            return i;
    }
    // the key is larger than any of the keys in the ptr
    // and thus should be inserted into the last place.
    return T->keyNum; 
}

/*  T is the root node of that B tree, key is the key word to be searched
return the Result type( the found node, index in that node, isfound? ) */
Result searchBTree( BTNode* T, int key)
{
    Result lastResult;
    BTNode *ptr = T;
    BTNode *fptr = nullptr;
    bool found = false;
    int index = 0;
    //using iteration to search this 
    while( ptr && !found )
    {
        cout << "debug20: enter the while loop in searchNode.\n";
        index = searchBTNode(ptr, key);
        cout << "debug21: the index is " << index << endl;
        if(ptr->ptrArray[index] == nullptr)
            cout << "debug22: the ptr[index] is a nullptr.\n";
        else
        {
            cout << "debug23: the ptr[index] is not a nullptr.\n";
            cout << "debug24: the ptr[index]'s keyNum is " << ptr->ptrArray[index]->keyNum << endl;
        }
        if( index > 0 && ptr->keyArray[index] == key )
            found = true;
        else
        {
            fptr = ptr;
            ptr = ptr->ptrArray[index];
            if( !ptr || ptr->keyNum == 0 )
                break;
        }
    }//while
    if(found) //return (ptr,index,true)
    {
        lastResult.ptr = ptr;
        lastResult.index = index;
        lastResult.found = true;
        return lastResult;
    }
    else // return(fptr,index,false)
    {
        lastResult.ptr = fptr;
        lastResult.index = index;
        lastResult.found = false;
        return lastResult;
    }
}
/* from the searchNode we have got the ptr and the index.
then we insert the key into ptr->keyArray[index+1] 
and we insert the nextPtr into ptr->ptrArray[index+1] 
plus: nextPtr has no key as a leaf node
(but not a null because we can utilize its parent*/
void insertBTNode(BTNode *&ptr, int index,int key,BTNode *nextPtr)
{
    cout << "debug40: enter insertBTnode.\n";
    for (int j = ptr->keyNum; j > index ;--j)
    {
        ptr->keyArray[j+1] = ptr->keyArray[j];
        ptr->ptrArray[j + 1] = ptr->ptrArray[j];
    }
    cout << "debug42: alive?\n";
    ptr->keyArray[index + 1] = key;
    ptr->ptrArray[index + 1] = nextPtr;
    cout << "debug42: alive+?\n";
    ++ptr->keyNum;
    cout << "debug43: alive++?\n";
    nextPtr->parent = ptr;
    nextPtr->keyNum = 0;
    nextPtr->keyArray[0] = NEG_INF;
    cout << "debug44: alive+++?\n";
    cout << "debug41: after the insert, the ptr->keyArray["<< index << " +1] = " << ptr->keyArray[index + 1] << endl;
}
/* split the node firstPtr into two nodes,
    The first half remains in firstPtr,
    The second half is kept in nextPtr; */
void splitBTNode(BTNode* &firstPtr,BTNode *& nextPtr)
{
    cout << "debug60: enter splitBTNode.\n";
    int half = (M + 1) / 2;
    for (int i = half + 1; i <= M;++i)
    {
        nextPtr->keyArray[i - half] = firstPtr->keyArray[i];
        nextPtr->ptrArray[i - half] = firstPtr->ptrArray[i];
    }
    cout << "debug61: hello there?\n";
    nextPtr->keyNum = firstPtr->keyNum - half;
    nextPtr->parent = firstPtr->parent;
    cout << "debug62: hello there+? nextPtr->KeyNum is " << nextPtr->keyNum << endl;
    for(int j =1 ; j <= nextPtr->keyNum;++j)
    {
        cout << "debug62.3: nextPtr->keyArray[" << j << "] = " << nextPtr->keyArray[j] << endl;
    }
    for (int i = 0; i <= nextPtr->keyNum;++i)
    {
        cout << "debug62.5: now enter the FOR LOOP and i = " << i << endl;
        if( nextPtr->ptrArray[i] )
        {
            cout << "debug64: nextPtr->ptrArray[" << i << "] is not a null.\n";
            nextPtr->ptrArray[i]->parent = nextPtr;
            cout << "debug64.5: can you reach there?\n";
        }
        else
            cout << "debug65: nextPtr->ptrArray[" << i << "] is a null.\n";
    }
    
    // the key[half] will be inserted into the father of the firstPtr.
    cout << "debug63: hello there++?\n";
    firstPtr->keyNum = half - 1;
}
/* generate new root node newRoot with rootData in it.
    ptr1 and ptr2 are two subtree ptr of newRoot */
void makeNewRoot(BTNode*&newRoot, int rootData, BTNode*ptr1, BTNode*ptr2)
{
    newRoot = new BTNode;
    newRoot->keyNum = 1;
    newRoot->ptrArray[0] = ptr1;
    newRoot->ptrArray[1] = ptr2;
    newRoot->keyArray[1] = rootData;
    if(ptr1)
        ptr1->parent = newRoot;
    if(ptr2)
        ptr2->parent = newRoot;
    newRoot->parent = nullptr;
}

/* T is the root ptr of the tree.
    key will be firstly inserted into ptr->ptrArray[index+1]
*/
void InsertBTree(BTNode* &T,int index,int key,BTNode *ptr)
{
    cout << "debug30: enter the insertBTree.\n";
    if( !ptr )
    {
        cout << "debug31: the ptr is null.\n";
        makeNewRoot(T, key, nullptr, nullptr);
    }
    else
    {
        cout << "debug32: the ptr is not a null\n";
        BTNode *nextPtr = new BTNode;
        int finish_tag = 0, newRoot_tag = 0, elem = key;
        // using iteration to insert a new node into the Btree.
        while (!finish_tag && !newRoot_tag)
        {
            cout << "debug34: enter the while loop.\n";
            insertBTNode(ptr, index, elem, nextPtr);
            if (ptr->keyNum <= MAX_KEY_NUM)
            {
                cout << "debug35: the insert is ok, don't need to split.\n";
                finish_tag = 1;
            }
            else
            {
                cout << "debug36: we need to split the node into two nodes.\n";
                int half = (M + 1) / 2;
                BTNode *anotherPtr = new BTNode;
                splitBTNode(ptr, anotherPtr);
                elem = ptr->keyArray[half];
                if( ptr->parent )
                {
                    ptr = ptr->parent;
                    index = searchBTNode(ptr, elem);
                }
                else
                    newRoot_tag = 1;
             }
         }//while(!finish_tag && !newRoot_tag)
         if( newRoot_tag == 1)
             makeNewRoot(T, elem, ptr, nextPtr);
         cout << "debug33: hello there.\n";
    } //else
}

struct couple
{
    BTNode *ptr;
    int height;
};

void traverseBTree(BTNode* T)
{
    cout << "debug10: enter the tree traverse.\n";
    queue<couple> Q;
    if(!T)
        return;
    couple cp;
    cp.ptr = T;
    cp.height = 1;
    Q.push(cp);
    int currentHeight = 1;
    while( !Q.empty())
    {
        cp = Q.front();
        cout << "debug11: now the ptr height is " << cp.height << endl;
        //cout << "Debug12: now the ptr keyNum is " << cp.ptr->keyNum << endl;
        if( !cp.ptr )
            break;
        if( currentHeight == cp.height )
        {
            Q.pop();
            for (int i = 0; i <= cp.ptr->keyNum;++i)
            {
                couple tempCP;
                tempCP.ptr = cp.ptr->ptrArray[i];
                tempCP.height = cp.height + 1;
                Q.push(tempCP);
            }//for
            cout << "[ ";
            for (int i = 1; i <= cp.ptr->keyNum;++i)
            {
                cout << cp.ptr->keyArray[i] << " ";
            }
            cout << "]  ";
        }//if
        else
        {
            cout << endl;
            currentHeight += 1;
        }//else
    }//while
}


#endif