#include "linelinelayout.h"
#include <set>
#include <cmath>
#include <map>

void lineLineLayout::calcLayout()
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
    int size_ac = paper_have_ac.size();    //存储与conference和author的paper节点数量
    int size_not_ac = paper_not_ac.size(); //存储不与conference和author的paper节点数量
    int size_au_co = ac.size();            //存储conference和author节点数量
    double not_pi = pi / size_not_ac;
    double auco_pi = pi / size_au_co;
    set<int>::iterator iter;
    int i;
    for(i = 0, iter = paper_have_ac.begin(); iter != paper_have_ac.end(); iter++, i++)
    {
        point_xyz[*iter].resize(3);
        point_xyz[*iter][0] = 200 * sin(2 * pi / size_ac * (i - size_ac / 2));
        point_xyz[*iter][1] = 11 * (i - size_ac / 2);
    }
    for(i = 0, iter = paper_not_ac.begin(); iter != paper_not_ac.end(); iter++, i++)
    {
        point_xyz[*iter].resize(3);
        point_xyz[*iter][0] = 500 + 400 * cos((i - size_not_ac / 2) * not_pi);
        point_xyz[*iter][1] = 400 * sin((i - size_not_ac / 2) * not_pi);
    }
    for(i = 0, iter = ac.begin(); iter != ac.end(); iter++, i++)
    {
        point_xyz[*iter].resize(3);
        point_xyz[*iter][0] = - 500 - 400 * cos((i - size_au_co / 2) * auco_pi);
        point_xyz[*iter][1] = -400 * sin((i - size_au_co / 2) * auco_pi);
    }
}

