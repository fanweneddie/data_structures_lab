#ifndef ADJLISTGRAPH
#define ADJLISTGRAPH
#include <vector>
#include <iostream>
using namespace std;

//four types of graph
enum graphType 
{
    dirGraph,
    undirGraph,
    dirNet,
    undirNet
};
// the node for arcs in the graph
struct ArcNode
{
    int adjvex; // the index that this arc points to.
    ArcNode *next;
    double weight = 0;
};
// the node for vertexes in the graph.
template<class T>
struct VexNode
{
    int index;
    T info;
    ArcNode *firstArc;
};

//four constructive functions to create different types of graphs.
//use reference parameter to save multiple values.
template <class T>
void create_dirGraph( vector<VexNode<T>> &adjList,int vexNum,int arcNum);
template <class T>
void create_undirGraph( vector<VexNode<T>> &adjList,int vexNum,int arcNum);
template <class T>
void create_dirNet( vector<VexNode<T>> &adjList,int vexNum,int arcNum);
template <class T>
void create_undirNet( vector<VexNode<T>> &adjList, int vexNum,int arcNum);

// for the ostream friend function to fit in with the template.
// we need to declare it in advance.
template <class T>
class AdjListGraph;

template <class T>
ostream &operator<< (ostream &out, const AdjListGraph<T> & alg);

template<class T>
class AdjListGraph
{
    private:
        int vexNum;
        int arcNum;
        graphType kind;
        vector< VexNode<T> > adjList;
    public:
        AdjListGraph();
        int get_vexNum() const { return vexNum; }
        int get_arcNum() const { return arcNum; }
        graphType get_type() const { return kind; }
        vector<VexNode<T>> get_adjList() const { return adjList; }
        friend ostream &operator<< <> (ostream &out, const AdjListGraph<T> & alg);
};

template<class T>
AdjListGraph<T>::AdjListGraph()
{
    cout << "please input the type of graph.\n";
    cout << "1.dirGraph  2.undirGraph  3.dirNet  4.undirNet\n";
    int typeChoice = 0;
    cin >> typeChoice;
    //input some basic info such as the vexNum,arcNum and the vexs.
    //those features are shared by all kinds of graph.
    cout << "please input the number of vex.\n";
    cin >> vexNum;
    cout << "please input the number of arc.\n";
    cin >> arcNum;
    cout << "please input the info of vexs.\n";
    for (int i = 0; i < vexNum;++i)
    {
        VexNode<T> tempVexNode;
        tempVexNode.index = i;
        cin >> tempVexNode.info;
        tempVexNode.firstArc = nullptr;
        adjList.push_back(tempVexNode);
    }
    //for different type of graph, the way to input and deal with
    // -- the arcs is different. So we use four functions.
    switch( typeChoice)
    {
        case 1:
            kind = dirGraph;
            create_dirGraph(adjList, vexNum, arcNum);
            break;
        case 2:
            kind = undirGraph;
            create_undirGraph(adjList, vexNum, arcNum);
            break;
        case 3:
            kind = dirNet;
            create_dirNet(adjList, vexNum, arcNum);
            break;
        case 4:
            kind = undirNet;
            create_undirNet(adjList, vexNum, arcNum);
            break;
        default:
            cout << "invalid graph type!!!\n";
            throw " invalid graph type!\n";
            break;
    }
}

template <class T>
void create_dirGraph( vector<VexNode<T>> &adjList,int vexNum,int arcNum)
{
    cout << "please input the directed arcs.(e.g. A B means A->B)\n";
    for(int i = 0;i < arcNum;++i)
    {
        T vexInfo_1,vexInfo_2;
        cin >> vexInfo_1 >> vexInfo_2;
        int vexIndex_1 = -1, vexIndex_2 = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_1)
            {
                vexIndex_1 = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_2)
            {
                vexIndex_2 = j;
                break;
            }
        }
        // insert the arcNode next to the vexNode.
        // since the graph is directed, we only need to insert once.
        ArcNode *arcNodePtr = new ArcNode;
        arcNodePtr -> adjvex = vexIndex_2;
        arcNodePtr -> next = adjList[vexIndex_1].firstArc;
        adjList[vexIndex_1].firstArc = arcNodePtr;
    }//for(int i = 0;i < arcNum;++i)
}

template <class T>
void create_undirGraph( vector<VexNode<T>> &adjList,int vexNum,int arcNum)
{
    cout << "please input the undirected arcs.(e.g. A B means A-B)\n";
    for(int i = 0;i < arcNum;++i)
    {
        T vexInfo_1,vexInfo_2;
        cin >> vexInfo_1 >> vexInfo_2;
        int vexIndex_1 = -1, vexIndex_2 = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_1)
            {
                vexIndex_1 = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_2)
            {
                vexIndex_2 = j;
                break;
            }
        }
        // insert the arcNode next to the vexNode.
        //the graph is undirected, we need to insert twice to make it symmetrical.
        //first, A - B
        ArcNode *arcNodePtr_1 = new ArcNode;
        arcNodePtr_1 -> adjvex = vexIndex_2;
        arcNodePtr_1 -> next = adjList[vexIndex_1].firstArc;
        adjList[vexIndex_1].firstArc = arcNodePtr_1;
        //then, B - A
        ArcNode *arcNodePtr_2 = new ArcNode;
        arcNodePtr_2 -> adjvex = vexIndex_1;
        arcNodePtr_2 -> next = adjList[vexIndex_2].firstArc;
        adjList[vexIndex_2].firstArc = arcNodePtr_2;
    }//for(int i = 0;i < arcNum;++i)
}

template <class T>
void create_dirNet( vector<VexNode<T>> &adjList,int vexNum,int arcNum)
{
    cout << "please input the directed path.(e.g. A B w means A->B has weight w.)\n";
    for(int i = 0;i < arcNum;++i)
    {
        T vexInfo_1,vexInfo_2;
        double w;
        cin >> vexInfo_1 >> vexInfo_2 >> w;
        int vexIndex_1 = -1, vexIndex_2 = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_1)
            {
                vexIndex_1 = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_2)
            {
                vexIndex_2 = j;
                break;
            }
        }
        // insert the arcNode next to the vexNode.
        //the net is directed, we only need to insert once.
        ArcNode *arcNodePtr = new ArcNode;
        arcNodePtr -> adjvex = vexIndex_2;
        arcNodePtr->weight = w;
        arcNodePtr -> next = adjList[vexIndex_1].firstArc;
        adjList[vexIndex_1].firstArc = arcNodePtr;
    }//for(int i = 0;i < arcNum;++i)
}

template <class T>
void create_undirNet( vector<VexNode<T>> &adjList,int vexNum,int arcNum)
{
    cout << "please input the undirected path.(e.g. A B w means A-B has weight w.)\n";
    for(int i = 0;i < arcNum;++i)
    {
        T vexInfo_1,vexInfo_2;
        double w;
        cin >> vexInfo_1 >> vexInfo_2 >> w;
        int vexIndex_1 = -1, vexIndex_2 = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_1)
            {
                vexIndex_1 = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(adjList[j].info == vexInfo_2)
            {
                vexIndex_2 = j;
                break;
            }
        }
        // insert the arcNode next to the vexNode.
        //the net is undirected, we need to insert twice to make it symmetrical.
        //first, A - B
        ArcNode *arcNodePtr_1 = new ArcNode;
        arcNodePtr_1 -> adjvex = vexIndex_2;
        arcNodePtr_1->weight = w;
        arcNodePtr_1 -> next = adjList[vexIndex_1].firstArc;
        adjList[vexIndex_1].firstArc = arcNodePtr_1;
        //then, B - A
        ArcNode *arcNodePtr_2 = new ArcNode;
        arcNodePtr_2 -> adjvex = vexIndex_1;
        arcNodePtr_2->weight = w;
        arcNodePtr_2 -> next = adjList[vexIndex_2].firstArc;
        adjList[vexIndex_2].firstArc = arcNodePtr_2;
    }//for(int i = 0;i < arcNum;++i)
}

//output the info of the graph stored in a adjacent list.
template <class T>
ostream &operator<<(ostream &out, const AdjListGraph<T> & alg)
{
    out << "The info of the graph is as below:\n";
    //first, print the type of the graph.
    switch(alg.kind)
    {
        case dirGraph:
            out << "this is a directed graph.\n";
            break;
        case undirGraph:
            out << "this is a undirected graph.\n";
            break;
        case dirNet:
            out << "this is a directed net.\n";
            break;
        case undirNet:
            out << "this is a undirected net.\n";
            break;
        default:
            break;
    }
    out << "the vertex number is " << alg.vexNum << endl;
    out << "the arc number is " << alg.arcNum << endl;
    out << "the connected vertexes are :\n";
    for (int i = 0;i < alg.vexNum;++i)
    {
        out << alg.adjList[i].info << "  with  ";
        ArcNode *arcPtr = alg.adjList[i].firstArc;
        while(arcPtr != nullptr)
        {
            out << alg.adjList[arcPtr->adjvex].info << " ";
            arcPtr = arcPtr -> next;
        }
        out << endl;
    }
    return out;
}

#endif