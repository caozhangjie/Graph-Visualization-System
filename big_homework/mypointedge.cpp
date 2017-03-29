#include "mypointedge.h"

void myPointEdge::setAll(int i, double src_x, double src_y, double des_x, double des_y, int size)
{
    my_id = i;
    src.setPoint(src_x, src_y);
    des.setPoint(des_x, des_y);
    middle.setPoint((src_x + des_x) / 2, (src_y + des_y) / 2);
    cos_edge.resize(size);
    length_diff.resize(size);
    avg_edge.resize(size);
    dis_edge.resize(size);
    CV.resize(size);
    C_factor.resize(size);
    point_array.push_back(&src);
    point_array.push_back(&des);
    leng = myDistance(src, des);
    kp = K /leng;
}

void myPointEdge::calcDiff(int id, myPointEdge & edge)
{
    length_diff[id] = 2 / (max(leng, edge.leng) / avg_edge[id] + avg_edge[id] /min(leng, edge.leng));
}

void myPointEdge::calcCos(int id, myPointEdge & edge)
{
    cos_edge[id] = fabs((des - src) * (edge.des - edge.src) / (leng * edge.leng));
}

void myPointEdge::calcLvg(int id, myPointEdge & edge)
{
    avg_edge[id] = (leng + edge.leng) / 2;
}

void myPointEdge::calcDistance(int id, myPointEdge & edge)
{
    dis_edge[id] = avg_edge[id] / (avg_edge[id] + myDistance(middle, edge.middle) / 2);
}

void myPointEdge::calcCV(int id, myPointEdge & edge)
{
    CV[id] = min(max(1 - 2 * fabs(myDistance(middle, edge.middle) * ((edge.middle - middle) * (des - src) / (myDistance(middle, edge.middle) * leng))) / leng, 0),
                 max(1 - 2 * fabs(myDistance(middle, edge.middle) * ((edge.middle - middle) * (edge.des - edge.src) / (myDistance(middle, edge.middle) * edge.leng))) / edge.leng, 0));
}

void myPointEdge::calcAll(int id, myPointEdge & edge)
{
    calcLvg(id, edge);
    calcDiff(id, edge);
    calcCos(id, edge);
    calcCV(id, edge);
    calcDistance(id, edge);
    C_factor[id] = cos_edge[id] * length_diff[id] * dis_edge[id];
}

void myPointEdge::addNode()
{
    for(vector<myPoint *>::iterator iter = point_array.begin() + 1; iter != point_array.end(); iter++)
    {
        iter = point_array.insert(iter, new myPoint(((*(iter - 1))->x + (*iter)->x) / 2, ((*(iter - 1))->y + (*iter)->y) / 2));
        iter++;
    }
}

void myPointEdge::calcForceNeighbor()
{
    for(vector<myPoint *>::iterator iter = point_array.begin() + 1; iter != (point_array.end() - 1); iter++)
    {
        (*iter)->x_force = kp * (((*(*(iter - 1))) - (**iter)) + ((*(*(iter + 1))) - (**iter))).x;
        (*iter)->y_force = kp * (((*(*(iter - 1))) - (**iter)) + ((*(*(iter + 1))) - (**iter))).y;
    }
}

void myPointEdge::calcFactorToId(int id, myPointEdge & edge)
{
    int size = point_array.size();
    for(int i = 1; i < size - 1; i++)
    {
       if(((*edge.point_array[i]) - *point_array[i]).length() >= 0.1)
       {
        point_array[i]->x_force += (1 / ((*edge.point_array[i]) - *point_array[i])).x * cos_edge[id] * 1.4 * dis_edge[id] * 1.5;
        point_array[i]->y_force += (1 / ((*edge.point_array[i]) - *point_array[i])).y * cos_edge[id] * 1.4 * dis_edge[id] * 1.5;
       }
       else
       {
           point_array[i]->x_force += calcSign((*edge.point_array[i] - *point_array[i]).x) * 10 * cos_edge[id] * 1.1 * dis_edge[id] * 1.5;
           point_array[i]->y_force += calcSign((*edge.point_array[i] - *point_array[i]).y) * 10 * cos_edge[id] * 1.1 * dis_edge[id] * 1.5;
       }
    }
}

double myPointEdge::calcSign(double num)
{
    if(num > 0)
    {
        return 1;
    }
    else if(num < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void myPointEdge::updateXYZ()
{
    vector<myPoint *>::iterator iter = point_array.begin() + 1;
    for(; iter != point_array.end() - 1;iter++)
    {
        (*iter)->x += (*iter)->x_force * S;
        (*iter)->y += (*iter)->y_force * S;
    }
}

