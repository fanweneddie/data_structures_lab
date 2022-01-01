#include "../graphADT/adjMatrixGraph.h"
#include <iostream>
using namespace std;
const int MAX_VEX_NUM = 10;
double dist[MAX_VEX_NUM][MAX_VEX_NUM];
bool path[MAX_VEX_NUM][MAX_VEX_NUM][MAX_VEX_NUM];
//*(arcsPtr + MAX_VERTEX_NUM * i + j) that is arcs[i][j];
void floyd(const AdjMatrixGraph<char> G)
{
    const double *arcsPtr = G.get_arcs();
    int vexNum = G.get_vexNum();
    for (int u = 0; u < vexNum;++u)
    {
        for (int v = 0; v < vexNum;++v)
        {
            dist[u][v] = *(arcsPtr + MAX_VERTEX_NUM * u + v);
            for (int w = 0; w < vexNum;++w)
                path[u][v][w] = false;
            if( dist[u][v] < INFINITY )
            {
                path[u][v][u] = true;
                path[u][v][v] = true;
            }//if
        }//for v
    }// for u

    cout << "debug01:the shortest distance: \n";
    for (int u = 0; u < vexNum; ++u)
    {
        for (int v = 0; v < vexNum; ++v)
        {
            cout << dist[u][v] << " ";
        }
        cout << endl;
    }
    // the main iteration
    for (int u = 0; u < vexNum;++u)// the vex in the middle of a path
    {
        for (int v = 0; v < vexNum;++v)
        {
            for (int w = 0; w < vexNum;++w)
            {
                if( dist[v][w] > dist[v][u] + dist[u][w] )
                {
                    dist[v][w] = dist[v][u] + dist[u][w];
                    for (int i = 0; i < vexNum;++i)
                    {
                        path[v][w][i] = path[v][u][i] || path[u][w][i];
                    }//for i
                }//if 
            }//for w
        }//for v
        cout << "debug02:the shortest distance: \n";
    for (int u = 0; u < vexNum; ++u)
    {
        for (int v = 0; v < vexNum; ++v)
        {
            cout << dist[u][v] << " ";
        }
        cout << endl;
    }
    }//for u
    cout << "now output the shortest distance: \n";
    for (int u = 0; u < vexNum; ++u)
    {
        for (int v = 0; v < vexNum; ++v)
        {
            cout << dist[u][v] << " ";
        }
        cout << endl;
    }
    cout << "now output the shortest path: \n";
    for (int u = 0; u < vexNum; ++u)
    {
        for (int v = 0; v < vexNum;++v)
        {
            for (int w = 0; w < vexNum;++w)
            {
                if( path[u][v][w] == true)
                    cout << w;
                else
                    cout << " ";
            }//for
            cout << "   ";
        }
        cout << endl;
    }
}

int main()
{
    AdjMatrixGraph<char> Graph;
    cout << "now getting the shortest path using floyd algo.\n";
    floyd(Graph);
    return 0;
}
/*
please input the type of graph.
1.dirGraph  2.undirGraph  3.dirNet  4.undirNet
3
please input the number of vex.
3
please input the number of arc.
5
please input the info of vexs.
0 1 2
please input the directed path.(e.g. A B w means A->B has weight w.)
0 1 4
0 2 11
1 0 6
1 2 2
2 0 3
*/