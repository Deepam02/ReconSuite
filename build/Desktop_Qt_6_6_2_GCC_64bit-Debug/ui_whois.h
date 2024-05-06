/********************************************************************************
** Form generated from reading UI file 'whois.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHOIS_H
#define UI_WHOIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_whois
{
public:

    void setupUi(QWidget *whois)
    {
        if (whois->objectName().isEmpty())
            whois->setObjectName("whois");
        whois->resize(640, 480);

        retranslateUi(whois);

        QMetaObject::connectSlotsByName(whois);
    } // setupUi

    void retranslateUi(QWidget *whois)
    {
        whois->setWindowTitle(QCoreApplication::translate("whois", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class whois: public Ui_whois {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHOIS_H
