#ifndef POINTCOLOR
#define POINTCOLOR

#include <QColor>
#define PAPERCOLOR 0
#define CONFERENCECOLOR 1
#define AUTHORCOLOR 2
class PointColor
{
private:
    int r;
    int g;
    int b;
    int a;
public:
    void setColor(int level, int type, int alpha = 200);
    QColor getColor(){return QColor(r,g,b,a);}
};

#endif // POINTCOLOR

