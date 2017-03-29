#ifndef SEARCHRESULTDIALOG_H
#define SEARCHRESULTDIALOG_H

#include <QDialog>
#include "paperconferenceauthorgraph.h"
#include "topicgraph.h"

namespace Ui {
class searchResultDialog;
}

class searchResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchResultDialog(Graph & temp, vector<int> id, QWidget *parent = 0);
    ~searchResultDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::searchResultDialog *ui;
    Graph & graph;

};

#endif // SEARCHRESULTDIALOG_H
