/********************************************************************************
** Form generated from reading UI file 'searchresultdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHRESULTDIALOG_H
#define UI_SEARCHRESULTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_searchResultDialog
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *searchResultDialog)
    {
        if (searchResultDialog->objectName().isEmpty())
            searchResultDialog->setObjectName(QStringLiteral("searchResultDialog"));
        searchResultDialog->resize(697, 435);
        searchResultDialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/searchresult.jpg);"));
        textEdit = new QTextEdit(searchResultDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(150, 130, 401, 181));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        textEdit->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(12);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/search_kuang.jpg);"));
        pushButton = new QPushButton(searchResultDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(303, 360, 92, 43));
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/ok.jpg);"));

        retranslateUi(searchResultDialog);

        QMetaObject::connectSlotsByName(searchResultDialog);
    } // setupUi

    void retranslateUi(QDialog *searchResultDialog)
    {
        searchResultDialog->setWindowTitle(QApplication::translate("searchResultDialog", "Dialog", 0));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class searchResultDialog: public Ui_searchResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTDIALOG_H
