/********************************************************************************
** Form generated from reading UI file 'nmap.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NMAP_H
#define UI_NMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nmap
{
public:

    void setupUi(QWidget *nmap)
    {
        if (nmap->objectName().isEmpty())
            nmap->setObjectName("nmap");
        nmap->resize(640, 480);

        retranslateUi(nmap);

        QMetaObject::connectSlotsByName(nmap);
    } // setupUi

    void retranslateUi(QWidget *nmap)
    {
        nmap->setWindowTitle(QCoreApplication::translate("nmap", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nmap: public Ui_nmap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NMAP_H
