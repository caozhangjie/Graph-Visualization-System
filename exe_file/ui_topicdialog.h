/********************************************************************************
** Form generated from reading UI file 'topicdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPICDIALOG_H
#define UI_TOPICDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_topicdialog
{
public:
    QPlainTextEdit *words_text;
    QTextEdit *number_text;
    QLineEdit *select_number;
    QPushButton *ok_b;
    QPushButton *exit_b;
    QPushButton *save_number;
    QPushButton *save_words;

    void setupUi(QDialog *topicdialog)
    {
        if (topicdialog->objectName().isEmpty())
            topicdialog->setObjectName(QStringLiteral("topicdialog"));
        topicdialog->resize(754, 423);
        topicdialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_back.jpg);"));
        words_text = new QPlainTextEdit(topicdialog);
        words_text->setObjectName(QStringLiteral("words_text"));
        words_text->setGeometry(QRect(190, 40, 501, 51));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        words_text->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Myriad Pro Light"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        words_text->setFont(font);
        words_text->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_big.jpg);"));
        number_text = new QTextEdit(topicdialog);
        number_text->setObjectName(QStringLiteral("number_text"));
        number_text->setGeometry(QRect(190, 180, 501, 51));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        number_text->setPalette(palette1);
        number_text->setFont(font);
        number_text->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_big.jpg);"));
        select_number = new QLineEdit(topicdialog);
        select_number->setObjectName(QStringLiteral("select_number"));
        select_number->setGeometry(QRect(280, 300, 441, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        select_number->setPalette(palette2);
        select_number->setFont(font);
        select_number->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_small.jpg);"));
        ok_b = new QPushButton(topicdialog);
        ok_b->setObjectName(QStringLiteral("ok_b"));
        ok_b->setGeometry(QRect(254, 352, 104, 41));
        ok_b->setFont(font);
        ok_b->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/ok.jpg);"));
        exit_b = new QPushButton(topicdialog);
        exit_b->setObjectName(QStringLiteral("exit_b"));
        exit_b->setGeometry(QRect(464, 352, 104, 41));
        exit_b->setFont(font);
        exit_b->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_exit.jpg);"));
        save_number = new QPushButton(topicdialog);
        save_number->setObjectName(QStringLiteral("save_number"));
        save_number->setGeometry(QRect(53, 230, 104, 41));
        save_number->setFont(font);
        save_number->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_save.jpg);"));
        save_words = new QPushButton(topicdialog);
        save_words->setObjectName(QStringLiteral("save_words"));
        save_words->setGeometry(QRect(53, 90, 104, 41));
        save_words->setFont(font);
        save_words->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_save.jpg);"));

        retranslateUi(topicdialog);

        QMetaObject::connectSlotsByName(topicdialog);
    } // setupUi

    void retranslateUi(QDialog *topicdialog)
    {
        topicdialog->setWindowTitle(QApplication::translate("topicdialog", "Dialog", 0));
        select_number->setText(QString());
        ok_b->setText(QString());
        exit_b->setText(QString());
        save_number->setText(QString());
        save_words->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class topicdialog: public Ui_topicdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPICDIALOG_H
