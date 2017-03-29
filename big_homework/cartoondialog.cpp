#include "cartoondialog.h"
#include "ui_cartoondialog.h"
#include <QPainter>
#include <QPoint>
#include <QPen>
#include "mypoint.h"

cartoonDialog::cartoonDialog(TopicGraph & temp, QWidget *parent) :
    QDialog(parent),layout(temp),
    ui(new Ui::cartoonDialog)
{
    layout.episional = 0.01;
    ui->setupUi(this);
    index = 0;
    cartoon_timer.setInterval(50);
    connect(&cartoon_timer, SIGNAL(timeout()), this, SLOT(changePlace()));
    resize(1920, 1000);
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
    QTime my_time;
    my_time = QTime::currentTime();
    qsrand(my_time.msec() + my_time.second()*1000);
    cartoon_timer.start();
}

void cartoonDialog::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPen pen;
    //画边用的点
    QPointF point1;
    QPointF point2;
    painter.setBrush(QColor(255,210,210,255));
    painter.translate(960, 400);

        painter.setBrush(QColor(255,210,210,255));
        pen.setColor(QColor(250,150,150,0));
        painter.setPen(pen);
        for(int i = 0; i < layout.node_num; i++)
            painter.drawEllipse(65*(layout.array[i].getXAxis()) - 5, 65*(layout.array[i].getYAxis()) - 5, 10, 10);
        for(int j = 0; j < layout.graph.getEdgeNum(); j++)
        {
             pen.setColor(QColor(230,230,230,180));
             painter.setPen(pen);
             point1.setX(65*layout.array[layout.graph.getEdgeNode()[j][0]].getXAxis());
             point1.setY(65*layout.array[layout.graph.getEdgeNode()[j][0]].getYAxis());
             point2.setX(65*layout.array[layout.graph.getEdgeNode()[j][1]].getXAxis());
             point2.setY(65*layout.array[layout.graph.getEdgeNode()[j][1]].getYAxis());
             painter.drawLine(point1, point2);
        }

}


void cartoonDialog::changePlace()
{
    index++;
    layout.calcPoint(index % 200);
    for(int j = 0; j < layout.node_num; j++)
    {
        layout.array[j].updateAxis();
        layout.state_visit[j] = false;
    }
    update();
}

cartoonDialog::~cartoonDialog()
{
    cartoon_timer.stop();
    delete ui;
}
