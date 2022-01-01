#include "../graphADT/adjListGraph.h"
#include <iostream>
#include <stack>
using namespace std;
const int MAX_VEX_NUM = 100;
int indegree[MAX_VEX_NUM];
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

void topoSort(const AdjListGraph<char> G)
{
    findIndegree(G);
    cout << endl;
    stack<int> S;
    int vexNum = G.get_vexNum();
    vector<VexNode<char>> GAdjList = G.get_adjList();
    //dealing with the vex whose indegree is 0.
    for (int i = 0; i < vexNum;++i)
    {
        if( indegree[i] == 0)
            S.push(i);
    }//for 
    int count = 0;
    while( ! S.empty() )
    {
        int vex = S.top();
        S.pop();
        cout << vex << " " ;
        ++count;
        // deleting the arcs connecting to the vex.
        for( ArcNode* p = GAdjList[vex].firstArc;p;p = p->next)
        {
            int k = p->adjvex;
            // delete the arcs by showing it in indegree array.
            indegree[k]--;
            //deal with the vex whose indegree becomes 0;
            if( indegree[k] == 0 )
                S.push(k);
        }//for
    }//while
    // if there is still some vexes left, print the error.
    if( count < vexNum )
        cout << "there is a directed circle in the graph.\n";
}

int main()
{
    AdjListGraph<char> Graph;
    cout << "now starting the topo sort!!!\n";
    topoSort(Graph);
    return 0;
}
/*
please input the type of graph.
1.dirGraph  2.undirGraph  3.dirNet  4.undirNet
1
please input the number of vex.
6
please input the number of arc.
8
please input the info of vexs.
1 2 3 4 5 6  
please input the directed arcs.(e.g. A B means A->B)
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5
*/