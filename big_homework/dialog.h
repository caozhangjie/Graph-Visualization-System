#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mypointedge.h"
#include <QMouseEvent>
#include <Qt>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int size, vector<vector<double> >& point, vector<vector<int> > & temp_edge, QWidget *parent = 0);
    ~Dialog();
    void calcXYZForPaint();
    void paintEvent(QPaintEvent * ev);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * ev);
private:
    Ui::Dialog *ui;
    vector<myPointEdge> edge_bundle;
    vector<double> Opoint;
    double temp_x;
    double temp_y;
    bool is_dragging;
};

#endif // DIALOG_H
