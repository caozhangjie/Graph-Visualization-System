#include "filterdialog.h"
#include "ui_filterdialog.h"

filterDialog::filterDialog(PaperConferenceAuthorGraph
 & temp, vector<bool> & temp_state, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filterDialog),
    graph(temp),
    state(temp_state)
{
    ui->setupUi(this);
    node_num = graph.getNodeNum();
}

filterDialog::~filterDialog()
{
    delete ui;
}

void filterDialog::on_ok_b_clicked()
{
    //设置状态
    string & all = ui->all_c->text().toStdString();
    string & shor = ui->short_c->text().toStdString();
    QString & page = ui->page_c->text();
    QString & type = ui->type_c->text();
    QString & id_number = ui->id_number_c->text();
    string & id = ui->id_c->text().toStdString();
    string & author = ui->author_c->text().toStdString();
    QString & year = ui->year_c->text();
    QString & year_f = ui->year_f_c->text();
    string & view_label = ui->view_label_c->text().toStdString();
    for(int i = 0; i < node_num; i++)
    {
        state[i] = true;
    }
    if(id_number.length() > 0)
    {
        int num = id_number.toInt();
        for(int i = 0; i < node_num; i++)
        {
            if(!(graph.getNode()[i]->getIdOfNode() == num))
            {
                state[i] = false;
            }
        }
    }
    if(all.length() > 0)
    {
        int len = all.length();
        for(int i = 0; i < node_num; i++)
        {
            if(len > graph.getNode()[i]->getName().length())
            {
                state[i] = false;
                continue;
            }
            if(!(graph.getNode()[i]->getName().substr(0, len) == all))
            {
                state[i] = false;
            }
        }
    }
    if(id.length() > 0)
    {
        int len = id.length();
        for(int i = 0; i < node_num; i++)
        {
            if(len > graph.getNode()[i]->getId().length())
            {
                state[i] = false;
                continue;
            }
            if(!(graph.getNode()[i]->getId().substr(0, len) == id))
            {
                state[i] = false;
            }
        }
    }
    if(shor.length() > 0)
    {
        int len = shor.length();
        for(int i = 0; i < node_num; i++)
        {
            if(len > graph.getNode()[i]->getNameShort().length())
            {
                state[i] = false;
                continue;
            }
            if(!(graph.getNode()[i]->getNameShort().substr(0, len) == shor))
            {
                state[i] = false;
            }
        }
    }
    if(view_label.length() > 0)
    {
        int len = view_label.length();
        for(int i = 0; i < node_num; i++)
        {
            if(len > graph.getNode()[i]->getViewLabel().length())
            {
                state[i] = false;
                continue;
            }
            if(!(graph.getNode()[i]->getViewLabel().substr(0, len) == view_label))
            {
                state[i] = false;
            }
        }
    }
    if(year.length() > 0)
    {
        int num = year.toInt();
        for(int i = 0; i < node_num; i++)
        {
            if(!(graph.getNode()[i]->getYear() == num))
            {
                state[i] = false;
            }
        }
    }
    if(type.length() > 0)
    {
        if(!QString::compare("paper", type, Qt::CaseInsensitive))
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!(graph.getNode()[i]->getType() == PaperConferenceAuthorNode::PAPER))
                {
                    state[i] = false;
                }
            }
            compareForMore(graph, state, page, year_f, author);
        }
        else if(!QString::compare("conference", type, Qt::CaseInsensitive))
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!(graph.getNode()[i]->getType() == PaperConferenceAuthorNode::CONFERENCE))
                {
                    state[i] = false;
                }
            }
        }
        else if(!QString::compare("author", type, Qt::CaseInsensitive))
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!(graph.getNode()[i]->getType() == PaperConferenceAuthorNode::AUTHOR))
                {
                    state[i] = false;
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                  state[i] = false;
            }
        }
    }
    accept();
}

void filterDialog::on_clear_b_clicked()
{
    ui->all_c->clear();
    ui->author_c->clear();
    ui->id_c->clear();
    ui->type_c->clear();
    ui->id_number_c->clear();
    ui->page_c->clear();
    ui->year_c->clear();
    ui->year_f_c->clear();
    ui->short_c->clear();
    ui->view_label_c->clear();
}

void filterDialog::compareForMore(PaperConferenceAuthorGraph
 & temp, vector<bool> & st, QString & pag, QString & year, string & autho)
{
    if(year.length() > 0)
    {
        int num = year.toInt();
        for(int i = 0; i < node_num; i++)
        {
            if(!(graph.getNode()[i]->getDateFrom() == num))
            {
                state[i] = false;
            }
        }
    }
    if(pag.length() > 0)
    {
        int num = pag.toInt();
        for(int i = 0; i < node_num; i++)
        {
            if(!(graph.getNode()[i]->getPageFrom() == num))
            {
                state[i] = false;
            }
        }
    }
    if(autho.length() > 0)
    {
        int len = autho.length();
        for(int i = 0; i < node_num; i++)
        {
            if(len > graph.getNode()[i]->getExtra().length())
            {
                state[i] = false;
                continue;
            }
            if(!(graph.getNode()[i]->getExtra().substr(0, len) == autho))
            {
                state[i] = false;
            }
        }
    }
}
