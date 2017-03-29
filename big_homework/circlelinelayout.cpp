#include "circlelinelayout.h"
#include <set>
#include <cmath>
#include <map>

void circleLineLayout::calcLayout()
{
    const double pi = acos(-1);
    set<int> paper_have_ac;
    set<int> paper_not_ac;
    set<int> ac;
    for(int i = 0; i < node_num; i++)
    {
        if(graph.getNode()[i]->getType() == PaperConferenceAuthorNode::CONFERENCE ||
                graph.getNode()[i]->getType() == PaperConferenceAuthorNode::AUTHOR)
        {
            ac.insert(i);
            for(int j = 0; j < graph.getNodeOut()[i].size(); j++)
            {
                paper_have_ac.insert(graph.getNodeOut()[i][j]);
            }
        }
    }
    for(int i = 0; i < node_num; i++)
    {
        if(graph.getNode()[i]->getType() == PaperConferenceAuthorNode::PAPER)
        {
            if(paper_have_ac.find(i) == paper_have_ac.end())
            {
                paper_not_ac.insert(i);
            }
        }
    }
    int size_ac = paper_have_ac.size();
    int size_not_ac = paper_not_ac.size();
    int size_au_co = ac.size();
    double theta_ac = 2 * pi / size_ac;
    double theta_not = 2 * pi / size_not_ac;
    map<int, double> angle_ac;
    set<int>::iterator iter;
    int i;
    for(i = 0, iter = paper_have_ac.begin(); iter != paper_have_ac.end(); iter++, i++)
    {
        angle_ac.insert(map<int, double>::value_type(*iter, theta_ac * i));
        point_xyz[*iter].resize(3);
        point_xyz[*iter][0] = cos(theta_ac * i) * 2.5 * 200;
        point_xyz[*iter][1] = sin(theta_ac * i) * 2.5 * 100;
    }
    for(i = 0, iter = paper_not_ac.begin(); iter != paper_not_ac.end(); iter++, i++)
    {
        point_xyz[*iter].resize(3);
        point_xyz[*iter][0] = cos(theta_not * i) * 1.5 * 200;
        point_xyz[*iter][1] = sin(theta_not * i) * 1.5 * 100;
    }
    double angle = 0;
    int index;
    int number;
    for(iter = ac.begin(); iter != ac.end(); iter++)
    {
        index = *iter;
        number = graph.getNodeOut()[index].size();
        for(int j = 0; j < number; j++)
        {
            angle += angle_ac[graph.getNodeOut()[index][j]];
        }
        angle /= number;
        point_xyz[index].resize(3);
        point_xyz[index][0] = cos(angle) * 4 * 200;
        point_xyz[index][1] = sin(angle) * 4 * 100;
    }
}
