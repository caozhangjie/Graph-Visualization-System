/********************************************************************************
** Form generated from reading UI file 'docdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCDIALOG_H
#define UI_DOCDIALOG_H

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

class Ui_docDialog
{
public:
    QLineEdit *number;
    QTextEdit *doc;
    QPushButton *save;
    QPushButton *exit;

    void setupUi(QDialog *docDialog)
    {
        if (docDialog->objectName().isEmpty())
            docDialog->setObjectName(QStringLiteral("docDialog"));
        docDialog->resize(815, 534);
        docDialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/docnode.jpg);"));
        number = new QLineEdit(docDialog);
        number->setObjectName(QStringLiteral("number"));
        number->setGeometry(QRect(210, 90, 441, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        number->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Myriad Pro Light"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        number->setFont(font);
        number->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/doc_small.jpg);"));
        doc = new QTextEdit(docDialog);
        doc->setObjectName(QStringLiteral("doc"));
        doc->setGeometry(QRect(150, 170, 501, 211));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        doc->setPalette(palette1);
        doc->setFont(font);
        doc->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/doc_big.jpg);"));
        save = new QPushButton(docDialog);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(208, 440, 109, 49));
        save->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_save.jpg);"));
        exit = new QPushButton(docDialog);
        exit->setObjectName(QStringLiteral("exit"));
        exit->setGeometry(QRect(460, 441, 109, 49));
        exit->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/topic_exit.jpg);"));

        retranslateUi(docDialog);

        QMetaObject::connectSlotsByName(docDialog);
    } // setupUi

    void retranslateUi(QDialog *docDialog)
    {
        docDialog->setWindowTitle(QApplication::translate("docDialog", "Dialog", 0));
        save->setText(QString());
        exit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class docDialog: public Ui_docDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCDIALOG_H
