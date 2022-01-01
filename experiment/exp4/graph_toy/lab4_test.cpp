#include "../../../graph/graph_application/graph_shortest_path.cpp"
#include "../../../graph/graph_application/graph_cutVex_nonRecur.cpp"
/*
testing data1:
8 10
0 1 2 3 4 5 6 7
0 1 
0 2
1 2
1 3
1 6
2 5
3 4
3 6
5 6
5 7

testing data2:
10 12
0 1 2 3 4 5 6 7 8 9
0 4
0 9
1 2
1 3
1 4
2 4
2 6
3 5
5 6
5 9
6 7
7 8
*/


int main()
{
    cout << "please input a undirected graph.\n";
    AdjMatrixGraph<char> Graph1;
    cout << "now getting the cut vertex of the graph.\n";
    find_cutVex(Graph1);
    AdjListGraph<char> Graph2;
    cout << "now start to search the shortest path from v0 to every other vertex.\n";
    bfs_traverse_adjList(Graph2);
    return 0;
}