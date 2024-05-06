#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "ping.h"
#include "nmap.h"
#include "dig.h"
#include "traceroute.h"
#include "subfinder.h"
#include "dnsenum.h"
#include "whois.h"
#include "ffuf.h"

widget::widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    // Create the tab widget
    tabWidget = new QTabWidget(this);


    // Set the size policy for the tab widget
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    // Set the tab widget as the central widget
    setCentralWidget(tabWidget);

    // Set window properties
    QIcon icon(":/img/reconsuitelogo.jpg");
    setWindowIcon(icon);
    setWindowTitle("ReconSuite");

    // Add content to the home tab
    QWidget *homeWidget = new QWidget(this);
    QVBoxLayout *homeLayout = new QVBoxLayout(homeWidget);

    QLabel *titleLabel = new QLabel("Welcome to ReconSuite", homeWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    homeLayout->addWidget(titleLabel);

    QLabel *descriptionLabel = new QLabel("ReconSuite is a comprehensive GUI application built using Qt C++ that integrates a suite of reconnaissance tools for network analysis and information gathering. This project aims to provide a user-friendly interface for common reconnaissance tasks, streamlining the process for both beginners and experienced users.", homeWidget);
    descriptionLabel->setWordWrap(true);
    homeLayout->addWidget(descriptionLabel);

    QLabel *featuresLabel = new QLabel("Features:", homeWidget);
    featuresLabel->setFont(QFont("Arial", 14, QFont::Bold));
    homeLayout->addWidget(featuresLabel);

    // Add features list
    QListWidget *featuresList = new QListWidget(homeWidget);
    QStringList features;
    features << "Ping: Check the reachability of a host on an IP network."
             << "Nmap: Perform network discovery and security auditing."
             << "Dig: Query DNS servers for information about host addresses, mail exchanges, and other data."
             << "Traceroute: Trace the route taken by packets across an IP network."
             << "Whois: Retrieve registration information for domain names."
             << "Dnsenum: Perform DNS enumeration to gather information about DNS nameservers and zones."
             << "Subfinder: Discover subdomains belonging to a domain."
             << "Ffuf: A fast web fuzzer used for directory and parameter brute-forcing.";
    featuresList->addItems(features);
    homeLayout->addWidget(featuresList);

    tabWidget->addTab(homeWidget, "Home");

    // Set initial window size
    resize(800, 800);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &widget::on_tabWidget_tabCloseRequested);
}



widget::~widget()
{
    delete ui;
}

void widget::on_actionPing_triggered()
{
    ping *pingWidget = new ping(this);
    addToolTab(pingWidget, "Ping");
}

void widget::on_actionNmap_triggered()
{
    Nmap *nmapWidget = new Nmap(this);
    addToolTab(nmapWidget, "Nmap");
}

void widget::on_actionTraceroute_triggered()
{
    traceroute *tracerouteWidget = new traceroute(this);
    addToolTab(tracerouteWidget, "Traceroute");
}

void widget::on_actionSubfinder_triggered()
{
    Subfinder *subfinderWidget = new Subfinder(this);
    addToolTab(subfinderWidget, "Subfinder");
}

void widget::on_actionDig_triggered()
{
    dig *digWidget = new dig(this);
    addToolTab(digWidget, "Dig");
}

void widget::on_actionWhois_triggered()
{
    whois *whoisWidget = new whois(this);
    addToolTab(whoisWidget, "Whois");
}

void widget::on_actionDnsenum_triggered()
{
    Dnsenum *dnsenumWidget = new Dnsenum(this);
    addToolTab(dnsenumWidget, "Dnsenum");
}

void widget::on_actionFfuf_triggered()
{
    ffuf *ffufWidget = new ffuf(this);
    addToolTab(ffufWidget, "Ffuf");
}

void widget::addToolTab(QWidget *toolWidget, const QString &label)
{
    // Add the tool widget as a new tab
    tabWidget->addTab(toolWidget, label);
    int newIndex = tabWidget->count() - 1; // Index of the newly added tab
    tabWidget->setCurrentIndex(newIndex);
    if (label == "Home") {
        tabWidget->setMovable(false);
        tabWidget->setTabsClosable(false);
    }
    else{
        tabWidget->setMovable(true);
        tabWidget->setTabsClosable(true);
    }
}

void widget::on_tabWidget_tabCloseRequested(int index){

    tabWidget->removeTab(index);
}

