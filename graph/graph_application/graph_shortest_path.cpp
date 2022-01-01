#include "../graphADT/adjListGraph.h"
#include <queue>
#include <stack>

/*############################################## */
//bfs function for traversing a graph
void bfs_traverse_adjList(const AdjListGraph<char> &G)
{
    vector<VexNode<char>> G_adjList = G.get_adjList();
    int vexNum = G.get_vexNum();
    //orig[w] = v means that v is w's father.
    int orig[vexNum];
    for(int i = 0; i < vexNum;++i)
        orig[i] = -1;
    bool visited[vexNum];
    for(int i = 0;i < vexNum;++i)
        visited[i] = false;
    // record the shortest path of every vex. 
    vector< stack<char> > shtPath;
    stack<char> onePath;
    for(int i = 0;i < vexNum;++i)
        shtPath.push_back(onePath); 
    queue<int> vexQueue;
    //be careful of the different connected components.
    for (int i = 0; i < vexNum;++i)
    {
        if(visited[i] == false)
        {
            vexQueue.push(i);
            visited[i] = true;
            while( ! vexQueue.empty() )
            {
                int tempVex = vexQueue.front(); 
                vexQueue.pop();
                // when poping a vex, it means that I have found it.
                // So record the shortest path of that tempVex.
                for( int temp = tempVex;orig[temp] != -1;temp = orig[temp] ) 
                {
                    shtPath[tempVex].push( G_adjList[temp].info );
                }
                //pushing the tempVex's sons into the stack.
                for (ArcNode *arc = G_adjList[tempVex].firstArc; arc != nullptr;
                       arc = arc->next)
                {
                    if (visited[arc->adjvex] == false)
                    {
                        vexQueue.push(arc -> adjvex);
                        visited[arc -> adjvex] = true;
                        //
                        orig[arc->adjvex] = tempVex;
                    }
                }//for (ArcNode *arc = G_adjList[tempVex].firstArc; 
            }//while
        }//if    
    }//for (int i = 0; i < vexNum;++i)
    //output the shortest path of every vex.
    for(int i = 1; i < vexNum;++i)
    {
        int tempLen = shtPath[i].size();
         cout << G_adjList[i].info << " : " << G_adjList[0].info;
         while( ! shtPath[i].empty() )
         {
             cout << " -> " << shtPath[i].top();
             shtPath[i].pop();
         }
         cout << "  length: " << tempLen << endl;
    }
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
/*
int main()
{
    AdjListGraph<char> Graph;
    cout << "now start to search the shortest path from v0 to every other vertex\n";
    bfs_traverse_adjList(Graph);
    return 0;
}
*/