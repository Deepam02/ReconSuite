#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QSplitter>
#include "ping.h"
#include "nmap.h"
#include "dig.h"
#include "traceroute.h"
#include "nslookup.h"
#include "subfinder.h"
#include "dnsenum.h"
#include "whois.h"
#include "ffuf.h"


widget::widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralWidget);
    QIcon icon(":/img/reconsuitelogo.jpg");
    setWindowIcon(icon);

    QLabel *label = new QLabel("ReconSuite");
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label, 0, Qt::AlignTop | Qt::AlignHCenter);

    ui->centralWidget->setLayout(mainLayout);

    setWindowTitle("ReconSuite");
    resize(800, 800);
}

widget::~widget()
{
    delete ui;
}

void widget::setupToolScreen(QWidget *toolScreen)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    // Add the tool widget to the top section of the splitter
    splitter->addWidget(toolScreen);




    // Set the size policy for the splitter
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(splitter);
}





void widget::on_actionPing_triggered()
{
    currentScreen = new ping(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionNmap_triggered()
{
    currentScreen = new Nmap(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionTraceroute_triggered()
{
    currentScreen = new traceroute(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionSubfinder_triggered()
{
    currentScreen = new Subfinder(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionDig_triggered()
{
    currentScreen = new DigTool(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionWhois_triggered()
{
    currentScreen = new whois(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionDnsenum_triggered()
{
    currentScreen = new Dnsenum(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}

void widget::on_actionFfuf_triggered()
{
    currentScreen = new ffuf(this);
    setupToolScreen(currentScreen);
    currentScreen->show();
}
