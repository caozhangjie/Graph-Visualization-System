#ifndef FILTERTOPICDIALOG_H
#define FILTERTOPICDIALOG_H

#include <QDialog>
#include "topicgraph.h"
namespace Ui {
class filterTopicDialog;
}

class filterTopicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit filterTopicDialog(TopicGraph & temp, vector<bool> &, QWidget *parent = 0);
    ~filterTopicDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::filterTopicDialog *ui;
    TopicGraph & graph;
    int node_num;
    vector<bool> & state;
};

#endif // FILTERTOPICDIALOG_H
