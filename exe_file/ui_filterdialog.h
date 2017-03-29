/********************************************************************************
** Form generated from reading UI file 'filterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERDIALOG_H
#define UI_FILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_filterDialog
{
public:
    QPushButton *ok_b;
    QPushButton *clear_b;
    QLineEdit *year_f_c;
    QLineEdit *author_c;
    QLineEdit *type_c;
    QLineEdit *year_c;
    QLineEdit *id_number_c;
    QLineEdit *id_c;
    QLineEdit *short_c;
    QLineEdit *all_c;
    QLineEdit *view_label_c;
    QLineEdit *page_c;

    void setupUi(QDialog *filterDialog)
    {
        if (filterDialog->objectName().isEmpty())
            filterDialog->setObjectName(QStringLiteral("filterDialog"));
        filterDialog->resize(773, 524);
        QPalette palette;
        filterDialog->setPalette(palette);
        filterDialog->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_back.jpg);"));
        ok_b = new QPushButton(filterDialog);
        ok_b->setObjectName(QStringLiteral("ok_b"));
        ok_b->setGeometry(QRect(186, 445, 114, 46));
        QFont font;
        font.setPointSize(10);
        ok_b->setFont(font);
        ok_b->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/ok.jpg);"));
        clear_b = new QPushButton(filterDialog);
        clear_b->setObjectName(QStringLiteral("clear_b"));
        clear_b->setGeometry(QRect(473, 445, 114, 46));
        clear_b->setFont(font);
        clear_b->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/clear .jpg);"));
        year_f_c = new QLineEdit(filterDialog);
        year_f_c->setObjectName(QStringLiteral("year_f_c"));
        year_f_c->setGeometry(QRect(375, 305, 310, 33));
        QPalette palette1;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        year_f_c->setPalette(palette1);
        QFont font1;
        font1.setFamily(QStringLiteral("Palatino Linotype"));
        font1.setPointSize(14);
        font1.setItalic(true);
        year_f_c->setFont(font1);
        year_f_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_long.jpg);"));
        author_c = new QLineEdit(filterDialog);
        author_c->setObjectName(QStringLiteral("author_c"));
        author_c->setGeometry(QRect(375, 350, 310, 33));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        author_c->setPalette(palette2);
        author_c->setFont(font1);
        author_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_long.jpg);"));
        type_c = new QLineEdit(filterDialog);
        type_c->setObjectName(QStringLiteral("type_c"));
        type_c->setGeometry(QRect(350, 200, 111, 33));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        type_c->setPalette(palette3);
        type_c->setFont(font1);
        type_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_short.jpg);"));
        year_c = new QLineEdit(filterDialog);
        year_c->setObjectName(QStringLiteral("year_c"));
        year_c->setGeometry(QRect(530, 200, 151, 33));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        year_c->setPalette(palette4);
        year_c->setFont(font1);
        year_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_rightup.jpg);"));
        id_number_c = new QLineEdit(filterDialog);
        id_number_c->setObjectName(QStringLiteral("id_number_c"));
        id_number_c->setGeometry(QRect(420, 90, 261, 33));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        id_number_c->setPalette(palette5);
        id_number_c->setFont(font1);
        id_number_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_rightup.jpg);"));
        id_c = new QLineEdit(filterDialog);
        id_c->setObjectName(QStringLiteral("id_c"));
        id_c->setGeometry(QRect(160, 90, 121, 33));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Text, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        id_c->setPalette(palette6);
        id_c->setFont(font1);
        id_c->setContextMenuPolicy(Qt::DefaultContextMenu);
        id_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_shortest.jpg);"));
        short_c = new QLineEdit(filterDialog);
        short_c->setObjectName(QStringLiteral("short_c"));
        short_c->setGeometry(QRect(180, 200, 111, 33));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Text, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        short_c->setPalette(palette7);
        short_c->setFont(font1);
        short_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_short.jpg);"));
        all_c = new QLineEdit(filterDialog);
        all_c->setObjectName(QStringLiteral("all_c"));
        all_c->setGeometry(QRect(160, 140, 121, 33));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Text, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        all_c->setPalette(palette8);
        all_c->setFont(font1);
        all_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_short.jpg);"));
        view_label_c = new QLineEdit(filterDialog);
        view_label_c->setObjectName(QStringLiteral("view_label_c"));
        view_label_c->setGeometry(QRect(420, 140, 261, 33));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Text, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        view_label_c->setPalette(palette9);
        view_label_c->setFont(font1);
        view_label_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_rightup.jpg);"));
        page_c = new QLineEdit(filterDialog);
        page_c->setObjectName(QStringLiteral("page_c"));
        page_c->setGeometry(QRect(375, 260, 310, 33));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Text, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        page_c->setPalette(palette10);
        page_c->setFont(font1);
        page_c->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/paper_filter_long.jpg);"));

        retranslateUi(filterDialog);

        QMetaObject::connectSlotsByName(filterDialog);
    } // setupUi

    void retranslateUi(QDialog *filterDialog)
    {
        filterDialog->setWindowTitle(QApplication::translate("filterDialog", "Dialog", 0));
        ok_b->setText(QString());
        clear_b->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class filterDialog: public Ui_filterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERDIALOG_H
