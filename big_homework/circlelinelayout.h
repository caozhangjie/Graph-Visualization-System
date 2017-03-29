#ifndef CIRCLELINELAYOUT
#define CIRCLELINELAYOUT

#include "paperconferenceauthorgraph.h"

class circleLineLayout
{
private:
    PaperConferenceAuthorGraph & graph;
    vector<vector<double> > point_xyz;
    int node_num;
public:
    circleLineLayout(PaperConferenceAuthorGraph
 & temp):graph(temp){node_num = graph.getNodeNum(); point_xyz.resize(node_num);}
    void getPoint(vector<vector<double> > & point){point = point_xyz;}
    void calcLayout();
};

#endif // CIRCLELINELAYOUT

