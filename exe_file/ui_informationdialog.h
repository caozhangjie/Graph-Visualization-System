/********************************************************************************
** Form generated from reading UI file 'informationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONDIALOG_H
#define UI_INFORMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InformationDialog
{
public:
    QLineEdit *year_content;
    QLineEdit *id_content;
    QLineEdit *title_short_content;
    QLineEdit *view_label_content;
    QPushButton *more;
    QPushButton *ok;
    QPushButton *save;
    QPlainTextEdit *title_content;
    QLineEdit *type_content;
    QLabel *title_short_label;
    QLabel *title_label;

    void setupUi(QDialog *InformationDialog)
    {
        if (InformationDialog->objectName().isEmpty())
            InformationDialog->setObjectName(QStringLiteral("InformationDialog"));
        InformationDialog->resize(888, 585);
        InformationDialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_bac.jpg);"));
        year_content = new QLineEdit(InformationDialog);
        year_content->setObjectName(QStringLiteral("year_content"));
        year_content->setGeometry(QRect(420, 123, 143, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        year_content->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(12);
        year_content->setFont(font);
        year_content->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_short.jpg);"));
        id_content = new QLineEdit(InformationDialog);
        id_content->setObjectName(QStringLiteral("id_content"));
        id_content->setGeometry(QRect(600, 123, 181, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        id_content->setPalette(palette1);
        id_content->setFont(font);
        id_content->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_rightup.jpg);"));
        title_short_content = new QLineEdit(InformationDialog);
        title_short_content->setObjectName(QStringLiteral("title_short_content"));
        title_short_content->setGeometry(QRect(310, 380, 471, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        title_short_content->setPalette(palette2);
        title_short_content->setFont(font);
        title_short_content->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_long.jpg);"));
        view_label_content = new QLineEdit(InformationDialog);
        view_label_content->setObjectName(QStringLiteral("view_label_content"));
        view_label_content->setGeometry(QRect(310, 200, 471, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        view_label_content->setPalette(palette3);
        view_label_content->setFont(font);
        view_label_content->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_rightup.jpg);"));
        more = new QPushButton(InformationDialog);
        more->setObjectName(QStringLiteral("more"));
        more->setGeometry(QRect(165, 505, 122, 49));
        more->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_more.jpg);"));
        ok = new QPushButton(InformationDialog);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(590, 505, 122, 49));
        ok->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/ok.jpg);"));
        save = new QPushButton(InformationDialog);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(380, 505, 122, 49));
        save->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_save.jpg);"));
        title_content = new QPlainTextEdit(InformationDialog);
        title_content->setObjectName(QStringLiteral("title_content"));
        title_content->setGeometry(QRect(310, 270, 471, 71));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        title_content->setPalette(palette4);
        title_content->setFont(font);
        title_content->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_rightup.jpg);"));
        type_content = new QLineEdit(InformationDialog);
        type_content->setObjectName(QStringLiteral("type_content"));
        type_content->setGeometry(QRect(190, 123, 151, 31));
        QPalette palette5;
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        QBrush brush6(QColor(240, 240, 240, 0));
        brush6.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush6);
        QBrush brush7(QColor(255, 255, 255, 0));
        brush7.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush7);
        QBrush brush8(QColor(247, 247, 247, 0));
        brush8.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush8);
        QBrush brush9(QColor(120, 120, 120, 0));
        brush9.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush9);
        QBrush brush10(QColor(160, 160, 160, 0));
        brush10.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush10);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush11(QColor(255, 255, 255, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush11);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush11);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush5);
        QBrush brush12(QColor(247, 247, 247, 127));
        brush12.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush12);
        QBrush brush13(QColor(255, 255, 220, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush13);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush5);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush7);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush8);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush10);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush5);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush12);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush13);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush5);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush7);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush8);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush10);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush5);
        type_content->setPalette(palette5);
        type_content->setFont(font);
        type_content->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_shortest.jpg);"));
        title_short_label = new QLabel(InformationDialog);
        title_short_label->setObjectName(QStringLiteral("title_short_label"));
        title_short_label->setGeometry(QRect(150, 380, 151, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush11);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush11);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush11);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        title_short_label->setPalette(palette6);
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        title_short_label->setFont(font1);
        title_short_label->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/my_label2.png);"));
        title_short_label->setAlignment(Qt::AlignCenter);
        title_label = new QLabel(InformationDialog);
        title_label->setObjectName(QStringLiteral("title_label"));
        title_label->setGeometry(QRect(150, 270, 151, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush11);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush11);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        title_label->setPalette(palette7);
        title_label->setFont(font1);
        title_label->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/my_label.png);"));
        title_label->setTextFormat(Qt::AutoText);
        title_label->setAlignment(Qt::AlignCenter);

        retranslateUi(InformationDialog);

        QMetaObject::connectSlotsByName(InformationDialog);
    } // setupUi

    void retranslateUi(QDialog *InformationDialog)
    {
        InformationDialog->setWindowTitle(QApplication::translate("InformationDialog", "Dialog", 0));
        id_content->setText(QString());
        title_short_content->setText(QString());
        view_label_content->setText(QString());
        more->setText(QString());
        ok->setText(QString());
        save->setText(QString());
        type_content->setText(QString());
        title_short_label->setText(QString());
        title_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InformationDialog: public Ui_InformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONDIALOG_H
