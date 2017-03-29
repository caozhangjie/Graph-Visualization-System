#include "docdialog.h"
#include "ui_docdialog.h"
#include <QString>
#include <QMessageBox>
docDialog::docDialog(DocNode & temp, QWidget *parent) :
    QDialog(parent), node(temp),
    ui(new Ui::docDialog)
{
    ui->setupUi(this);
    ui->number->setText(QString::number(temp.getIdOfNode(), 10));
    ui->doc->setText(QString(temp.getTitle().c_str()) + "\n" + QString(temp.getContent().c_str()));
}

docDialog::~docDialog()
{
    delete ui;
}

void docDialog::on_save_clicked()
{
    QString temp_str = ui->doc->toPlainText();
    node.getTitle() = temp_str.section('\n', 0, 0).toStdString();
    node.getContent() = temp_str.section('\n', 1, 1).toStdString();
    QMessageBox::information(0, "succeed", "The modification is saved.", QMessageBox::Ok);
}

void docDialog::on_exit_clicked()
{
    accept();
}
