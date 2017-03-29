#ifndef NOBEZIERDIALOG_H
#define NOBEZIERDIALOG_H

#include <QDialog>
#include "mypointedge.h"
#include <QMouseEvent>
#include <Qt>

namespace Ui {
class noBezierDialog;
}

class noBezierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit noBezierDialog(int size, vector<vector<double> >& point, vector<vector<int> > & temp_edge, QWidget *parent = 0);
    ~noBezierDialog();
    void calcXYZForPaint();
    void paintEvent(QPaintEvent * ev);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * ev);
    void wheelEvent(QWheelEvent * ev);
private:
    Ui::noBezierDialog *ui;
    vector<myPointEdge> edge_bundle;
    vector<double> Opoint;
    double temp_x;
    double temp_y;
    bool is_dragging;
    double my_scale;
};

#endif // NOBEZIERDIALOG_H
