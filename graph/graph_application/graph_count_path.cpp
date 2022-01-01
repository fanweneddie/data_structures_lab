#include "../graphADT/adjMatrixGraph.h"

/* ################################################################## */
// dfs function for traversing a graph
//RECURSIVE FUNCTION
void dfs_count_path(const AdjMatrixGraph<char> &G, const int & currVex, 
    const int & endVex,bool *visitedPtr, int *pathPtr, 
    int & count,const int &length,int & pathNum)
{
    vector<char> vexInfo = G.get_vexs();
    const double *arcsPtr = G.get_arcs();
    int vexNum = G.get_vexNum();
    visitedPtr[currVex] = true;
    pathPtr[count] = currVex;
    if(currVex == endVex && count == length)
    {
        cout << "One path is found:\n";
        ++pathNum;
        for(int i = 0;i <= length;++i)
        {
            cout << vexInfo[ pathPtr[i] ] << " ";
        }
        cout << endl;
        ++count;
    }
    else
    {
        ++count;
        for (int i = 0;i < vexNum;++i)
        {
            if ( *(arcsPtr + MAX_VERTEX_NUM * currVex + i) == 1 && visitedPtr[i] == false )
            {
                dfs_count_path(G, i,endVex,visitedPtr,pathPtr,count,length,pathNum);
            }
        }
    }
    visitedPtr[currVex] = false;
    --count;
}
//OVERALL FUNCTION FOR DFS
void count_path_adjMatrix(const AdjMatrixGraph<char> & G,
        const char &vex_1, const char & vex_2,const int & length)
{
    int pathNum = 0;
    vector<char> vexInfo = G.get_vexs();
    int vexNum = G.get_vexNum();
    bool visited[vexNum];
    bool *visiedPtr = visited;
    int path[length+1];
    int *pathPtr = path;
    int count = 0;
    for(int i = 0;i < vexNum;++i)
        visited[i] = false;
    for (int i = 0; i <= length;++i)
        path[i] = -1;
    int startVex, endVex;
    for (int i = 0; i < vexNum;++i)
    {
        if( vexInfo[i]== vex_1)
        {
            startVex = i;
            break;
        }
    }
    for (int i = 0; i < vexNum;++i)
    {
        if( vexInfo[i] == vex_2)
        {
            endVex = i;
            break;
        }
    }
    dfs_count_path(G, startVex, endVex, visiedPtr, pathPtr, count, length,pathNum);
    cout << "there are " << pathNum << " paths.\n";
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */


int main()
{
    cout << "please input a directed graph.\n";
    AdjMatrixGraph<char> Graph;
    cout << "the program will count "
          << "how many k-length paths are there between two vertexes.\n"
          << "please input vertex u and v and a length k.\n";
    char vex_1,vex_2;
    int len;
    cin >> vex_1 >> vex_2 >> len;
    count_path_adjMatrix(Graph, vex_1, vex_2, len);
    return 0;
}