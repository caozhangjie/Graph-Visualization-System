#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QPainterPath>
#include <QColor>

double K = 0.05;
double S = 0.8;

Dialog::Dialog(int size, vector<vector<double> >& point, vector<vector<int> > & temp_edge,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Opoint.resize(2);
    Opoint[0] = 0;
    Opoint[1] = 0;
    resize(1920, 1000);
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
    edge_bundle.resize(size);
    for(int i = 0; i < size; i++)
    {
        edge_bundle[i].setAll(i, point[temp_edge[i][0]][0], point[temp_edge[i][0]][1], point[temp_edge[i][1]][0], point[temp_edge[i][1]][1], size);
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(j == i)
                continue;
            else
            {
                edge_bundle[i].calcAll(j, edge_bundle[j]);
            }
        }
    }
    is_dragging = false;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::calcXYZForPaint()
{
    int cycle = 1;
    int iter = 300;
    int size = edge_bundle.size();
    for(int i = 0; i < cycle; i++)
    {
        for(int k = 0; k < size; k++)
        {
            edge_bundle[k].addNode();
        }
        for(int j = 0; j < iter; j++)
        {
            for(int l = 0; l < size; l++)
            {
                edge_bundle[l].calcForceNeighbor();
                for(int p = 0; p < size; p++)
                {
                    if(p == l)
                        continue;

                    edge_bundle[l].calcFactorToId(p, edge_bundle[p]);
                }
            }
            for(int l = 0; l < size; l++)
                edge_bundle[l].updateXYZ();
        }
        S /= 1.5;
        iter *= 0.6;
    }
}

void Dialog::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        temp_x = ev->pos().x();
        temp_y = ev->pos().y();
        is_dragging = true;
    }
}

void Dialog::mouseMoveEvent(QMouseEvent * ev)
{
    if(is_dragging)
    {
        Opoint[0] += ev->pos().x() - temp_x;
        Opoint[1] += ev->pos().y() - temp_y;
        temp_x = ev->pos().x();
        temp_y = ev->pos().y();
        update();
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent * ev)
{
    if(is_dragging)
    {
        is_dragging = false;
    }
}


void Dialog::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    QPen pen;
    QPainterPath path;
    //画边用的点
    QPointF point1;
    QPointF point2;
    QPointF middle;
    QPointF temp;
    QPointF start;
    QPointF end;
    painter.setBrush(QColor(255,210,210,255));
    int size = edge_bundle.size();
    painter.translate(Opoint[0] + 960, Opoint[1] + 500);
    for(int i = 0; i < size; i++)
    {
        painter.setBrush(QColor(255,210,210,255));
        pen.setColor(QColor(250,150,150,0));
        painter.setPen(pen);
        painter.drawEllipse(edge_bundle[i].getX(0) - 5, edge_bundle[i].getY(0) - 5, 10, 10);
        painter.drawEllipse(edge_bundle[i].getX(2) - 5, edge_bundle[i].getY(2) - 5, 10, 10);
        painter.setBrush(QColor(0,0,0,0));
        start.setX(edge_bundle[i].getX(0));
        start.setY(edge_bundle[i].getY(0));
        end.setX(edge_bundle[i].getX(2));
        end.setY(edge_bundle[i].getY(2));
        point1.setX((edge_bundle[i].getX(0) + edge_bundle[i].getX(1)) / 2);
        point1.setY((edge_bundle[i].getY(0) + edge_bundle[i].getY(1)) / 2);
        point2.setX((edge_bundle[i].getX(1) + edge_bundle[i].getX(2)) / 2);
        point2.setY((edge_bundle[i].getY(1) + edge_bundle[i].getY(2)) / 2);
        middle = (point1 + point2) / 2;
        temp.setX(edge_bundle[i].getX(1));
        temp.setY(edge_bundle[i].getY(1));
        point1 += (temp - middle);
        point2 += (temp - middle);
        path.moveTo(start);
        path.cubicTo(point1, point1, temp);
        path.cubicTo(point2, point2, end);
        painter.setPen(QColor(255, 255, 255, 190));
        painter.drawPath(path);
    }
}
