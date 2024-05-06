/********************************************************************************
** Form generated from reading UI file 'dig.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIG_H
#define UI_DIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dig
{
public:

    void setupUi(QWidget *dig)
    {
        if (dig->objectName().isEmpty())
            dig->setObjectName("dig");
        dig->resize(640, 480);

        retranslateUi(dig);

        QMetaObject::connectSlotsByName(dig);
    } // setupUi

    void retranslateUi(QWidget *dig)
    {
        dig->setWindowTitle(QCoreApplication::translate("dig", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dig: public Ui_dig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIG_H
