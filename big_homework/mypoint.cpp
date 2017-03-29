#include "mypoint.h"

myPoint operator/(double l, myPoint p2)
{
    return myPoint((l * p2.x) / (p2.len * p2.len), (l * p2.y) / (p2.len * p2.len));
}

double myDistance(myPoint p1, myPoint p2)
{
    return (p1 - p2).length();
}
