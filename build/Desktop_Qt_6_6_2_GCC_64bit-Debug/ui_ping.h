/********************************************************************************
** Form generated from reading UI file 'ping.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PING_H
#define UI_PING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ping
{
public:

    void setupUi(QWidget *ping)
    {
        if (ping->objectName().isEmpty())
            ping->setObjectName("ping");
        ping->resize(640, 480);

        retranslateUi(ping);

        QMetaObject::connectSlotsByName(ping);
    } // setupUi

    void retranslateUi(QWidget *ping)
    {
        ping->setWindowTitle(QCoreApplication::translate("ping", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ping: public Ui_ping {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PING_H
