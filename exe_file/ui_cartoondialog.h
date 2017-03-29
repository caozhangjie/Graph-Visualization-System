/********************************************************************************
** Form generated from reading UI file 'cartoondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARTOONDIALOG_H
#define UI_CARTOONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_cartoonDialog
{
public:

    void setupUi(QDialog *cartoonDialog)
    {
        if (cartoonDialog->objectName().isEmpty())
            cartoonDialog->setObjectName(QStringLiteral("cartoonDialog"));
        cartoonDialog->resize(400, 300);

        retranslateUi(cartoonDialog);

        QMetaObject::connectSlotsByName(cartoonDialog);
    } // setupUi

    void retranslateUi(QDialog *cartoonDialog)
    {
        cartoonDialog->setWindowTitle(QApplication::translate("cartoonDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class cartoonDialog: public Ui_cartoonDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARTOONDIALOG_H
