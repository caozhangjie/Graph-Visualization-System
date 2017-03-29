#include "filtertopicdialog.h"
#include "ui_filtertopicdialog.h"
#include <QString>

filterTopicDialog::filterTopicDialog(TopicGraph & temp, vector<bool> & temp1, QWidget *parent) :
    QDialog(parent),
    graph(temp),
    state(temp1),
    ui(new Ui::filterTopicDialog)
{
    ui->setupUi(this);
    node_num = temp.getNodeNum();
}

filterTopicDialog::~filterTopicDialog()
{
    delete ui;
}

void filterTopicDialog::on_pushButton_2_clicked()
{
    ui->id_c->clear();
    ui->paper_c->clear();
    ui->words_c->clear();
}

void filterTopicDialog::on_pushButton_clicked()
{
    QString & id = ui->id_c->toPlainText();
    QString & words = ui->words_c->toPlainText();
    QString & doc = ui->paper_c->toPlainText();
    vector<int> doc_id;
    vector<string> words_array;
    QString temp_str = "";
    int index = 0;
    for(int i = 0; i < node_num; i++)
    {
        state[i] = false;
    }
    while(1)
    {
        temp_str = doc.section(',', index, index);
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
    index = 0;
    while(1)
    {
        temp_str = words.section(',', index, index);
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
    if(id.length() > 0)
    {
        int num = id.toInt();
        for(int i = 0; i < node_num; i++)
        {
            if(graph.getNode()[i]->getIdOfNode() == num)
            {
                state[i] = true;
            }
        }
    }
    int id_number = doc_id.size();
    int words_number = words_array.size();
    int find_num = 0;
    if(id_number == 0 && words_number == 0 && id.length() == 0)
    {
        for(int i = 0; i < node_num; i++)
        {
            state[i] = true;
        }
        accept();
    }
    for(int i = 0; i < node_num; i++)
    {
        for(int k = 0; k < id_number; k++)
        {
            int temp_len1 = graph.getNode()[i]->getDoc().size();
            for(int j = 0; j < temp_len1; j++)
            {
                if(graph.getNode()[i]->getDoc()[j] == doc_id[k])
                {
                    state[i] = true;
                    break;
                }
            }
            if(state[i] == false)
            {
                break;
            }
        }
        if(state[i])
        {
            find_num ++;
        }
    }
    if(find_num == 0 && id_number > 0)
    {
        accept();
    }
    for(int i = 0; i < node_num; i++)
    {
        if(state[i] == false && id_number > 0)
        {
            continue;
        }
        for(int k = 0; k < words_number; k++)
        {
            int temp_len1 = graph.getNode()[i]->getWords().size();
            for(int j = 0; j < temp_len1; j++)
            {
                if(graph.getNode()[i]->getWords()[j] == words_array[k])
                {
                    state[i] = true;
                    break;
                }
            }
            if(state[i] == false)
            {
               break;
            }
        }
    }
    accept();
}
