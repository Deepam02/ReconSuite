/********************************************************************************
** Form generated from reading UI file 'dnsenum.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DNSENUM_H
#define UI_DNSENUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dnsenum
{
public:

    void setupUi(QWidget *dnsenum)
    {
        if (dnsenum->objectName().isEmpty())
            dnsenum->setObjectName("dnsenum");
        dnsenum->resize(640, 480);

        retranslateUi(dnsenum);

        QMetaObject::connectSlotsByName(dnsenum);
    } // setupUi

    void retranslateUi(QWidget *dnsenum)
    {
        dnsenum->setWindowTitle(QCoreApplication::translate("dnsenum", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dnsenum: public Ui_dnsenum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DNSENUM_H
