#include "searchresultdialog.h"
#include "ui_searchresultdialog.h"

searchResultDialog::searchResultDialog(Graph & temp, vector<int> id, QWidget *parent) :
    QDialog(parent),graph(temp),
    ui(new Ui::searchResultDialog)
{
    ui->setupUi(this);
    QString str = "";
    for(vector<int>::iterator iter = id.begin(); iter != id.end(); iter ++)
    {
        str = str + QString::number(graph.getRealId(*iter)) + "   ";
    }
    if(str.length() > 0)
    {
        ui->textEdit->setPlainText(str);
    }
    else
    {
        ui->textEdit->setPlainText("No result is found.");
    }
}

searchResultDialog::~searchResultDialog()
{
    delete ui;
}

void searchResultDialog::on_pushButton_clicked()
{
    accept();
}
