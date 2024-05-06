/********************************************************************************
** Form generated from reading UI file 'traceroute.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACEROUTE_H
#define UI_TRACEROUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_traceroute
{
public:

    void setupUi(QWidget *traceroute)
    {
        if (traceroute->objectName().isEmpty())
            traceroute->setObjectName("traceroute");
        traceroute->resize(640, 480);

        retranslateUi(traceroute);

        QMetaObject::connectSlotsByName(traceroute);
    } // setupUi

    void retranslateUi(QWidget *traceroute)
    {
        traceroute->setWindowTitle(QCoreApplication::translate("traceroute", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class traceroute: public Ui_traceroute {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACEROUTE_H
