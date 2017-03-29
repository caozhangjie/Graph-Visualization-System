/********************************************************************************
** Form generated from reading UI file 'nobezierdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOBEZIERDIALOG_H
#define UI_NOBEZIERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_noBezierDialog
{
public:

    void setupUi(QDialog *noBezierDialog)
    {
        if (noBezierDialog->objectName().isEmpty())
            noBezierDialog->setObjectName(QStringLiteral("noBezierDialog"));
        noBezierDialog->resize(400, 300);

        retranslateUi(noBezierDialog);

        QMetaObject::connectSlotsByName(noBezierDialog);
    } // setupUi

    void retranslateUi(QDialog *noBezierDialog)
    {
        noBezierDialog->setWindowTitle(QApplication::translate("noBezierDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class noBezierDialog: public Ui_noBezierDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOBEZIERDIALOG_H
