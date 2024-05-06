/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionPing;
    QAction *actionNmap;
    QAction *actionTraceroute;
    QAction *actionWhois;
    QAction *actionDig;
    QAction *actionSubfinder;
    QAction *actionDnsenum;
    QAction *actionFfuf;
    QWidget *centralWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName("widget");
        widget->resize(1032, 523);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        actionNew = new QAction(widget);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(widget);
        actionOpen->setObjectName("actionOpen");
        actionPing = new QAction(widget);
        actionPing->setObjectName("actionPing");
        actionNmap = new QAction(widget);
        actionNmap->setObjectName("actionNmap");
        actionTraceroute = new QAction(widget);
        actionTraceroute->setObjectName("actionTraceroute");
        actionWhois = new QAction(widget);
        actionWhois->setObjectName("actionWhois");
        actionDig = new QAction(widget);
        actionDig->setObjectName("actionDig");
        actionSubfinder = new QAction(widget);
        actionSubfinder->setObjectName("actionSubfinder");
        actionDnsenum = new QAction(widget);
        actionDnsenum->setObjectName("actionDnsenum");
        actionFfuf = new QAction(widget);
        actionFfuf->setObjectName("actionFfuf");
        centralWidget = new QWidget(widget);
        centralWidget->setObjectName("centralWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMaximumSize(QSize(800, 554));
        widget->setCentralWidget(centralWidget);
        menubar = new QMenuBar(widget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1032, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        widget->setMenuBar(menubar);
        statusbar = new QStatusBar(widget);
        statusbar->setObjectName("statusbar");
        widget->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuTools->addAction(actionPing);
        menuTools->addAction(actionNmap);
        menuTools->addAction(actionTraceroute);
        menuTools->addAction(actionWhois);
        menuTools->addAction(actionDig);
        menuTools->addAction(actionSubfinder);
        menuTools->addAction(actionDnsenum);
        menuTools->addAction(actionFfuf);

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QMainWindow *widget)
    {
        widget->setWindowTitle(QCoreApplication::translate("widget", "widget", nullptr));
        actionNew->setText(QCoreApplication::translate("widget", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("widget", "Open", nullptr));
        actionPing->setText(QCoreApplication::translate("widget", "Ping", nullptr));
        actionNmap->setText(QCoreApplication::translate("widget", "Nmap", nullptr));
        actionTraceroute->setText(QCoreApplication::translate("widget", "Traceroute", nullptr));
        actionWhois->setText(QCoreApplication::translate("widget", "Whois", nullptr));
        actionDig->setText(QCoreApplication::translate("widget", "Dig", nullptr));
        actionSubfinder->setText(QCoreApplication::translate("widget", "Subfinder", nullptr));
        actionDnsenum->setText(QCoreApplication::translate("widget", "Dnsenum", nullptr));
        actionFfuf->setText(QCoreApplication::translate("widget", "Ffuf", nullptr));
        menuFile->setTitle(QCoreApplication::translate("widget", "File", nullptr));
        menuTools->setTitle(QCoreApplication::translate("widget", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
