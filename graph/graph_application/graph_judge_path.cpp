#include "../graphADT/adjListGraph.h"


/* ################################################################## */
// dfs function for traversing a graph
//RECURSIVE FUNCTION
void dfs_adjList(const AdjListGraph<char> &G, const int & currVex, 
    const int & endVex,bool *visitedPtr, int *pathPtr, 
    int & count,const int &length,bool &flagOfFound)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    visitedPtr[currVex] = true;
    pathPtr[count] = currVex;
    if(currVex == endVex && count == length)
    {
        cout << "the path is found:\n";
        flagOfFound = true;
        for(int i = 0;i <= length;++i)
        {
            cout << G_adjList[ pathPtr[i] ].info << " ";
        }
        cout << endl;
        return;
    }
    ++count;
    for (ArcNode *arc = G_adjList[currVex].firstArc; arc != nullptr;
         arc = arc->next)
    {
        if (visitedPtr[arc->adjvex] == false && flagOfFound == false)
        {
            dfs_adjList(G, arc->adjvex,endVex,visitedPtr,pathPtr,count,length,flagOfFound);
        }
    }
    visitedPtr[currVex] = false;
    --count;
}
//OVERALL FUNCTION FOR DFS
void check_path_adjList(const AdjListGraph<char> & G,
        const char &vex_1, const char & vex_2,const int & length)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int vexNum = G.get_vexNum();
    bool visited[vexNum];
    bool *visiedPtr = visited;
    int path[length+1];
    int *pathPtr = path;
    int count = 0;
    for(int i = 0;i < vexNum;++i)
        visited[i] = false;
    for (int i = 0; i <= length;++i)
        path[i] = 0;
    int startVex, endVex;
    for (int i = 0; i < vexNum;++i)
    {
        if(G_adjList[i].info == vex_1)
        {
            startVex = i;
            break;
        }
    }
    for (int i = 0; i < vexNum;++i)
    {
        if(G_adjList[i].info == vex_2)
        {
            endVex = i;
            break;
        }
    }
    bool flagOfFound = false;
    dfs_adjList(G, startVex, endVex, visiedPtr, pathPtr, count, length,flagOfFound);
    if(flagOfFound == false)
        cout << "path not found.\n";
    cout << endl;    
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */


int main()
{
    cout << "please input a undirected graph.\n";
    AdjListGraph<char> Graph;
    cout << "the program will check whether "
          << "there is a k-length path between two vertexes.\n"
          << "please input vertex u and v and a length k.\n";
    char vex_1,vex_2;
    int len;
    cin >> vex_1 >> vex_2 >> len;
    check_path_adjList(Graph, vex_1, vex_2, len);
    return 0;
}