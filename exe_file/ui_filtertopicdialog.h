/********************************************************************************
** Form generated from reading UI file 'filtertopicdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERTOPICDIALOG_H
#define UI_FILTERTOPICDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_filterTopicDialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextEdit *id_c;
    QTextEdit *words_c;
    QTextEdit *paper_c;

    void setupUi(QDialog *filterTopicDialog)
    {
        if (filterTopicDialog->objectName().isEmpty())
            filterTopicDialog->setObjectName(QStringLiteral("filterTopicDialog"));
        filterTopicDialog->resize(662, 360);
        filterTopicDialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_background.jpg);"));
        pushButton = new QPushButton(filterTopicDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 300, 101, 41));
        QPalette palette;
        pushButton->setPalette(palette);
        QFont font;
        font.setPointSize(10);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/ok.jpg);"));
        pushButton_2 = new QPushButton(filterTopicDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 300, 101, 41));
        QPalette palette1;
        pushButton_2->setPalette(palette1);
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/clear .jpg);"));
        id_c = new QTextEdit(filterTopicDialog);
        id_c->setObjectName(QStringLiteral("id_c"));
        id_c->setGeometry(QRect(231, 91, 339, 45));
        QPalette palette2;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        id_c->setPalette(palette2);
        QFont font1;
        font1.setFamily(QStringLiteral("Myriad Pro Light"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        id_c->setFont(font1);
        id_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_edit.jpg);"));
        words_c = new QTextEdit(filterTopicDialog);
        words_c->setObjectName(QStringLiteral("words_c"));
        words_c->setGeometry(QRect(231, 143, 339, 45));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::NoBrush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::NoBrush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::NoBrush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        words_c->setPalette(palette3);
        words_c->setFont(font1);
        words_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_edit.jpg);"));
        paper_c = new QTextEdit(filterTopicDialog);
        paper_c->setObjectName(QStringLiteral("paper_c"));
        paper_c->setGeometry(QRect(231, 195, 339, 45));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush8(QColor(0, 0, 0, 255));
        brush8.setStyle(Qt::NoBrush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush9(QColor(0, 0, 0, 255));
        brush9.setStyle(Qt::NoBrush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush10(QColor(0, 0, 0, 255));
        brush10.setStyle(Qt::NoBrush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush10);
        paper_c->setPalette(palette4);
        paper_c->setFont(font1);
        paper_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_edit.jpg);"));

        retranslateUi(filterTopicDialog);

        QMetaObject::connectSlotsByName(filterTopicDialog);
    } // setupUi

    void retranslateUi(QDialog *filterTopicDialog)
    {
        filterTopicDialog->setWindowTitle(QApplication::translate("filterTopicDialog", "Dialog", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class filterTopicDialog: public Ui_filterTopicDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERTOPICDIALOG_H
