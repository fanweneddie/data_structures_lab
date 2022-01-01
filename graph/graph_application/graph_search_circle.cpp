#include "../graphADT/adjListGraph.h"


/* ################################################################## */
//adding the newly found circle to all the paths.
//make sure that this circle is unique.
void non_repe_append(vector<int>& path,vector<vector<int>> &allPaths)
{
    path.pop_back();
    int currPathLen = path.size();
    int pathNum = allPaths.size();
    bool repeFlag = false;
    bool equal = true;
    // check whether the new path is of repetition with all the
    // other paths that has been found
    for (int i = 0; i < pathNum;++i)
    {
        equal = true;
        vector<int> tempPath = allPaths[i];
        int tempPathLen = allPaths[i].size();
        if(tempPathLen != currPathLen)
        {
            equal = false;
        }
        else
        {
            int start = -1;
            //find the starting index in the temppath.
            // if have not found, it means not equal.
            for (int j = 0; j < tempPathLen;++j)
            {
                if(tempPath[j] == path[0])
                {
                    start = j;
                    break;
                }
            }
            //have not found the start.
            if(start == -1)
            {
                equal = false;
            }
            //have found the start.
            else
            {
                for (int j = 0; j < tempPathLen;++j)
                {
                    if( tempPath[ (start + j)%tempPathLen ] != path[j] )
                    {
                        equal = false;
                        break;
                    }
                }
            }
        }//else (tempPathLen == currPathLen)

        if(equal == true)
        {
            repeFlag = true;
            break;
        }
    }//for (int i = 0; i < pathNum;++i)
    if(repeFlag == false)
    {
        allPaths.push_back(path);
    }
}

// dfs function for traversing a graph
//RECURSIVE FUNCTION
void dfs_search(const AdjListGraph<char> &G,const int & currVex,const int& endVex,
                bool * visitedPtr,vector<int>& path,vector<vector<int>> &allPaths)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    visitedPtr[currVex] = true;
    path.push_back(currVex);
    if (currVex == endVex && path.size() != 1)
    {
        non_repe_append(path, allPaths);
        return;
    }
    for (ArcNode *arc = G_adjList[currVex].firstArc; arc != nullptr;
         arc = arc->next)
    {
        if (visitedPtr[arc->adjvex] == false || arc->adjvex == endVex)
        {
            dfs_search(G,arc->adjvex,endVex,visitedPtr,path,allPaths);
        }
    }
    visitedPtr[currVex] = false;
    path.pop_back();
}

//OVERALL FUNCTION FOR DFS
void search_all_circle(const AdjListGraph<char> & G)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int vexNum = G.get_vexNum();
    bool visited[vexNum];
    bool *visitedPtr = visited;
    vector<int> path;
    vector<vector<int>> allPaths;
    for(int i = 0;i < vexNum;++i)
        visited[i] = false;
    //be careful of the different connected part.
    for (int i = 0; i< vexNum;++i)
    {
        dfs_search(G,i,i,visitedPtr,path,allPaths);
    }
    int pathNum = allPaths.size();
    cout << "there are " << pathNum << " paths in total.\n";
    for (int i = 0; i < pathNum;++i)
    {
        int pathLen = allPaths[i].size();
        for (int j = 0; j < pathLen;++j)
        {
            cout << G_adjList[(allPaths[i])[j]].info << " ";
        }
        cout << endl;
    }
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */


int main()
{
    cout << "please input a directed graph.\n";
    AdjListGraph<char> Graph;
    cout << "the program will search all the circles in the graph.\n ";
    search_all_circle(Graph);
    return 0;
}