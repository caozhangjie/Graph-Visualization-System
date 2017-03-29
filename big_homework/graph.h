#ifndef GRAPH
#define GRAPH

#include "node.h"
#include "edge.h"
#include <map>

class treeLayout;

class Graph
{
protected:
    //存储总节点数与总边数
    int node_num;
    int edge_num;
    //存储每个节点的作为起始点或作为终点时边的另一头的点
    vector<vector<int> > node_in;  //本点为起始点
    vector<vector<int> > node_out; //本点为终点
    vector<vector<int> > edge_node;
    //存储每个节点的入度和出度
    vector<int> every_node_in;
    vector<int> every_node_out;
    vector<int> every_node_sum;
    map<vector<int> , int> node_to_edge;
protected:
    void setEveryNodeIn(){every_node_in.clear();for(int i = 0; i < node_num; i++) {every_node_in.push_back(node_in[i].size());}}
    void setEveryNodeOut(){every_node_out.clear();for(int i = 0; i < node_num; i++) {every_node_out.push_back(node_out[i].size());}}
public:
    virtual void initialize() = 0;
    virtual int getRealId(int){return 0;}
    int getNodeNum(){return node_num;}
    int getEdgeNum(){return edge_num;}
    int getInNum(int id){return every_node_in[id];}
    int getOutNum(int id){return every_node_out[id];}
    int getSumNum(int id){return every_node_sum[id];}
    map<vector<int> , int> & getNodeToEdge(){return node_to_edge;}
    vector<vector<int> > & getNodeIn(){return node_in;}
    vector<vector<int> > & getNodeOut(){return node_out;}
    vector<vector<int> > & getEdgeNode(){return edge_node;}   
};

#endif // GRAPH

