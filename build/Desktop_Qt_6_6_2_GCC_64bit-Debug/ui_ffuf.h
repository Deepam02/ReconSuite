/********************************************************************************
** Form generated from reading UI file 'ffuf.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFUF_H
#define UI_FFUF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ffuf
{
public:

    void setupUi(QWidget *ffuf)
    {
        if (ffuf->objectName().isEmpty())
            ffuf->setObjectName("ffuf");
        ffuf->resize(640, 480);

        retranslateUi(ffuf);

        QMetaObject::connectSlotsByName(ffuf);
    } // setupUi

    void retranslateUi(QWidget *ffuf)
    {
        ffuf->setWindowTitle(QCoreApplication::translate("ffuf", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ffuf: public Ui_ffuf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFUF_H
