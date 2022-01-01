#include "../graphADT/adjListGraph.h"
#include <iostream>
#include <stack>
using namespace std;

const int MAX_VEX_NUM = 100;
int indegree[MAX_VEX_NUM];
double earliest[MAX_VEX_NUM];
double latest[MAX_VEX_NUM];
//getting the indegree of the vertexs in the graph.
void findIndegree(const AdjListGraph<char> G)
{
    ArcNode *arcPtr = nullptr;
    vector<VexNode<char>> GAdjList = G.get_adjList();
    int vexNum = G.get_vexNum();
    //initialization of the indegree
    for (int i = 0; i < vexNum;++i)
    {
        indegree[i] = 0;
    }
    //finding the indegree of each vex by traversing the adjList.
    for (int i = 0; i < G.get_vexNum(); ++i)
    {
        arcPtr = GAdjList[i].firstArc;
        while (arcPtr != nullptr)
        {
            int k = arcPtr->adjvex;
            ++indegree[k];
            arcPtr = arcPtr->next;
        } //while
    }//for
}
//the gragh is a directed net, each edge represents an event
// each vertex represents the start or end of an event.
//topostack returns a topological sequence.
// figure out the earliest happening time of each events
// if there is a directed ring in the graph, returns false
// else, we can find a topological sequence, return true. 
bool topological_Order(const AdjListGraph<char> &G,stack<int> &topoStack)
{
    findIndegree(G);
    int count = 0;//counts the vex in the topological stack.
    // if finally count < vexNum, there must be a ring in the graph.
    int vexNum = G.get_vexNum();
    vector<VexNode<char>> GAdjList = G.get_adjList();
    for (int i = 0; i < vexNum;++i)
        earliest[i] = 0;
    stack<int> zeroInStack;
    //build a stack to store the vex with zero indegree.
    for (int i = 0; i < vexNum;++i)
    {
        if(indegree[i] == 0)
            zeroInStack.push(i);
    }
    while( !zeroInStack.empty() )
    {
        int vex = zeroInStack.top();
        zeroInStack.pop();
        topoStack.push(vex);
        ++count;
        // deleting the arc that starts from this vex 
        // so we need to revise the indegree.
        for( ArcNode* arc = GAdjList[vex].firstArc; arc; arc = arc->next)
        {
            int nextVex = arc->adjvex;
            indegree[nextVex]--;
            if( indegree[nextVex] == 0 )
                zeroInStack.push(nextVex);
            //earliest[nextvex] = max(  earliest[vex] + dut ) 
            if( earliest[vex] + arc->weight > earliest[nextVex] )
                earliest[nextVex] = earliest[vex] + arc->weight;
        }//for
    }//while
    if( count < vexNum)
        return false;
    else
        return true;
}
//finding out the critical path.
void critical_Path(const AdjListGraph<char> &G,stack<int> topoStack)
{
    int vexNum = G.get_vexNum();
    vector<VexNode<char>> GAdjList = G.get_adjList();
    if( !topological_Order(G,topoStack) )
        cout << "ERROR: THIS GRAPH CAN NOT HAVE A TOPOLOGICAL ORDER.\n";
    //initializing the latest[i] with the time of the latest event.
    for (int i = 0; i < vexNum;++i)
        latest[i] = earliest[vexNum-1];
    // make the reverse topological sort.
    while( !topoStack.empty() )
    {
        int vex = topoStack.top();
        topoStack.pop();
        // latest[vex] = min( latest[nextVex] - dut )
        for( ArcNode* arc = GAdjList[vex].firstArc; arc; arc = arc->next)
        {
            int nextVex = arc->adjvex;
            double dut = arc->weight;
            if( latest[nextVex] - dut < latest[vex] )
            {
                latest[vex] = latest[nextVex] - dut;            
            }
        }//for
    }//while
    // for v, if earliest[v] = latest[v], that means v's relevant event can not be delayed,
    // So v is on the critical path.
    for (int vex = 0; vex < vexNum;++vex)
    {
        for( ArcNode* arc = GAdjList[vex].firstArc; arc; arc = arc->next)
        {
            int nextVex = arc->adjvex;
            double dut = arc->weight;
            if( earliest[vex] == latest[nextVex] - dut)
                cout << vex << " -> " << nextVex << endl;
        }//for
    }//for
}
int main()
{
    AdjListGraph<char> Graph;
    cout << "now starting the topo sort!!!\n";
    stack<int> topoStack;
    critical_Path(Graph, topoStack);
    return 0;
}
/*
testing data:
please input the type of graph.
1.dirGraph  2.undirGraph  3.dirNet  4.undirNet
3
please input the number of vex.
6
please input the number of arc.
8
please input the info of vexs.
0 1 2 3 4 5
please input the directed path.(e.g. A B w means A->B has weight w.)
0 1 3
0 2 2
1 3 2
1 4 3
2 3 4
2 5 3
3 5 2
4 5 1
*/