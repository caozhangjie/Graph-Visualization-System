#ifndef DOCDIALOG_H
#define DOCDIALOG_H

#include <QDialog>
#include <docnode.h>

namespace Ui {
class docDialog;
}

class docDialog : public QDialog
{
    Q_OBJECT

public:
    explicit docDialog(DocNode & temp, QWidget *parent = 0);
    ~docDialog();

private slots:
    void on_save_clicked();

    void on_exit_clicked();

private:
    Ui::docDialog *ui;
    DocNode & node;
};

#endif // DOCDIALOG_H
