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

widget::widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    // Create a vertical layout
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralWidget);
    QIcon icon(":/img/reconsuitelogo.jpg"); // Load the icon

    setWindowIcon(icon);

    // Create and set the label
    QLabel *label = new QLabel("ReconSuite");
    label->setAlignment(Qt::AlignCenter); // Center the text horizontally

    // Add the label to the main layout
    mainLayout->addWidget(label, 0, Qt::AlignTop | Qt::AlignHCenter); // Align the label to the top and center horizontally

    // Create a grid layout for the buttons
    QGridLayout *gridLayout = new QGridLayout;

    // Add buttons to the grid layout
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            QPushButton *button = createButton(row, col);
            gridLayout->addWidget(button, row, col);

            // Connect each button to the onButtonClicked function
            connect(button, &QPushButton::clicked, [this, row, col]() {
                onButtonClicked(row, col);
            });
        }
    }

    // Add the grid layout to the main layout
    mainLayout->addLayout(gridLayout);

    // Set the layout for the central widget
    ui->centralWidget->setLayout(mainLayout);

    // Set the window title
    setWindowTitle("ReconSuite");
    resize(800, 800);
}

widget::~widget()
{
    delete ui;
}

QPushButton* widget::createButton(int row, int col)
{
    QPushButton *button;
    if (row == 0 && col == 0) {
        button = new QPushButton("ping");
    }
    else if (row == 0 && col == 1) {
        button = new QPushButton("nmap");
    }
    else if (row == 0 && col == 2) {
        button = new QPushButton("traceroute");
    }
    else if (row == 0 && col == 3) {
        button = new QPushButton("whois");
    }
    else if (row == 1 && col == 0) {
        button = new QPushButton("dig");
    }
    else if (row == 1 && col == 1) {
        button = new QPushButton("subfinder");
    }
    else if (row == 1 && col == 2) {
        button = new QPushButton("DNSenum");
    }
    else {
        button = new QPushButton("tbd");
    }

    return button;
}

void widget::


    setupToolScreen(QWidget *toolScreen)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    // Add the tool widget to the top section of the splitter
    splitter->addWidget(toolScreen);

    // Create a widget for the button grid
    QWidget *buttonWidget = new QWidget(this);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonWidget);

    // Create and add buttons to the button layout
    for (int row = 0; row < 2; ++row) {
        QHBoxLayout *rowLayout = new QHBoxLayout;
        for (int col = 0; col < 4; ++col) {
            QPushButton *button = createButton(row, col);
            connect(button, &QPushButton::clicked, [this, row, col]() {
                onButtonClicked(row, col);
            });
            rowLayout->addWidget(button);
        }
        buttonLayout->addLayout(rowLayout);
    }

    // Add the button widget to the bottom section of the splitter
    splitter->addWidget(buttonWidget);

    // Set the size policy for the splitter
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(splitter);
}

void widget::onButtonClicked(int row, int col)
{
    if (currentScreen) {
        currentScreen->close();
        delete currentScreen;
        currentScreen = nullptr;
    }

    if (row == 0 && col == 0) {
        currentScreen = new ping(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 0 && col == 1) {
        currentScreen = new Nmap(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 0 && col == 2) {
        currentScreen = new traceroute(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 0 && col == 3) {
        currentScreen = new whois(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 1 && col == 0) {
        currentScreen = new DigTool(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 1 && col == 1) {
        currentScreen = new Subfinder(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 1 && col == 2) {
        currentScreen = new Dnsenum(this);
        setupToolScreen(currentScreen);
        currentScreen->show();
    }
    else if (row == 1 && col == 3) {
        // Handle the last button
    }
}
