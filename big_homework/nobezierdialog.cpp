#include "nobezierdialog.h"
#include "ui_nobezierdialog.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QPainterPath>
#include <QColor>

noBezierDialog::~noBezierDialog()
{
    delete ui;
}


noBezierDialog::noBezierDialog(int size, vector<vector<double> >& point, vector<vector<int> > & temp_edge,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::noBezierDialog)
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
    my_scale = 1;
}

void noBezierDialog::calcXYZForPaint()
{
    int cycle = 5;
    int iter = 200;
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
        S /= 1.1;
        iter *= 0.7;
    }
}

void noBezierDialog::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        temp_x = ev->pos().x();
        temp_y = ev->pos().y();
        is_dragging = true;
    }
}

void noBezierDialog::mouseMoveEvent(QMouseEvent * ev)
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

void noBezierDialog::mouseReleaseEvent(QMouseEvent * ev)
{
    if(is_dragging)
    {
        is_dragging = false;
    }
}

void noBezierDialog::wheelEvent(QWheelEvent * ev)
{
    if(ev->delta() > 0)
    {
        my_scale *= 1.1;
        Opoint[0] += 0.1 * (Opoint[0] + 1920 / 2 - QPoint(cursor().pos()).x());
        Opoint[1] += 0.1 * (Opoint[1] + 1000 / 2 - QPoint(cursor().pos()).y());
        update();
    }
    else
    {
        my_scale *= 0.9;
        Opoint[0] -= 0.1 * (Opoint[0] + 1920 / 2 - QPoint(cursor().pos()).x());
        Opoint[1] -= 0.1 * (Opoint[1] + 1000 / 2 - QPoint(cursor().pos()).y());
        update();
    }
}

void noBezierDialog::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    QPen pen;
    //画边用的点
    QPointF point1;
    QPointF point2;
    painter.setBrush(QColor(255,210,210,255));
    int size = edge_bundle.size();
    painter.translate(Opoint[0] + 960, Opoint[1] + 500);
    for(int i = 0; i < size; i++)
    {
        painter.setBrush(QColor(255,210,210,255));
        pen.setColor(QColor(250,150,150,0));
        painter.setPen(pen);
        painter.drawEllipse(my_scale * (edge_bundle[i].getX(0) - 5), my_scale * (edge_bundle[i].getY(0) - 5), my_scale * 10,my_scale * 10);
        painter.drawEllipse(my_scale * (edge_bundle[i].getX(32) - 5), my_scale * (edge_bundle[i].getY(32) - 5), my_scale * 10, my_scale * 10);
        for(int j = 0; j < 32; j++)
        {
             pen.setColor(QColor(230,230,230,180));
             painter.setPen(pen);
             point1.setX(my_scale * edge_bundle[i].getX(j));
             point1.setY(my_scale * edge_bundle[i].getY(j));
             point2.setX(my_scale * edge_bundle[i].getX(j+1));
             point2.setY(my_scale * edge_bundle[i].getY(j+1));
             painter.drawLine(point1, point2);
        }
    }
}
