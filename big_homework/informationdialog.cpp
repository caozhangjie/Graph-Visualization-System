#include "informationdialog.h"
#include "ui_informationdialog.h"
#include "moreforpaperdialog.h"
#include <QString>
#include <string>
#include <QMessageBox>
using namespace std;

InformationDialog::InformationDialog(PaperConferenceAuthorNode & temp,QWidget *parent) :
    graph(temp),
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    type = temp.getType();
    switch(type)
    {
    case PaperConferenceAuthorNode::PAPER:
        ui->title_label->setText("title");
        ui->title_short_label->setText("title short");
        ui->year_content->setText(QString::number(temp.getYear(), 10));
        ui->id_content->setText(temp.getId().c_str());
        ui->title_content->setPlainText(temp.getName().c_str());
        ui->title_short_content->setText(temp.getNameShort().c_str());
        ui->type_content->setText("paper");
        ui->view_label_content->setText(temp.getViewLabel().c_str());
        break;
    case PaperConferenceAuthorNode::CONFERENCE:
        ui->title_label->setText("name");
        ui->title_short_label->setText("name short");
        ui->year_content->setText(QString::number(temp.getYear(), 10));
        ui->id_content->setText(temp.getId().c_str());
        ui->title_content->setPlainText(temp.getName().c_str());
        ui->title_short_content->setText(temp.getNameShort().c_str());
        ui->type_content->setText("conference");
        ui->view_label_content->setText(temp.getViewLabel().c_str());
        break;
     case PaperConferenceAuthorNode::AUTHOR:
        ui->title_label->setText("name");
        ui->title_short_label->setText("name short");
        ui->year_content->setText(QString::number(temp.getYear(), 10));
        ui->id_content->setText(temp.getId().c_str());
        ui->title_content->setPlainText(temp.getName().c_str());
        ui->title_short_content->setText(temp.getNameShort().c_str());
        ui->type_content->setText("author");
        ui->view_label_content->setText(temp.getViewLabel().c_str());
        break;
    }
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

void InformationDialog::on_save_clicked()
{
    switch(type)
    {
    case PaperConferenceAuthorNode::PAPER:
        graph.setYear(ui->year_content->text().toInt());
        graph.setId(ui->id_content->text().toStdString());
        graph.setName(ui->title_content->toPlainText().toStdString());
        graph.setNameShort(ui->title_short_content->text().toStdString());
        graph.setViewLabel(ui->view_label_content->text().toStdString());
        break;
    case PaperConferenceAuthorNode::CONFERENCE:
        graph.setYear(ui->year_content->text().toInt());
        graph.setId(ui->id_content->text().toStdString());
        graph.setName(ui->title_content->toPlainText().toStdString());
        graph.setNameShort(ui->title_short_content->text().toStdString());
        graph.setViewLabel(ui->view_label_content->text().toStdString());
        break;
     case PaperConferenceAuthorNode::AUTHOR:
        graph.setYear(ui->year_content->text().toInt());
        graph.setId(ui->id_content->text().toStdString());
        graph.setName(ui->title_content->toPlainText().toStdString());
        graph.setNameShort(ui->title_short_content->text().toStdString());
        graph.setViewLabel(ui->view_label_content->text().toStdString());
        break;
    }
    QMessageBox::information(0, "succeed", "The modification is saved.", QMessageBox::Ok);
}

void InformationDialog::on_ok_clicked()
{
    accept();
}

void InformationDialog::on_more_clicked()
{
    if(type == PaperConferenceAuthorNode::PAPER)
    {
        moreforpaperdialog dlg(graph, parentWidget());
        dlg.exec();
    }
    else
    {
        return;
    }
}
