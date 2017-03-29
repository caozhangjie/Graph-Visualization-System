#ifndef MOREFORPAPERDIALOG_H
#define MOREFORPAPERDIALOG_H

#include <QDialog>
#include "paperconferenceauthornode.h"

namespace Ui {
class moreforpaperdialog;
}

class moreforpaperdialog : public QDialog
{
    Q_OBJECT

public:
    explicit moreforpaperdialog(PaperConferenceAuthorNode & temp , QWidget *parent = 0);
    ~moreforpaperdialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::moreforpaperdialog *ui;
    PaperConferenceAuthorNode & graph;
};

#endif // MOREFORPAPERDIALOG_H
