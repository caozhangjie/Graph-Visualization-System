#include "hellolayout.h"
#include "cmath"
using namespace std;
void helloLayout::calcLayout()
{
    int index = 0;
    drawVLine(260 - 990, 310 - 500, 20, 20, index);
    drawVLine(480 - 990, 310 - 500, 20, 40, index);
    drawHLine(280 - 990, 500 - 500, 20, 50, index);
    drawVLine(560 - 990, 310 - 500, 20, 70, index);
    drawHLine(580 - 990, 310 - 500, 20, 80, index);
    drawHLine(580 - 990, 500 - 500, 20, 90, index);
    drawHLine(580 - 990, 690 - 500, 20, 100, index);
    drawVLine(830 - 990, 310 - 500, 20, 120, index);
    drawHLine(850 - 990, 690 - 500, 20, 130, index);
    drawVLine(1100 - 990, 310 - 500, 20, 150, index);
    drawHLine(1120 - 990, 690 - 500, 20, 160, index);
    double pi = acos(-1);
    pi /= 20;
    for(int i = 0; i < 40; i++)
    {
        point_xyz[index].resize(3);
        point_xyz[index][0] = cos(pi * i) * 160 + 1490 - 990;
        point_xyz[index][1] = sin(pi * i) * 160;
        index++;
    }
}

void helloLayout::drawHLine(int x, int y, int distance, int base_index, int & index)
{
    int start_index = index;
    while(index < base_index)
    {
        point_xyz[index].resize(3);
        point_xyz[index][0] = x + distance * (index - start_index);
        point_xyz[index][1] = y;
        index++;
    }
}

void helloLayout::drawVLine(int x, int y, int distance, int base_index, int & index)
{
    int start_index = index;
    while(index < base_index)
    {
        point_xyz[index].resize(3);
        point_xyz[index][0] = x;
        point_xyz[index][1] = y + distance * (index - start_index);
        index++;
    }
}
