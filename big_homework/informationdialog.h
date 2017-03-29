#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include "paperconferenceauthornode.h"
#include <QDialog>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(PaperConferenceAuthorNode & temp,QWidget *parent = 0);
    ~InformationDialog();
private slots:
    void on_save_clicked();

    void on_ok_clicked();

    void on_more_clicked();

private:
    Ui::InformationDialog *ui;
    int type;
    PaperConferenceAuthorNode & graph;
};

#endif // INFORMATIONDIALOG_H
