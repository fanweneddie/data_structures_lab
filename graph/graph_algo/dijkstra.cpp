#include "../graphADT/adjMatrixGraph.h"
#include <iostream>
using namespace std;
const int MAX_VEX_NUM = 10;
double dist[MAX_VEX_NUM];
bool path[MAX_VEX_NUM][MAX_VEX_NUM];
bool final[MAX_VEX_NUM];
//*(arcsPtr + MAX_VERTEX_NUM * i + j) that is arcs[i][j];
void dijkstra(const AdjMatrixGraph<char> G,int v0)
{
    const double *arcsPtr = G.get_arcs();
    int vexNum = G.get_vexNum();
    //initialization of those arrays.
    for (int u = 0; u < vexNum;++u)
    {
        dist[u] = *(arcsPtr + MAX_VERTEX_NUM * v0 + u);
        final[u] = false;
        for (int v = 0; v < vexNum;++v)
        {
            path[u][v] = false;
        }
        if(dist[u] < INFINITY )
        {
            path[u][v0] = true;
            path[u][u] = true;
        }
    }//for
    final[v0] = true;
    dist[v0] = 0;
    double minWeight = INFINITY;
    int minVex = -1;
    //searching the next v-1 vexes
    for (int u = 1; u < vexNum;++u)
    {
        minWeight = INFINITY;
        minVex = -1;
        for (int v = 0; v < vexNum;++v)
        {
            //search the nearest vex and include it into S
            if(!final[v]) // cautious
            {
                if(dist[v] < minWeight)
                {
                    minWeight = dist[v];
                    minVex = v;
                }//if
            }//if
        }//for v
        //output the vex being found
        if( minVex >= 0 )
        {
            final[minVex] = true;
            cout << "vex: " << minVex << "  ,dist: " << dist[minVex] << endl;
        }
        else
            cout << "the search has ended.\n";
        //change the distance if necessary.
        for (int w = 0; w < vexNum;++w)
        {
            if( !final[w] &&
            dist[w] > dist[minVex] + *(arcsPtr + MAX_VERTEX_NUM * minVex + w) )
            {
                dist[w] = dist[minVex] + *(arcsPtr + MAX_VERTEX_NUM * minVex + w);
                for (int i = 0; i < vexNum;++i)
                    path[w][i] = path[minVex][i];
                path[w][w] = true;
            }//if
        }//for w
    }//for v
}

int main()
{
    AdjMatrixGraph<char> Graph;
    cout << "now getting the shortest path from vex 0.\n";
    dijkstra(Graph, 0);
    return 0;
}
/*
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
0 2 10
0 4 30
0 5 100
1 2 5
2 3 50
3 5 10
4 3 20
4 5 60
*/