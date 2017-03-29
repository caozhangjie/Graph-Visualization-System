#include "topicdialog.h"
#include "ui_topicdialog.h"
#include <QString>
#include <string>
#include <QMessageBox>
using namespace std;
topicdialog::topicdialog(TopicGraph & temp_topic, TopicNode & temp,QWidget *parent) :
    QDialog(parent),topic(temp_topic),
    ui(new Ui::topicdialog),
    graph(temp)
{
    ui->setupUi(this);
    words_num = temp.getWords().size();
    number_num = temp.getDoc().size();
    QString temp_str = "";
    for(int i = 0; i < words_num - 1; i++)
    {
        temp_str = temp_str + temp.getWords()[i].c_str() + ",    ";
    }
    temp_str = temp_str + temp.getWords()[words_num - 1].c_str();
    ui->words_text->setPlainText(temp_str);
    temp_str = "";
    for(int j = 0; j < number_num - 1; j++)
    {
        temp_str = temp_str + QString::number(temp.getDoc()[j], 10) + ",    ";
    }
    temp_str = temp_str + QString::number(temp.getDoc()[number_num - 1], 10);
    ui->number_text->setPlainText(temp_str);
    p = 0;
}

topicdialog::~topicdialog()
{
    delete ui;
}

void topicdialog::on_exit_b_clicked()
{
    accept();
}

void topicdialog::on_save_words_clicked()
{
    QString temp_str = "";
    QString & words = ui->words_text->toPlainText();
    vector<string> words_array;
    int index = 0;
    while(1)
    {
        temp_str = words.section(",    ", index, index);
        if(temp_str.length() <= 0)
        {
             break;
        }
        else
        {
            words_array.push_back(temp_str.toStdString());
        }
        index ++;
    }
    graph.getWords() = words_array;
    QMessageBox::information(0, "succeed", "The modification is saved.", QMessageBox::Ok);
}

void topicdialog::on_save_number_clicked()
{
    QString temp_str = "";
    QString & doc = ui->number_text->toPlainText();
    vector<int> doc_id;
    int index = 0;
    while(1)
    {
        temp_str = doc.section(",    ", index, index);
        if(temp_str.length() <= 0)
        {
             break;
        }
        else
        {
            doc_id.push_back(temp_str.toInt());
        }
        index ++;
    }
    graph.getDoc() = doc_id;
    QMessageBox::information(0, "succeed", "The modification is saved.", QMessageBox::Ok);
}

void topicdialog::on_ok_b_clicked()
{
    QString temp_str = ui->select_number->text();
    if(temp_str.length() <= 0)
    {
        return;
    }
    else
    {
        int number = temp_str.toInt();
        int id = topic.getDoc(number);
        if(id == -1)
        {
            QMessageBox::warning(this, "warning", "No such document.", QMessageBox::Cancel, QMessageBox::NoButton);
            return;
        }
        else
        {
            docDialog dlg(topic.getDocNode(id));
            dlg.exec();
        }
    }
}
