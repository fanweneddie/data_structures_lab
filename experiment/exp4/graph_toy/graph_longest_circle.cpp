#include "C:\Users\Eddie\Desktop\sophomore\data_structure\graph\graphADT\adjListGraph.h"
#include <algorithm>

/* knowing all of the circles, get the circle with the biggest overall weight.
return the index of that circle in the allPaths vector. 
the max Weight is changed as a reference parameter */
int get_longest_circle(const AdjListGraph<char> & G,vector<vector<int>> &allPaths,
                    int & maxCircleWeight)
{
    int maxCircleIndex = 0;
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int pathNum = allPaths.size();
    ArcNode *arc;
    for (int i = 0; i < pathNum;++i)
    {
        int currWeight = 0;
        int pathLen = allPaths[i].size();
        for (int j = 0; j < pathLen;++j)
        {
            // a stupid way to find the weight of each arc
            // given its two vexes.
            arc = G_adjList[ (allPaths[i])[j] ].firstArc; 
            while( arc->adjvex != (allPaths[i]) [ (j+1) % pathLen ]  )
                arc = arc->next;
            currWeight += arc->weight;
        }
        if(currWeight > maxCircleWeight)
        {
            maxCircleWeight = currWeight;
            maxCircleIndex = i;
        }
    }
    return maxCircleIndex;
}

/*adding the newly found circle to all the paths.
make sure that this circle is unique.
compared with that append function in the directed graph version,
-the way to judge repetition is different:
1. if the size of path is 3 (such as a b a), then it is illegal.
2. if two sequence of vex in paths is the same or the opposite,
-then the second one is of repetition. */
void non_repe_append(vector<int>& path,vector<vector<int>> &allPaths)
{
    if( path.size() == 3 )
        return;
    path.pop_back();
    int currPathLen = path.size();
    int pathNum = allPaths.size();
    bool repeFlag = false;
    bool equal = true;
    // check whether the new path is of repetition with all the
    // -other paths that has been found
    // by checking whether the sequence is the same or the opposite.
    for (int i = 0; i < 2*pathNum;++i)
    {
        equal = true;
        vector<int> tempPath = allPaths[i/2];
        //for the second time, check whether the newPath's vex sequence
        // -is opposite to that of the path found. 
        if(i % 2 == 1)
            reverse(tempPath.begin(), tempPath.end());
        int tempPathLen = tempPath.size();
        //we don't need to compare one by one.
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
                //check whether the vex is of repetition one by one.
                for (int j = 0; j < tempPathLen;++j)
                {
                    if( tempPath[ (start + j)%tempPathLen ] != path[j] )
                    {
                        equal = false;
                        break;
                    }
                }
            }//else(start != -1 )
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
// almost the same as that of the directed graph.
void dfs_search(const AdjListGraph<char> &G,const int & currVex,
            const int& endVex,bool * visitedPtr,vector<int>& path,
            vector<vector<int>> &allPaths)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    visitedPtr[currVex] = true;
    path.push_back(currVex);

    if (currVex == endVex && path.size() != 1 )
    {
        //this is the "fake ring"! we need to backtrack.
        if(path.size() == 3 ) 
            path.pop_back();
        //it is a circle, so we then need to check repetition and append.
        else
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
    //backtrack in dfs
    visitedPtr[currVex] = false;
    path.pop_back();
}

//OVERALL FUNCTION FOR DFS
//initialization of visited,allPaths
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
    //output the result.
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
    // find the circle with the biggest weight.
    if( pathNum > 0)
    {
        int maxCircleWeight = 0;
        int maxCircleIndex = get_longest_circle(G, allPaths, maxCircleWeight);
        cout << "the circle with the greatest weight is \n";
        int maxPathLen = allPaths[maxCircleIndex].size();
        for (int j = 0; j < maxPathLen;++j)
        {
            cout << G_adjList[(allPaths[maxCircleIndex])[j]].info << " ";
        }
        cout << "\nits weight is " << maxCircleWeight << endl;
    }
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
/*
testing data1
4 6 A B C D
A B 3
A C 2
A D 1
B C 10
B D 1
C D 4
testing data 2:
10 12
0 1 2 3 4 5 6 7 8 9
0 4 2 
0 9 1
1 2 6
1 3 3
1 4 9
2 4 5
2 6 5
3 5 6
5 6 4
5 9 6
6 7 5
7 8 5 
*/

int main()
{
    cout << "please input an undirected net.\n";
    AdjListGraph<char> Graph;
    cout << "the program will search all the circles in the graph.\n ";
    search_all_circle(Graph);
    return 0;
}

//WRONG FUNCTION CODE
/* ################################################################## */
/*
void non_repe_append(vector<int>& path,vector<vector<int>> &allPaths,
                    vector<vector<int>> & allSortedVex )
{
    //case 1 : we don't consider the ring in a simple graph.
    if( path.size() == 3 )
        return;
    path.pop_back();
    int pathNum = allPaths.size();
    bool repeFlag = false;
    bool equal = true;
    //
    vector<int> currPathVex = path;
    sort(currPathVex.begin(), currPathVex.end());
    // check whether the new path is of repetition with all the
    // other paths that have been found
    for (int i = 0; i < pathNum; ++i)
    {
        equal = true;
        vector<int> tempPathVex = allSortedVex[i];
        int tempPathLen = allSortedVex[i].size();
        for (int j = 0; j < tempPathLen; ++j)
        {
            if (currPathVex[j] != tempPathVex[j])
            {
                equal = false;
                break;
            }
        }

        if (equal == true)
        {
            repeFlag = true;
            break;
        }
        } //for 
    if(repeFlag == false)
    {
        allPaths.push_back(path);
        allSortedVex.push_back(currPathVex);
    }
}
*/