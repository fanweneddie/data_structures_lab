#include "C:\Users\Eddie\Desktop\sophomore\data_structure\graph\graphADT\adjMatrixGraph.h"
#include <stack>
//USING ADJACENT MATRIX TO STORE THE INFO OF THE GRAPH.
// INPUT A CONNECTED GRAPH
// THIS PROGRAM WOULD FIND OUT THE CUT VERTEX IN THIS GRAPH
// -BY USING NON-RECURSIVE DFS.

//Getting baseVex 's next adjacent vertex after currvex
// if currVex  = -1, return the first adjacent vertex of baseVex.
// there is no adjacent vertex after the currVex , return -1;
int get_next_adjVex(const AdjMatrixGraph<char> G,int baseVex, int currVex)
{
    const double *arcsPtr = G.get_arcs();
    int vexNum = G.get_vexNum();
    if(currVex == vexNum -1)
        return -1;
    for (int vex = currVex + 1; vex < vexNum;++vex)
    {
        if( *(arcsPtr + MAX_VERTEX_NUM * baseVex + vex) == 1 )
            return vex;
    }
    return -1;
}
// a couple of vertexes
// vex_2 can be a mark, if it = -1, that means vex_2 doesn't exist.
struct Couple
{
    int vex_1;
    int vex_2;
};

/* After ascertaining a root, use this to build its subtree,
-figure out visited,low and min in a non recursive way.
 low[v] = min { visited[v],low[w],visited[k] };
 w is v's son in a dfs tree and v and w is connected.
 k is the ancestor that is connected(in dotted line) with v's subtree. */
void dfs_non_recur(const AdjMatrixGraph<char> G, const int & vex_v, stack<Couple> & S,
                int * visited,int * low ,int * mins,int *previous,
                bool *isCutVexPtr, int & count, int & cutVexNum)
{
    mins[vex_v] = ++count;
    visited[vex_v] = mins[vex_v];
    Couple cp;
    cp.vex_1 = vex_v;
    cp.vex_2 = -1;
    S.push(cp);
    while( !S.empty())
    {
        cp = S.top();
        int v = cp.vex_1, w = cp.vex_2;
        //case : w exists.
        // try to use (v,w) to change mins[v] and get low[v]
        if (w != -1)
        {
            // v is the father of w
            if (visited[v] < visited[w] && previous[w] == v)
            {
                if (low[w] < mins[v])
                    mins[v] = low[w];
                // isCutvex can avoid repeating reproting the same vertex as cut vertex.
                if (low[w] >= visited[v] && isCutVexPtr[v] == false)
                {
                    cout << "one cut vertex has been found: " << (G.get_vexs())[v] << endl;
                    isCutVexPtr[v] = true;
                    ++cutVexNum;
                }
            }
            //v is the son of w
            else
            {
                if (visited[w] < mins[v])
                    mins[v] = visited[w];
            }
            } //if( c2.vex_2 != -1 )
        S.pop();
        w = get_next_adjVex(G, v, w);
        if(w != -1)
        {
            cp.vex_1 = v;
            cp.vex_2 = w;
            S.push(cp);
            if( visited[w] == 0 )
            {
                mins[w] = ++count;
                visited[w] = mins[w];
                previous[w] = v;
                cp.vex_1 = w;
                cp.vex_2 = -1;
                S.push(cp);
            }
        }
        // w == -1 that is w doesn't exist.
        //we can now get the low[v]
        else
        {
            low[v] = mins[v];
        }
    }//while( !S.empty())
}

/* The non-recursive function to figure out the low array. 
 low[v] = min { visited[v],low[w],visited[k] };
 w is v's son in a dfs tree and v and w is connected.
 k is the ancestor that is connected(in dotted line) with v's subtree. 
 This function also initializes the visited[],low[],min[] and count.
 Suppose that the input graph is connected. */
 void find_cutVex(const AdjMatrixGraph<char> G)
{
    stack<Couple> S;
    vector<char> vexInfo = G.get_vexs();
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
    //since it is a non- recursive function, we need to use an array
    //-to store the min of each vertex.
    //In the process, mins[v] is originally set as visited[v];
    int mins[vexNum];
    int *minsPtr = mins;
    for (int i = 0; i < vexNum;++i)
        mins[i] = 0;
    bool isCutVex[vexNum];
    for(int i = 0;i < vexNum;++i)
        isCutVex[i] = false;
    bool* isCutVexPtr = isCutVex;
    int previous[vexNum];
    for (int i = 0; i < vexNum;++i)
        previous[i] = -1;
    int *previousPtr = previous;
    //set the vertex 0 as the root of the generating tree.
    visited[0] = 1;
    //first consider the first adjacent vertex of vertex 0.
    int vex_v;
    vex_v = get_next_adjVex(G, 0,-1);
    dfs_non_recur(G, vex_v, S,visitedPtr, lowPtr, minsPtr
                    ,previousPtr, isCutVexPtr,count, cutVexNum);
    // vertex 0 has more than 1 subtree, firstly it is a cut vertex.
    // then keep on searching its remaining subtrees.
    if(count < vexNum)
    {
        cout << "one cut vertex has been found: " << vexInfo[0] << endl;
        isCutVexPtr[0] = true;
        ++cutVexNum;
        for (vex_v = get_next_adjVex(G, 0, vex_v); vex_v != -1; 
            vex_v = get_next_adjVex(G, 0, vex_v) )
        {
            dfs_non_recur(G, vex_v, S,visitedPtr, lowPtr, minsPtr
                        ,previousPtr,isCutVexPtr, count, cutVexNum);
        }
    }
     if( cutVexNum == 0)
         cout << "there is no cut vertex in this graph.\n";
    else
        cout << "there are " << cutVexNum << " cut vertexes in this graph.\n";
}
/*
int main()
{
    AdjMatrixGraph<char> Graph;
    cout << "now getting the cut vertex of the graph.\n";
    find_cutVex(Graph);
    return 0;
}
*/