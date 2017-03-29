#ifndef MYPOINTEDGE
#define MYPOINTEDGE
#include "mypoint.h"
#include <vector>
using namespace std;

extern double K; //全局恒力
extern double S; //该点
class myPointEdge
{
private:
    int my_id;
    myPoint middle;
    myPoint src;
    myPoint des;
    vector<myPoint *> point_array;
    vector<double> cos_edge;
    vector<double> length_diff;
    vector<double> avg_edge;
    vector<double> dis_edge;
    vector<double> CV;
    vector<double> C_factor;
    double kp;
    double leng;
public:
    myPointEdge(){}
    void setAll(int i, double src_x, double src_y, double des_x, double des_y, int size);
    void calcDiff(int id, myPointEdge & edge);
    void calcCos(int id, myPointEdge & edge);
    void calcLvg(int id, myPointEdge & edge);
    void calcDistance(int id, myPointEdge & edge);
    void calcCV(int id, myPointEdge & edge);
    void calcAll(int id, myPointEdge & edge);
    double getFactor(int id){return C_factor[id];}
    void addNode();
    void calcForceNeighbor();
    void calcFactorToId(int id, myPointEdge & edge);
    void updateXYZ();
    double max(double x, double y){if(x >= y) return x; else return y;}
    double min(double x, double y){if(x <= y) return x; else return y;}
    double getX(int i){return point_array[i]->x;}
    double getY(int i){return point_array[i]->y;}
    double calcSign(double num);
};

#endif // MYPOINTEDGE

