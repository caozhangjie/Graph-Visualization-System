#ifndef UNDIRECTEDEDGE
#define UNDIRECTEDEDGE

#include "edge.h"

class UndirectedEdge: public Edge
{
private:
    double weight;
public:
    void abstract(){}
    UndirectedEdge(){}
    double getWeight(){return weight;}
    void setWeight(double temp_weight){weight = temp_weight;}
};

#endif // UNDIRECTEDEDGE

