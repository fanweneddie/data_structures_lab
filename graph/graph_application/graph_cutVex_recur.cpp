#include "../graphADT/adjListGraph.h"
// USING ADJACENT LIST TO STORE THE INFO OF A GRAPH.
// INPUT A CONNECTED GRAPH
// THIS PROGRAM WOULD FIND OUT THE CUT VERTEX IN THIS GRAPH
// -BY USING RECURSIVE DFS.

/* The recursive function to figure out the low array. 
 low[v] = min { visited[v],low[w],visited[k] };
 w is v's son in a dfs tree and v and w is connected.
 k is the ancestor that is connected(in dotted line) with v's subtree. */
void dfs_recur( const AdjListGraph<char> G,const int & currVex,
            int * visitedPtr, int * lowPtr, int & count ,int & cutVexNum)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int min = ++count;
    // record the visiting order of each vertex.
    visitedPtr[currVex] = min;
    bool isCutVex = false;
    // since currVex is in a tree that is connected, it must have its adjacent vertex
    // so the iteration below would not be skipped.
    for (ArcNode *arc = G_adjList[currVex].firstArc; arc != nullptr;
         arc = arc->next)
    {
        // case 1 : this vertex has not been searched.
        if (visitedPtr[arc->adjvex] == 0 )
        {
            dfs_recur(G, arc->adjvex, visitedPtr,lowPtr,count,cutVexNum);
            //********** important *********//
            //let min = the minimal value of low[w] (many) and visited[v].
            if( lowPtr[arc->adjvex] < min )
                min = lowPtr[arc->adjvex];
            // v's son w can not connect to prior to v's ancestor, so v is a cut vex.  
            if( lowPtr[arc->adjvex] >= visitedPtr[currVex]  && !isCutVex)
            {
                cout << "one cut vertex has been found: " << G_adjList[currVex].info << endl;
                ++cutVexNum;
                isCutVex = true;
            }
        }  //if (visitedPtr[arc->adjvex] == 0 )
        // case 2 : this vertex has been visited.
        // let min = the minimum of the original one and visited[k]
        else if( visitedPtr[arc->adjvex] < min)
        {
            min = visitedPtr[arc->adjvex];
        }        
    }//for (ArcNode *arc ....
    // after the iteration,we get that low[v] = min { visited[v],low[w],visited[k] }.
    lowPtr[currVex] = min;
}


/* the function to initialize the visited,low and count
 suppose that the input graph is connected. */
 void find_cutVex(const AdjListGraph<char> G)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int vexNum = G.get_vexNum(), count = 1,cutVexNum = 0;
    // visited shows the visiting order of vertex.
    // visited[v] = 0 means v has not been visited. 
    int visited[vexNum];
    int *visitedPtr = visited;
    for (int i = 0; i < vexNum;++i)
        visited[i] = 0;
    //low[v] means the earliest ancestor that the subtree of v can connect to.
    //the initialization of low doesn't matter.
    //- because we can use DFS to figure out low in a post order way.
    int low[vexNum];
    int *lowPtr = low;
    for (int i = 0; i < vexNum;++i)
        low[i] = 0;
    visited[0] = 1;
    //set the vertex 0 as the root of the generating tree.
    ArcNode *arc = G_adjList[0].firstArc;
    int v = arc->adjvex;
    dfs_recur(G, v,visitedPtr,lowPtr,count,cutVexNum);
    // vertex 0 has more than 1 subtree, firstly it is a cut vertex.
    // then keep on searching its remaining subtrees.
    if(count < vexNum)
    {
        cout << "one cut vertex has been found: " << G_adjList[0].info << endl;
        ++cutVexNum;
        // dfs searching its remaining subtree.
        for (ArcNode *arcTemp = arc->next; arcTemp != nullptr;
         arcTemp = arcTemp->next)
        {
            if( visited[ arcTemp->adjvex ] == 0 )
                dfs_recur(G, arcTemp->adjvex , visitedPtr, lowPtr, count,cutVexNum);
        }
    }//if(count < vexNum)
     if( cutVexNum == 0)
         cout << "there is no cut vertex in this graph.\n";
    else
        cout << "there are " << cutVexNum << " cut vertexes in this graph.\n";
}



int main()
{
    AdjListGraph<char> Graph;
    cout << "now getting the cut vertex of the graph.\n";
    find_cutVex(Graph);
    return 0;
}