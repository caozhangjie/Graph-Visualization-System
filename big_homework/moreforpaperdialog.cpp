#include "moreforpaperdialog.h"
#include "ui_moreforpaperdialog.h"
#include <QMessageBox>
#include <QString>
moreforpaperdialog::moreforpaperdialog(PaperConferenceAuthorNode & temp , QWidget *parent) :
    QDialog(parent),graph(temp),
    ui(new Ui::moreforpaperdialog)
{
    ui->setupUi(this);
    int index = 0;
    QString temp_str(graph.getExtra().c_str());
    QString son_str = temp_str.section("\\n", index, index);
    QString result_str;
    while(son_str.length() > 0)
    {
        result_str = result_str + son_str + "\n";
        index ++;
        son_str = temp_str.section("\\n", index, index);
    }
    ui->author->setPlainText(result_str);
    ui->page->setText(QString::number(temp.getPageFrom(), 10));
    ui->year->setText(QString::number(temp.getDateFrom(), 10));
}

moreforpaperdialog::~moreforpaperdialog()
{
    delete ui;
}

void moreforpaperdialog::on_pushButton_clicked()
{
    graph.setDateFrom(ui->year->text().toInt());
    graph.setPageFrom(ui->page->text().toInt());
    int index = 0;
    QString temp_str(ui->author->toPlainText());
    QString son_str = temp_str.section('\n', index, index);
    QString result_str;
    while(son_str.length() > 0)
    {
        result_str = result_str + son_str + "\\n";
        index ++;
        son_str = temp_str.section('\n', index, index);
    }
    graph.setExtra(result_str.toStdString());
    QMessageBox::information(0, "succeed", "The modification is saved.", QMessageBox::Ok);
}

void moreforpaperdialog::on_pushButton_2_clicked()
{
    accept();
}
