#ifndef MYPOINT
#define MYPOINT
#include <cmath>
#include <qDebug>
using namespace std;

class myPointEdge;

class myPoint
{
private:
    double x;
    double y;
    double len;
    double x_force;
    double y_force;
    friend class myPointEdge;
public:
    double getXAxis(){return x;}
    double getYAxis(){return y;}
    myPoint(double tx = 0, double ty = 0){setPoint(tx, ty); x_force = 0; y_force = 0;}
    void setPoint(double tx = 0, double ty = 0){x = tx; y = ty; len = sqrt(x * x + y * y);}
    friend double myDistance(myPoint p1, myPoint p2);
    double length(){return len;}
    myPoint operator-(myPoint & p2){return myPoint(x - p2.x, y - p2.y);}
    myPoint operator+(myPoint & p2){return myPoint(x + p2.x, y + p2.y);}
    void addForce(myPoint & p){x_force += p.x; y_force += p.y;}
    friend myPoint operator /(double l, myPoint p2);
    myPoint operator /(double l){return myPoint(x / l, y / l);}
    double operator *(myPoint & p2){return (y * p2.y) + (x * p2.x);}
    myPoint operator *(double t){return myPoint(x * t, y * t);}
    void updateAxis(){x += x_force; y += y_force; x_force = 0; y_force = 0; len = sqrt(x * x + y * y);}
    myPoint normalLize(){if((x * x + y * y) > 0) return myPoint(x / len, y / len); else return myPoint(0, 0);}
};

#endif // MYPOINT

