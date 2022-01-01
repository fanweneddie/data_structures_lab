//include the ADT of the binary tree
#include "../mytreeADT/myBiTree.h"
#include <string>

/* input is a preorder expression and a inorder expression
    WE can create a unique binary tree according to them.
*/
BiTNode* in_pre_createBiTree(string preExpr,string inExpr)
{
    BiTNode *tempNode = new BiTNode;
    // the first element of pre expression is the root of the current subtree.
    tempNode->data = preExpr[0];
    int rootIndex = inExpr.find(preExpr[0], 0);
    //at the left of the rootindex in inorder expression, 
    //  -those nodes are at the left subtree.
    
    //there are more than one elements in the left part
    // use recursion to build the left subtree.
    if( rootIndex != 0 )
    {
        string tempInExpr = inExpr.substr(0, rootIndex);
        string tempPreExpr = preExpr.substr(1, rootIndex + 1);
        tempNode->lchild = in_pre_createBiTree(tempPreExpr, tempInExpr);
    }
    //there is no element in the left part, so the left subtree is nullptr.
    else
        tempNode->lchild = nullptr;
    
    //at the right of the rootindex in inorder expression, 
    //  -those nodes are at the right subtree.
    
    //there are more than one elements in the right part
    // use recursion to build the right subtree.
    if(rootIndex != inExpr.length() -1)
    {
        string tempInExpr = inExpr.substr(rootIndex + 1);
        string tempPreExpr = preExpr.substr(rootIndex + 1);
        tempNode->rchild = in_pre_createBiTree(tempPreExpr, tempInExpr);
    }
    //there is no element in the right part, so the right subtree is nullptr.
    else
        tempNode->rchild = nullptr;
    return tempNode;
}

int main()
{
    string preExpr,inExpr;
    preExpr = "abc";
    inExpr = "bac";
    cout << "hello\n";
    BiTNode *root = in_pre_createBiTree(preExpr, inExpr);
    cout << "now traversing the tree in a preorder way.\n";
    inOrderTraverse(root);
    cout << "\nnow traversing the tree in a inorder way.\n";
    inOrderTraverse(root);
    cout << "\nnow traversing the tree in a postorder way.\n";
    postOrderTraverse(root);
    cout << "done!\n";
}