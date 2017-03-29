#ifndef WEIGHTLAYOUT
#define WEIGHTLAYOUT

#include "topicgraph.h"
#include "mypoint.h"
#include <queue>
class cartoonDialog;

class weightLayout
{
private:
    int index;
    TopicGraph & graph;
    int node_num;
    queue<int> wid_search;
    vector<bool> state_visit;
    vector<myPoint> array;
    double episional;
    double mfactor;
    int epoch;
    friend class cartoonDialog;
private:
    void calcPoint(int id);
public:
    weightLayout(TopicGraph & temp);
    void getPoint(vector<vector<double> > & point);
    void calcLayout();
    void setEpoch(int n){epoch = n;}
    void setEpisional(double x){episional = x;}
    void setFactor(int f){mfactor = f;}
};

#endif // WEIGHTLAYOUT

