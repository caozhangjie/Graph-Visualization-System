#ifndef LINELINELAYOUT
#define LINELINELAYOUT
#include "paperconferenceauthorgraph.h"

class lineLineLayout
{
private:
    PaperConferenceAuthorGraph & graph;
    vector<vector<double> > point_xyz;
    int node_num;
public:
    lineLineLayout(PaperConferenceAuthorGraph
 & temp):graph(temp){node_num = graph.getNodeNum(); point_xyz.resize(node_num);}
    void getPoint(vector<vector<double> > & point){point = point_xyz;}
    void calcLayout();
};

#endif // LINELINELAYOUT

