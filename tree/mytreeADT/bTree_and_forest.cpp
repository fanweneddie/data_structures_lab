#include "myBiTree.h"
#include <deque>

//ADT for forest.
//storing the root of the trees to simplify.
class Forest
{
    private:
        int trNum;
        deque<BiTNode*> treeRoots;
    public:
        Forest(int n)
        {
            trNum = n;
            string input1 = "AB##C##";
            MyBiTree t1(input1);
            BiTNode *tempRoot = t1.get_root();
            treeRoots.push_back(tempRoot);

            string input2 = "EF###";
            MyBiTree t2(input1);
            tempRoot = t2.get_root();
            treeRoots.push_back(tempRoot);

            string input3 = "GH#I###";
            MyBiTree t3(input1);
            tempRoot = t3.get_root();
            treeRoots.push_back(tempRoot);
            /*
            for (int i = 0; i < n;++i)
            {
                string input;
                cout << "please input a string to represent a tree.\n";
                cin >> input;
                MyBiTree t1(input);
                cout << "debug01\n";
                //just storing the root of each generated tree
                BiTNode *tempRoot = t1.get_root();
                cout << "debug02\n";
                treeRoots.push_back(tempRoot);
                cout << "debug03.\n";
            }
            */
        }

        int get_trNum() const { return trNum; }
        deque<BiTNode*> get_treeRoots() const { return treeRoots; }
};

//transforming a forest to a binary tree.
BiTNode* fst_to_bTr( deque<BiTNode*> treeRoots)
{
   
    if( treeRoots.empty() )
        return nullptr;
    // let
    cout << "debug10 not empty.\n";
    BiTNode *tempNode = treeRoots[0];
    cout << "debug11: tempNode is " << tempNode << endl;
    deque<BiTNode *> tempRootVector;
    if(tempNode->lchild != nullptr )
    {
        tempRootVector.push_back(tempNode->lchild);
        cout << "debug : leftchild is not null.\n";
    }
    if(tempNode->rchild != nullptr )
    {
        tempRootVector.push_back(tempNode->rchild);
        cout << "debug : rightchild is not null.\n";
    }
    cout << "debug12: the deque for the leftchild is \n";
    for (int i = 0; i <= 1;++i)
        cout << "  " << tempRootVector[i] << "  , " << tempRootVector[i]->data << endl;
    tempNode->lchild = fst_to_bTr(tempRootVector);
    treeRoots.pop_front();
    tempNode->rchild = fst_to_bTr(treeRoots);
    cout << "Debug11.\n";
    return tempNode;
}


void test()
{
    Forest f(3);
    cout << "debug04.\n";
    BiTNode *root = fst_to_bTr(f.get_treeRoots());
    cout << "debug05.\n";
    preOrderTraverse(root);
}

int main()
{
    test();
    return 0;
}