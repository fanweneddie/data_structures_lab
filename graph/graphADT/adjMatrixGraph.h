#ifndef ADJMATRIXGRAPH
#define ADJMATRIXGRAPH
#include "adjListGraph.h"
#include <vector>
#include <iostream>
using namespace std;
const int INFINITY = 9999;
const int MAX_VERTEX_NUM = 20;

/*four types of graph
enum graph_Type 
{
    dirGraph,
    undirGraph,
    dirNet,
    undirNet
};*/
//the definition of arc, the meaning of w 
//-depends on the type of graph.

//four constructive functions to create different types of graphs.
//use reference parameter to save multiple values.
template <class T>
void create_dirGraph(vector<T> & vexsR,double *arcsPtr, int & vexNum,int & arcNum);
template <class T>
void create_undirGraph(vector<T> & vexsR, double *arcsPtr,int & vexNum,int & arcNum);
template <class T>
void create_dirNet(vector<T> & vexsR, double *arcsPtr,int & vexNum,int & arcNum);
template <class T>
void create_undirNet(vector<T> & vexsR, double *arcsPtr, int &vexNum, int &arcNum);

template <class T>
class AdjMatrixGraph;

template <class T>
ostream &operator<< (ostream &out, const AdjMatrixGraph<T> & amg);

template <class T>
class AdjMatrixGraph
{
    private:
        int vexNum;
        int arcNum;
        vector<T> vexs;
        double arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
        graphType kind;
    public:
        AdjMatrixGraph();
        int get_vexNum() const { return vexNum; }
        int get_arcNum() const { return arcNum; }
        graphType get_type() const { return kind; }
        vector<T> get_vexs() const { return vexs; }
        // we can get the weight of the graph through the matrix.
        const double *get_arcs() const { const double *arcsPtr = &arcs[0][0];
                                    return arcsPtr;  }
        friend ostream &operator<< <> (ostream &out, const AdjMatrixGraph &amg);

};

template <class T>
AdjMatrixGraph<T>::AdjMatrixGraph()
{
    cout << "please input the type of graph.\n";
    cout << "1.dirGraph  2.undirGraph  3.dirNet  4.undirNet\n";
    int typeChoice = 0;
    cin >> typeChoice;
    double *arcsPtr = &arcs[0][0];
    switch( typeChoice)
    {
        case 1:
            kind = dirGraph;
            create_dirGraph(vexs,arcsPtr,vexNum, arcNum);
            break;
        case 2:
            kind = undirGraph;
            create_undirGraph(vexs,arcsPtr, vexNum, arcNum);
            break;
        case 3:
            kind = dirNet;
            create_dirNet(vexs,arcsPtr, vexNum, arcNum);
            break;
        case 4:
            kind = undirNet;
            create_undirNet(vexs, arcsPtr, vexNum, arcNum);
            break;
        default:
            cout << "invalid graph type!!!\n";
            throw " invalid graph type!\n";
            break;
    }
}
//print the basic info of the graph
// the most important info is the adjacent matrix.
template<class T>
ostream &operator<<(ostream &out, const AdjMatrixGraph<T> &amg)
{
    out << "The info of the graph is as below:\n";
    //first, print the type of the graph.
    switch(amg.kind)
    {
        case dirGraph:
            out << "this is a directed graph.\n";
            break;
        case undirGraph:
            out << "this is a undirected graph.\n";
            break;
        case dirNet:
            out << "this is a directed net.\n";
            break;
        case undirNet:
            out << "this is a undirected net.\n";
            break;
        default:
            break;
    }

    out << "the vertex number is " << amg.vexNum << endl;
    out << "the arc number is " << amg.arcNum << endl;
    out << "the id of the vertexs are :\n";
    for (int i = 0; i < amg.vexNum;++i)
        out << amg.vexs[i] << " ";
    out << "\nthe arc matrix is :\n";
    for (int i = 0; i < amg.vexNum;++i)
    {
        for (int j = 0; j < amg.vexNum;++j)
            out << amg.arcs[i][j] << " ";
        out << endl;
    }
    return out;
}

template <class T>
void create_dirGraph(vector<T> & vexsR,double *arcsPtr, int & vexNum,int & arcNum)
{
    cout << "please input the number of vex.\n";
    cin >> vexNum;
    cout << "please input the number of arc.\n";
    cin >> arcNum;
    cout << "please input the info of vexs.\n";
    T vexInfo;
    for (int i = 0;i < vexNum;++i)
    {
        cin >> vexInfo;
        vexsR.push_back(vexInfo);
    }
    //initialization for the adjacent matrix.
    for (int i = 0; i < MAX_VERTEX_NUM;++i)
        for (int j = 0; j < MAX_VERTEX_NUM;++j)
            *(arcsPtr + MAX_VERTEX_NUM * i + j)= 0;
    cout << "please input the directed arcs.(e.g. A B means A->B)\n";
    for (int i = 0; i < arcNum;++i)
    {
        T vex1Info,vex2Info;
        cin >> vex1Info >> vex2Info;
        int vex1Pos = -1, vex2Pos = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex1Info)
            {
                vex1Pos = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex2Info)
            {
                vex2Pos = j;
                break;
            }
        }
        // showing the directed arc in the adjacent matrix.
        //NOTE: if A -> B, the position on the up-right place will be set 1.
        *(arcsPtr + MAX_VERTEX_NUM * vex1Pos + vex2Pos) = 1;
    }//for (int i = 0; i < arcNum;++i) ( inputting the arcs.)
}

template <class T>
void create_undirGraph(vector<T> & vexsR, double *arcsPtr,int & vexNum,int & arcNum)
{
    cout << "please input the number of vex.\n";
    cin >> vexNum;
    cout << "please input the number of arc.\n";
    cin >> arcNum;
    cout << "please input the info of vexs.\n";
    T vexInfo;
    for (int i = 0;i < vexNum;++i)
    {
        cin >> vexInfo;
        vexsR.push_back(vexInfo);
    }
    //initialization for the adjacent matrix.
    for (int i = 0; i < MAX_VERTEX_NUM;++i)
        for (int j = 0; j < MAX_VERTEX_NUM;++j)
            *(arcsPtr + MAX_VERTEX_NUM * i + j)= 0;
    cout << "please input the undirected arcs.(e.g. A B means A-B)\n";
    for (int i = 0; i < arcNum;++i)
    {
        T vex1Info,vex2Info;
        cin >> vex1Info >> vex2Info;
        int vex1Pos = -1, vex2Pos = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex1Info)
            {
                vex1Pos = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex2Info)
            {
                vex2Pos = j;
                break;
            }
        }
        // showing the undirected arc in the adjacent matrix.
        // to make it symmetirical.
        *(arcsPtr + MAX_VERTEX_NUM * vex1Pos + vex2Pos) = 1;
        *(arcsPtr + MAX_VERTEX_NUM * vex2Pos + vex1Pos) = 1;
    }//for (int i = 0; i < arcNum;++i)  ( inputting the arcs.)
}

template <class T>
void create_dirNet(vector<T> & vexsR, double *arcsPtr,int & vexNum,int & arcNum)
{
    cout << "please input the number of vex.\n";
    cin >> vexNum;
    cout << "please input the number of arc.\n";
    cin >> arcNum;
    cout << "please input the info of vexs.\n";
    T vexInfo;
    for (int i = 0;i < vexNum;++i)
    {
        cin >> vexInfo;
        vexsR.push_back(vexInfo);
    }
    //initialization for the adjacent matrix.
    for (int i = 0; i < MAX_VERTEX_NUM;++i)
        for (int j = 0; j < MAX_VERTEX_NUM;++j)
        {
            if( i != j )
                *(arcsPtr + MAX_VERTEX_NUM * i + j) = INFINITY;
            else// i == j
                *(arcsPtr + MAX_VERTEX_NUM * i + j) = 0;
        }
    cout << "please input the directed path.(e.g. A B w means A->B has weight w.)\n";
    for (int i = 0; i < arcNum;++i)
    {
        T vex1Info,vex2Info;
        double weight = 0;
        cin >> vex1Info >> vex2Info >> weight;
        int vex1Pos = -1, vex2Pos = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex1Info)
            {
                vex1Pos = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex2Info)
            {
                vex2Pos = j;
                break;
            }
        }
        // showing the directed path and its weight in the adjacent matrix.
        //NOTE: if A -> B, the position on the up-right place will be set as the weight.
        *(arcsPtr + MAX_VERTEX_NUM * vex1Pos + vex2Pos) = weight;
    }//for (int i = 0; i < arcNum;++i) ( inputting the arcs.)
}

template <class T>
void create_undirNet(vector<T> & vexsR, double *arcsPtr, int &vexNum, int &arcNum)
{
    cout << "please input the number of vex.\n";
    cin >> vexNum;
    cout << "please input the number of arc.\n";
    cin >> arcNum;
    cout << "please input the info of vexs.\n";
    T vexInfo;
    for (int i = 0;i < vexNum;++i)
    {
        cin >> vexInfo;
        vexsR.push_back(vexInfo);
    }
    //initialization for the adjacent matrix.
    for (int i = 0; i < MAX_VERTEX_NUM;++i)
        for (int j = 0; j < MAX_VERTEX_NUM;++j)
        {
            if( i != j )
                *(arcsPtr + MAX_VERTEX_NUM * i + j) = INFINITY;
            else// i == j
                *(arcsPtr + MAX_VERTEX_NUM * i + j) = 0;
        }
    cout << "please input the directed path.(e.g. A B w means A-B has weight w.)\n";
    for (int i = 0; i < arcNum;++i)
    {
        T vex1Info,vex2Info;
        double weight = 0;
        cin >> vex1Info >> vex2Info >> weight;
        int vex1Pos = -1, vex2Pos = -1;
        //finding the index of vex1.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex1Info)
            {
                vex1Pos = j;
                break;
            }
        }
        //finding the index of vex2.
        for (int j = 0; j < vexNum;++j)
        {
            if(vexsR[j] == vex2Info)
            {
                vex2Pos = j;
                break;
            }
        }
        // showing the directed path and its weight in the adjacent matrix.
        *(arcsPtr + MAX_VERTEX_NUM * vex1Pos + vex2Pos) = weight;
        *(arcsPtr + MAX_VERTEX_NUM * vex2Pos + vex1Pos) = weight;
    }//for (int i = 0; i < arcNum;++i) ( inputting the arcs.)
}


#endif