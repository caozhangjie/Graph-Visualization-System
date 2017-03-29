#ifndef TOPICDIALOGH
#define TOPICDIALOGH

#include <QDialog>
#include "topicgraph.h"
namespace Ui {
class topicdialog;
}

class topicdialog : public QDialog
{
    Q_OBJECT

public:
    explicit topicdialog(TopicGraph & temp_topic, TopicNode & temp, QWidget *parent = 0);
    ~topicdialog();

private slots:

    void on_exit_b_clicked();

    void on_save_words_clicked();

    void on_save_number_clicked();

    void on_ok_b_clicked();

private:
    Ui::topicdialog *ui;
    TopicNode & graph;
    TopicGraph & topic;
    int words_num;
    int p;
    int number_num;
};

#endif // TOPICDIALOG_H
