#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

//the node in a huffmann tree.
struct HTnode
{
    //when building a tree, weight represents weight
    //when getting the code, weight represents a flag.
    int weight;
    int parent, lchild, rchild;
};

//getting 2 nodes with least weights
//those 2 nodes are not merged, so their parents should be 0.(as a flag)
void select(HTnode* HT, int num, int & index1, int & index2 )
{
    // a select sort.
    HTnode currentMin = {9999, 0, 0, 0};
    int currentMinIndex = 0;
    index1 = -1;
    for (int i = 0; i < 2;++i)
    {
        currentMin = {9999, 0, 0, 0};
        for (int j = 0; j < num; ++j)
        {
            //those 2 nodes are not merged, so their parents should be 0.   
            if ( HT[j].parent == 0 && (HT + j)->weight < currentMin.weight && j != index1 )
            {
                currentMin = *(HT + j);
                currentMinIndex = j;
            }
        }//for j
        if( i == 0)
        {
            index1 = currentMinIndex;
        }
        else if( i == 1)
        {   
            index2 = currentMinIndex;
        }
    }
}

//input: *w is an array of weight, num is the number of nodes
//output: (reference) codes is an array of HTnode and its code.
void HuffmanCoding( int *w, int num ,vector<string> &codes)
{   
    if(num < 1)
        return;
    //creating an array to store huffman tree
    // there will be num-1 generated nodes.
    int totalNum = 2*num - 1;
    HTnode *HT = new HTnode [totalNum];
    HTnode *ptr = HT;
    //INITIALIZATION OF THOSE nodes.
    for (int i = 0; i < num; ++i,++ptr)
    {
        *ptr = {*(w + i), 0, 0, 0};
    }
    for (int i = num; i < totalNum;++i)
    {
        *ptr = {0, 0, 0, 0};
    }
    ptr = HT;
    cout << endl;
    // merge the two nodes with least weights.
    //revise their parent and their parent's lchild/rchild
    for (int i = num; i < totalNum; ++i)
    {
        int s1 = 0, s2 = 0;
        select(HT, i, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    // the last node is the root node.
    HT[totalNum - 1].parent = -1;
    //coding for huffman tree.
    for (int i = 0; i < num; ++i)
    {
        string code;
        //from a leaf node, backtrace to find its root.
        // if it is its parent's lchild, add 0
        // else( rchild ), add 1.
        // at last, reverse the code and it is the huffman code of that node.
        for (int currentIndex = i, parentIndex = HT[i].parent; parentIndex > 0;
             currentIndex = parentIndex, parentIndex = HT[parentIndex].parent)
        {
            if (HT[parentIndex].lchild == currentIndex)
                code += "0";       
            else if (HT[parentIndex].rchild == currentIndex)
                code += "1";
        }//for currentIndex
        reverse(code.begin(), code.end());
        codes.push_back(code);
    }//for i
    delete[] HT;
}

int main()
{
    int w[4] = {7,5,4,2};
    vector<string> codes;
    HuffmanCoding(w, 4, codes);
    int len = codes.size();
    cout << "now,print the huffman code.\n";
    for (int i = 0; i < len; ++i)
    {
        cout << codes[i] << endl;
    }
}
