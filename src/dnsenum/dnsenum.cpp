#include "dnsenum.h"
#include "ui_dnsenum.h"
#include <QVBoxLayout>
#include <QtConcurrent>

dnsenum::dnsenum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dnsenum)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    setLayoutAndTitle();
}

dnsenum::~dnsenum()
{
    delete ui;
}

void dnsenum::setupUI()
{
    domainInput = createLineEdit("Enter domain");
    modeComboBox = createComboBox({"Standard Mode",
                                   "--enum",
                                   "--enum -f",
                                   "--reverse",
                                   "--zonetransfer",
                                   "--enum --brute"});
    commandDisplay = createLineEdit("Command will be displayed here");
    enumerateButton = createButton("Enumerate");
    clearButton = createButton("Clear");
    outputArea = new QTextEdit(this);
}

void dnsenum::setupConnections()
{
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &dnsenum::updateCommandDisplay);
    connect(enumerateButton, &QPushButton::clicked, this, &dnsenum::executeCommand);
    connect(clearButton, &QPushButton::clicked, this, &dnsenum::onClearButtonClicked);
    connect(domainInput, &QLineEdit::returnPressed, this, &dnsenum::executeCommand);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &dnsenum::updateCommandDisplay);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &dnsenum::executeCommand);

    // Connect textChanged signal of domainInput to updateCommandDisplay slot
    connect(domainInput, &QLineEdit::textChanged, this, &dnsenum::updateCommandDisplay);
}


void dnsenum::setLayoutAndTitle()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainInput);
    layout->addWidget(commandDisplay);
    layout->addWidget(enumerateButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("DNS Enumeration Tool");
    outputArea->setReadOnly(true);
}

QLineEdit *dnsenum::createLineEdit(const QString &placeholder)
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton *dnsenum::createButton(const QString &text)
{
    return new QPushButton(text, this);
}

QComboBox *dnsenum::createComboBox(const QStringList &items)
{
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

void dnsenum::updateCommandDisplay()
{
    QString domain = domainInput->text();
    QString option = modeComboBox->currentText();
    QString command;

    if (option == "Standard Mode") {
        command = "dnsenum " + domain;
    } else if (option == "--enum") {
        command = "dnsenum --enum " + domain;
    } else if (option == "--enum -f") {
        command = "dnsenum --enum -f " + domain;
    } else if (option == "--reverse") {
        command = "dnsenum --reverse " + domain;
    } else if (option == "--zonetransfer") {
        command = "dnsenum --zonetransfer " + domain;
    } else if (option == "--enum --brute") {
        command = "dnsenum --enum --brute " + domain;
    }

    commandDisplay->setText(command);
}


void dnsenum::executeCommand()
{
    QString command = commandDisplay->text();

    if (command.isEmpty()) {
        outputArea->append("Command is empty.");
        return;
    }

    outputArea->clear();
    outputArea->append("Executing command: " + command);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QtConcurrent::run([=]() {
        QProcess process;
        process.start(command);
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();
        updateCommandOutput(output);
        updateCommandOutput(error);
        QApplication::restoreOverrideCursor();
    });
}

void dnsenum::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    commandDisplay->clear();
}

void dnsenum::updateCommandOutput(const QString &result)
{
    outputArea->append(result);
}
