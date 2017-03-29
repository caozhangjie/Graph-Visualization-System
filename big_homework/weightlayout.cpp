#include "weightlayout.h"
#include <QTime>
#include <map>
#include <QDebug>
weightLayout::weightLayout(TopicGraph & temp):graph(temp)
{
    QTime my_time;
    my_time = QTime::currentTime();
    qsrand(my_time.msec() + my_time.second()*1000);
    episional = 0.1;
    mfactor = 15;
    node_num = graph.getNodeNum();
    epoch = 300;
    array.resize(node_num);
    state_visit.resize(node_num);
    for(int j = 0; j < node_num; j++)
    {
        array[j].setPoint(double(qrand() % 100) / 100, double(qrand() % 100) / 100);
        state_visit[j] = false;
    }
}

void weightLayout::calcLayout()
{
    for(int i = 0; i < epoch; i++)
    {
        calcPoint(i % 200);
        for(int j = 0; j < node_num; j++)
        {
            array[j].updateAxis();
            state_visit[j] = false;
        }
        episional *= 0.999;
    }
}

void weightLayout::getPoint(vector<vector<double> > & p)
{
    for(int i = 0; i < node_num; i++)
    {
        p[i].resize(3);
        p[i][0] = array[i].getXAxis() * 400;
        p[i][1] = array[i].getYAxis() * 400;
    }
}

void weightLayout::calcPoint(int id)
{
    vector<int> temp_pair;
    int num = graph.getInNum(id);
    for(int i = 0; i < num; i++)
    {
        if(state_visit[graph.getNodeIn()[id][i]])
            continue;
        temp_pair.push_back(id);
        temp_pair.push_back(graph.getNodeIn()[id][i]);

        array[graph.getNodeIn()[id][i]].addForce((array[id] - array[graph.getNodeIn()[id][i]]).normalLize() * ((myDistance(array[id], array[graph.getNodeIn()[id][i]])
                          - graph.getEdge()[graph.getNodeToEdge()[temp_pair]]->getWeight() * mfactor) * episional));
        temp_pair.clear();
    }
    state_visit[id] = true;
    for(int i = 0; i < num; i++)
    {
        if(!state_visit[graph.getNodeIn()[id][i]])
        {
            wid_search.push(graph.getNodeIn()[id][i]);
            index++;
            state_visit[graph.getNodeIn()[id][i]] = true;
        }
    }
    if(wid_search.size() <= 0)
        return;
    int temp = wid_search.front();
    wid_search.pop();
    calcPoint(temp);
}
