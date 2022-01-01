#include "../graphADT/adjMatrixGraph.h"
#include <iostream>
using namespace std;
const double MAX_WEIGHT = 9999;
const int MAX_VEX_NUM = 10;
 //using integers to represent each vertexes.
struct
{
    int adjvex;         //adjvex and j are connected
    double lowCost;     // the cost of (adjvex,j)
} closedge[MAX_VEX_NUM];

// getting the index of the minimal weight.
int get_minIndex(int vexNum)
{
    double minWeight = MAX_WEIGHT;
    int minIndex = 1;
    for (int j = 1; j < vexNum;++j)
    {
        if(  closedge[j].lowCost > 0 && closedge[j].lowCost < minWeight )
        {
            minWeight = closedge[j].lowCost;
            minIndex = j;
        }
    }
    return minIndex;
}
/* PRIM algorithm: searching the mininum spanning tree 
-- in a connected graph.
INPUT : matrixgraph G, the starting vertex u
OUTPUT: print the arcs of the MST
*/
void MST_prim( const AdjMatrixGraph<char> G,int startVex )
{
    int tempVex = startVex;
    //arcsPtr points to the matrix
    const double *arcsPtr = G.get_arcs();
    int vexNum = G.get_vexNum();
    //initialization of closedge array
    for (int j = 1; j < vexNum;++j)
    {
        if (j != tempVex)
        {
            closedge[j].adjvex = startVex;
            closedge[j].lowCost = *(arcsPtr + MAX_VERTEX_NUM * tempVex + j);
        }
    }
    closedge[tempVex].adjvex = tempVex;
    closedge[tempVex].lowCost = 0;
    // the main iteration process
    for (int i = 1; i <= vexNum - 1; ++i)
    {
        tempVex = get_minIndex(vexNum);
        //output the newly found arc
        cout << closedge[tempVex].adjvex << "  " << tempVex << endl;
        closedge[tempVex].lowCost = 0;
        // renew U and update the closedge array.
        for (int j = 1; j < vexNum;++j)
        {
            if( *(arcsPtr + MAX_VERTEX_NUM * tempVex + j) < 
                closedge[j].lowCost  )
            {
                closedge[j].lowCost = *(arcsPtr + MAX_VERTEX_NUM * tempVex + j);
                closedge[j].adjvex = tempVex;
            }
        }
    }//for (int i = 1; i <= vexNum - 1; ++i)
}

int main()
{
    AdjMatrixGraph<char> Graph;
    cout << "now getting the MST.\n";
    MST_prim(Graph, 0);
    return 0;
}
/*
TESTING DATA1
please input the type of graph.
1.dirGraph  2.undirGraph  3.dirNet  4.undirNet
4
please input the number of vex.
4
please input the number of arc.
5
please input the info of vexs.
0 1 2 3 
please input the directed path.(e.g. A B w means A-B has weight w.)
0 1 10
0 2 1
0 3 1
1 3 1
2 3 1
now getting the MST.
testing data2:
please input the type of graph.
1.dirGraph  2.undirGraph  3.dirNet  4.undirNet
4
please input the number of vex.
6
please input the number of arc.
10
please input the info of vexs.
0 1 2 3 4 5
please input the directed path.(e.g. A B w means A-B has weight w.)
0 1 6
0 2 1
0 3 5
1 2 5
1 4 3
2 4 6
2 3 5
2 5 4
3 5 2
4 5 6
*/