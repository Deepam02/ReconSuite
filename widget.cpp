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

    // Add label to the tab widget
    QLabel *label = new QLabel("ReconSuite", tabWidget);
    label->setAlignment(Qt::AlignCenter);
    tabWidget->addTab(label, "home");

    // Set initial window size
    resize(800, 800);
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
}
