#ifndef EDGE1
#define EDGE1

#include <map>
#include <iostream>
#include <vector>
using namespace std;

class Edge
{
private:
    int src_id;
    int tar_id;
public:
    int getSource(){return src_id;}
    int getTarget(){return tar_id;}
    void setSource(int src){src_id = src;}
    void setTarget(int tar){tar_id = tar;}
    virtual void abstract() = 0;
};



#endif // EDGE

