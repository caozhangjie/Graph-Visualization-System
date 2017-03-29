#ifndef NODE
#define NODE

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node
{
private:
    int id_of_node;
public:
    void setIdOfNode(int temp){id_of_node = temp;}
    int getIdOfNode(){return id_of_node;}
protected:
    virtual void abstract() = 0;
};

#endif // NODE

