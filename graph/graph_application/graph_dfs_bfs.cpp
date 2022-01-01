//#include "C:\Users\Eddie\Desktop\sophomore\data_structure\graph\graphADT\adjMatrixGraph.h"
#include "../graphADT/adjListGraph.h"
#include <queue>
#include <iostream>
using namespace std;

/* ################################################################## */
// dfs function for traversing a graph
//RECURSIVE FUNCTION
void dfs_adjList(const AdjListGraph<char> &G, int vexIndex, bool *ptr)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    *( ptr + vexIndex) = true;
    cout << G_adjList[vexIndex].info << " ";
    for (ArcNode *arc = G_adjList[vexIndex].firstArc; arc != nullptr;
         arc = arc->next)
    {
        if (ptr[arc->adjvex] == false)
        {
            dfs_adjList(G, arc->adjvex, ptr);
        }
    }
}
//OVERALL FUNCTION FOR DFS
void dfs_traverse_adjList(const AdjListGraph<char> & G)
{
    int vexNum = G.get_vexNum();
    bool visited[vexNum];
    bool *ptr = visited;
    for(int i = 0;i < vexNum;++i)
        visited[i] = false;
    //be careful of the different connected components.
    for (int i = 0;i < vexNum;++i)
    {
        if(visited[i] == false)
        {
            dfs_adjList(G, i,ptr);
            //in order to distinguish different connected components.
            cout << endl;
        }
    }
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */

/*############################################## */
//bfs function for traversing a graph
void bfs_traverse_adjList(const AdjListGraph<char> &G)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int vexNum = G.get_vexNum();
    bool visited[vexNum];
    for(int i = 0;i < vexNum;++i)
        visited[i] = false;
    queue<int> vexQueue;
    for (int i = 0; i < vexNum;++i)
    {
        //be careful of the different connected components.
        if(visited[i] == false)
        {
            vexQueue.push(i);
            visited[i] = true;
            cout << G_adjList[i].info << " ";
            while( ! vexQueue.empty() )
            {
                int tempVex = vexQueue.front(); 
                vexQueue.pop();
                for (ArcNode *arc = G_adjList[tempVex].firstArc; arc != nullptr;
                       arc = arc->next)
                {
                    if (visited[arc->adjvex] == false)
                    {
                        vexQueue.push(arc -> adjvex);
                        visited[arc -> adjvex] = true;
                        cout << G_adjList[arc -> adjvex].info << " ";
                    }
                }//for (ArcNode *arc = G_adjList[tempVex].firstArc; 
            }//while
            //in order to distinguish different connected components.
            cout << endl;
        }//if
        
    }//for (int i = 0; i < vexNum;++i)
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */

int main()
{
    AdjListGraph<char> Graph;
    cout << "now start to dfs.\n";
    dfs_traverse_adjList(Graph);
    cout << "now start to bfs.\n";
    bfs_traverse_adjList(Graph);
    return 0;
}
