/********************************************************************************
** Form generated from reading UI file 'moreforpaperdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOREFORPAPERDIALOG_H
#define UI_MOREFORPAPERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_moreforpaperdialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *page;
    QLineEdit *year;
    QTextEdit *author;

    void setupUi(QDialog *moreforpaperdialog)
    {
        if (moreforpaperdialog->objectName().isEmpty())
            moreforpaperdialog->setObjectName(QStringLiteral("moreforpaperdialog"));
        moreforpaperdialog->resize(776, 473);
        moreforpaperdialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/moreforpaperbac.jpg);"));
        pushButton = new QPushButton(moreforpaperdialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(214, 380, 103, 46));
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_save.jpg);"));
        pushButton_2 = new QPushButton(moreforpaperdialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(456, 380, 103, 46));
        pushButton_2->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/ok.jpg);"));
        page = new QLineEdit(moreforpaperdialog);
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(252, 91, 119, 27));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        page->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(12);
        page->setFont(font);
        page->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/moresmallleft.jpg);"));
        year = new QLineEdit(moreforpaperdialog);
        year->setObjectName(QStringLiteral("year"));
        year->setGeometry(QRect(510, 91, 148, 27));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        year->setPalette(palette1);
        year->setFont(font);
        year->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/moresmallright.jpg);"));
        author = new QTextEdit(moreforpaperdialog);
        author->setObjectName(QStringLiteral("author"));
        author->setGeometry(QRect(130, 190, 531, 131));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        author->setPalette(palette2);
        author->setFont(font);
        author->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/morebig.jpg);"));

        retranslateUi(moreforpaperdialog);

        QMetaObject::connectSlotsByName(moreforpaperdialog);
    } // setupUi

    void retranslateUi(QDialog *moreforpaperdialog)
    {
        moreforpaperdialog->setWindowTitle(QApplication::translate("moreforpaperdialog", "Dialog", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class moreforpaperdialog: public Ui_moreforpaperdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOREFORPAPERDIALOG_H
