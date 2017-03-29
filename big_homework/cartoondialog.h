#ifndef CARTOONDIALOG_H
#define CARTOONDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include "weightlayout.h"
#include "topicgraph.h"

namespace Ui {
class cartoonDialog;
}

class cartoonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cartoonDialog(TopicGraph & temp, QWidget *parent = 0);
    ~cartoonDialog();
    void paintEvent(QPaintEvent *ev);

private slots:
    void changePlace();
private:
    Ui::cartoonDialog *ui;
    QTimer cartoon_timer;
    weightLayout layout;
    int index;
};

#endif // CARTOONDIALOG_H
