#ifndef PTCDLIST
#define PTCDLIST
#include <vector>
#include <iostream>
using namespace std;
//child node
struct CDNode
{
    int index;
    CDNode *next;
};

// the general node
struct Node
{
    int currIndex;
    int parentIndex;
    CDNode *firstChild;
};

// the list showing parent and children
// So it is called PTCDList
class PTCDList
{
    protected:
        int nodeNum;
        vector<Node> nodes;
    public:
        //constructor
        PTCDList();
        void output();
        ~PTCDList();
};

//constructor, input the nodes and edges literally
PTCDList::PTCDList()
{
    cout << "please input the number of nodes in this tree.\n";
    cin >> nodeNum;
    Node newNode;
    //firstly, input the data of the nodes.
    cout << "please input those " << nodeNum << " nodes\n";
    for (int i = 0; i < nodeNum;++i)
    {
        newNode.currIndex = i;
        newNode.firstChild = nullptr;
        newNode.parentIndex = -1;
        nodes.push_back(newNode);
    }
    int tempChild; 
    // secondly, input the children of each node.
    for (int i = 0; i < nodeNum;++i)
    {
        cout << "please input node " << nodes[i].currIndex
            << " 's direct children. ( enter -1 to end )\n";
        CDNode *lastChildPtr = nullptr;
        nodes[i].firstChild = lastChildPtr;
        while( true )
        {
            cin >> tempChild;
            if(tempChild != -1 )
            {
                CDNode *childPtr = new CDNode;
                // using head-inserting way to insert a node into
                // the head of the list.
                childPtr->index = tempChild;
                childPtr->next = lastChildPtr;
                nodes[i].firstChild = childPtr;
                lastChildPtr = childPtr;
            }//if(tempChild != -1 )
            else
                break;
        }
    } //for (int i = 0; i < nodeNum;++i)

    //NOW TRYING TO FIND OUT EACH NODE'S PARENT NODE
    for (int i = 0; i < nodeNum;++i)
    {
        CDNode *childPtr = nodes[i].firstChild;
        while(childPtr)
        {
            int cd = childPtr->index;
            nodes[cd].parentIndex = i;
            childPtr = childPtr->next;
        }
    } //for (int i = 0; i < nodeNum;++i)
}

// output the nodes of the list representing a Bitree
void PTCDList::output()
{
    for (int i = 0; i < nodeNum;++i)
    {
        cout << i << "   ";
        CDNode *childPtr = nodes[i].firstChild;
        while( childPtr)
        {
            cout << childPtr -> index << " ";
            childPtr = childPtr -> next;
        }
        cout << endl;
    }
}

PTCDList::~PTCDList()
{
    for (int i = 0; i < nodeNum;++i)
    {
       CDNode *childPtr = nodes[i].firstChild;
       CDNode *tempPtr;
       while( childPtr )
       {
           tempPtr = childPtr->next;
           delete childPtr;
           childPtr = tempPtr;
       }
    } //for (int i = 0; i < nodeNum;++i)
}

#endif