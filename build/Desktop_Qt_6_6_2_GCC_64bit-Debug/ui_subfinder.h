/********************************************************************************
** Form generated from reading UI file 'subfinder.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBFINDER_H
#define UI_SUBFINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Subfinder
{
public:

    void setupUi(QWidget *Subfinder)
    {
        if (Subfinder->objectName().isEmpty())
            Subfinder->setObjectName("Subfinder");
        Subfinder->resize(640, 480);

        retranslateUi(Subfinder);

        QMetaObject::connectSlotsByName(Subfinder);
    } // setupUi

    void retranslateUi(QWidget *Subfinder)
    {
        Subfinder->setWindowTitle(QCoreApplication::translate("Subfinder", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Subfinder: public Ui_Subfinder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBFINDER_H
