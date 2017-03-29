#ifndef PAPER_CONFERENCE_AUTHOR_GRAPH
#define PAPER_CONFERENCE_AUTHOR_GRAPH

#include "paperconferenceauthornode.h"
#include "directededge.h"
#include "graph.h"

class PaperConferenceAuthorGraph: public Graph
{
private:
    vector<PaperConferenceAuthorNode *> node;
    vector<DirectedEdge *> edge;
public:
    PaperConferenceAuthorGraph(){}
    void addNode(PaperConferenceAuthorNode * temp){node.push_back(temp);}
    void addEdge(DirectedEdge * temp){edge.push_back(temp);}
    vector<PaperConferenceAuthorNode *> & getNode(){return node;}
    vector<DirectedEdge *> & getEdge(){return edge;}
    void initialize(){setEdgeNum();setNodeNum();setEveryNodeIn();setEveryNodeOut();every_node_sum.clear();
                     for(int i = 0; i < node_num; i++) {every_node_sum.push_back(every_node_in[i]+ every_node_out[i]);}}
    void setNodeNum(){node_num = node.size();}
    void setEdgeNum(){edge_num = edge.size();}
    int getRealId(int id);
    int findNode(int id);
    void readInNode(const char * file_name);
    void readInEdge(const char * file_name);
    void readSTD(ifstream & fin, char * buffer, PaperConferenceAuthorNode * & temp_base, int & id, int & k);
    ~PaperConferenceAuthorGraph(){}
    void deleteNode();
    void deleteEdge();
};

extern void readInNode(char * file_name, PaperConferenceAuthorGraph & temp_graph);
extern void readInEdge(char * file_name, PaperConferenceAuthorGraph & temp_graph);
#endif // PAPERCONFERENCEAUTHORGRAPH


