#include "forcelayout.h"
#include <QTime>
forceLayout::forceLayout(TopicGraph & temp, int num):graph(temp), node_num(num)
{
    factor = 0.075;
    iter = 100;
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int i = 0; i < node_num; i++)
        array.push_back(myPoint(qrand() % 1000 - 500, qrand() % 1000 - 500));
}

void forceLayout::calcOnce()
{
    for(int i = 0; i < node_num; i++)
    {
        for(int j = 0; j < node_num; j++)
        {
            if(i == j)
                continue;
            else
            {
                if(myDistance(array[i], array[j]) > 100)
                    ;
                else
                    array[i].addForce(myPoint(0.003, 0.003) * (100 - myDistance(array[i], array[j])));
            }
        }
    }
    int edge_num = graph.getEdgeNum();
    for(int i = 0; i < edge_num; i++)
    {
        array[graph.getEdgeNode()[i][1]].addForce((array[graph.getEdgeNode()[i][0]] - array[graph.getEdgeNode()[i][1]]) * graph.getEdge()[i]->getWeight() * factor);
        array[graph.getEdgeNode()[i][0]].addForce((array[graph.getEdgeNode()[i][1]] - array[graph.getEdgeNode()[i][0]]) * graph.getEdge()[i]->getWeight() * factor);
    }
    for(int i = 0; i < node_num; i++)
    {
        array[i].updateAxis();
    }
}

void forceLayout::getPoint(vector<vector<double> > & p)
{
    for(int i = 0; i < node_num; i++)
    {
        p[i].resize(3);
        p[i][0] = array[i].getXAxis() * 1.5;
        p[i][1] = array[i].getYAxis() * 1.5;
    }
}

void forceLayout::calcLayout()
{
    for(int i = 0; i < iter; i++)
    {
        calcOnce();
    }
}
