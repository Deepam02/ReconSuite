/********************************************************************************
** Form generated from reading UI file 'nslookup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NSLOOKUP_H
#define UI_NSLOOKUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nslookup
{
public:

    void setupUi(QWidget *nslookup)
    {
        if (nslookup->objectName().isEmpty())
            nslookup->setObjectName("nslookup");
        nslookup->resize(640, 480);

        retranslateUi(nslookup);

        QMetaObject::connectSlotsByName(nslookup);
    } // setupUi

    void retranslateUi(QWidget *nslookup)
    {
        nslookup->setWindowTitle(QCoreApplication::translate("nslookup", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nslookup: public Ui_nslookup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NSLOOKUP_H
