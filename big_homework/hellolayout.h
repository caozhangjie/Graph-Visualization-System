#ifndef HELLOLAYOUT
#define HELLOLAYOUT

#include "paperconferenceauthorgraph.h"

class helloLayout
{
private:
    vector<vector<double> > point_xyz;
    int node_num;
public:
    helloLayout(int num){node_num = num; point_xyz.resize(node_num);}
    void getPoint(vector<vector<double> > & point){point = point_xyz;}
    void calcLayout();
    void drawVLine(int x, int y, int distance, int base_index, int & index);
    void drawHLine(int x, int y, int distance, int base_index, int & index);

};

#endif // HELLOLAYOUT

