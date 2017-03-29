#include "pointcolor.h"

void PointColor::setColor(int level, int type, int alpha)
{
    switch(type)
    {
    case PAPERCOLOR:
        r = 255;
        g = 190 - level * 1.6;
        b = 190 - level * 1.6;
        a = alpha;
        break;
    case CONFERENCECOLOR:
        b = 255;
        g = 190 - level * 5;
        r = 190 - level * 5;
        a = alpha;
        break;
    case AUTHORCOLOR:
        g = 255;
        r = 190 - level * 5;
        b = 190 - level * 5;
        a = alpha;
        break;
    }
}
