#ifndef TOPICGRAPH
#define TOPICGRAPH

#include "undirectededge.h"
#include "topicnode.h"
#include "docnode.h"
#include "docdialog.h"
#include "graph.h"

class treeLayout;

class TopicGraph:public Graph
{
private:
    vector<TopicNode *> node;
    vector<UndirectedEdge *> edge;
    vector<DocNode *> doc;

    map<int, int> doc_map;
public:
    void initialize(){setEdgeNum();setNodeNum();setEveryNodeIn();setEveryNodeOut(); every_node_sum.clear();
                     for(int i = 0; i < node_num; i++) {every_node_sum.push_back(every_node_in[i]);}}
    void setNodeNum(){node_num = node.size();}
    void setEdgeNum(){edge_num = edge.size();}
    DocNode & getDocNode(int id){return *(doc[id]);}
    vector<DocNode *> & getAllDoc(){return doc;}
    int findNode(int id);
    vector<TopicNode *> & getNode(){return node;}
    vector<UndirectedEdge *> & getEdge(){return edge;}
    map<int, int> & getDocMap(){return doc_map;}
    int getDoc(int id);
    int getRealId(int id);
    void addTopicNode(TopicNode * temp){node.push_back(temp);}
    void addDocNode(DocNode * temp){doc.push_back(temp);}
    void addEdge(UndirectedEdge * temp){edge.push_back(temp);}
    void readInTopicNode(const char * file_name);
    void readInTopicEdge(const char * file_name);
    void readInDocNode(const char *file_name);
    void readSTD(ifstream & fin, char * buffer, TopicNode * & temp_base, int & id);
    ~TopicGraph(){}
    void deleteNode();
    void deleteEdge();
    void deleteDocNode();
    friend class treeLayout;
};


#endif // TOPICGRAPH

