#ifndef FORCELAYOUT
#define FORCELAYOUT

#include "topicgraph.h"
#include "mypoint.h"


class forceLayout
{
private:
    vector<myPoint> array;
    int node_num;
    int iter;
    TopicGraph & graph;
    double factor;
private:
    void calcOnce();
public:
    forceLayout(TopicGraph & temp, int num = 0);

    void getPoint(vector<vector<double> > & p);
    void calcLayout();
};

#endif // FORCELAYOUT

