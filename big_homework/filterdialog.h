#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "paperconferenceauthorgraph.h"

namespace Ui {
class filterDialog;
}

class filterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit filterDialog(PaperConferenceAuthorGraph
 & temp, vector<bool> & temp_state, QWidget *parent = 0);
    ~filterDialog();

private:
    void compareForMore(PaperConferenceAuthorGraph
 & temp, vector<bool> & st, QString & pag, QString & yea, string & autho);

private slots:
    void on_ok_b_clicked();

    void on_clear_b_clicked();

private:
    Ui::filterDialog *ui;
    PaperConferenceAuthorGraph
 & graph;
    vector<bool> & state;
    int node_num;
};

#endif // FILTERDIALOG_H
