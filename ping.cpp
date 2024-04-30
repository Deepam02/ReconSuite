#include "ping.h"
#include "ui_ping.h"
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QtConcurrent>

ping::ping(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ping)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    setLayoutAndTitle();
}

ping::~ping()
{
    delete ui;
}

void ping::setupUI()
{
    domainInput = createLineEdit("Enter domain");
    packetCountInput = createLineEdit("Enter packet count");
    pingButton = createButton("Ping");
    clearButton = createButton("Clear");
    outputArea = new QTextEdit(this);
    modeComboBox = createComboBox({"Select Mode", "Standard Mode", "Verbose Output", "Flooding"});
    commandDisplay = createLineEdit("Command will be displayed here");
    stopButton = createButton("Stop");
}

void ping::setupConnections()
{
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ping::onModeChanged);
    connect(pingButton, &QPushButton::clicked, this, &ping::executeCommand);
    connect(clearButton, &QPushButton::clicked, this, &ping::onClearButtonClicked);
    connect(domainInput, &QLineEdit::returnPressed, this, &ping::executeCommand);
    connect(packetCountInput, &QLineEdit::returnPressed, this, &ping::executeCommand);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &ping::executeCommand);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ping::updateCommandDisplay);
    connect(domainInput, &QLineEdit::textChanged, this, &ping::updateCommandDisplay);
    connect(packetCountInput, &QLineEdit::textChanged, this, &ping::updateCommandDisplay);
    connect(stopButton, &QPushButton::clicked, this, &ping::stopExecution);

}

void ping::setLayoutAndTitle()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainInput);
    layout->addWidget(packetCountInput);
    layout->addWidget(commandDisplay);
    layout->addWidget(pingButton);
    layout->addWidget(clearButton);
    layout->addWidget(stopButton);
    layout->addWidget(outputArea);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("Ping Tool");
    outputArea->setReadOnly(true);
}

QLineEdit *ping::createLineEdit(const QString &placeholder)
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton *ping::createButton(const QString &text)
{
    return new QPushButton(text, this);
}

QComboBox *ping::createComboBox(const QStringList &items)
{
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

bool ping::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)");
    return domainPattern.match(input).hasMatch();
}

void ping::updateOutput(const QString &result)
{
    outputArea->append(result);
}

void ping::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    packetCountInput->clear();
    commandDisplay->clear();
}

void ping::executeCommand()
{
    outputArea->clear();
    QString command = commandDisplay->text();

    if (command.isEmpty())
    {
        outputArea->append("Command is empty.");
        return;
    }

    // Validate that the command contains the "ping" keyword
    if (!command.contains("ping", Qt::CaseInsensitive))
    {
        outputArea->append("Invalid command. Only 'ping' command is allowed.");
        return;
    }

    outputArea->clear(); // Clear any previous content

    if (modeComboBox->currentIndex() == 3)
    {
        // Display disclaimer in big red text
        outputArea->setText("<font color='red' size='6'>Disclaimer: Flooding PING request may result in IP ban. Press stop button after some time to avoid this.</font>");

        // Wait for a few seconds before starting code execution
        QTimer::singleShot(5000, this, [=]() {
            startExecution(command);
        });
    }
    else
    {
        // Start execution immediately
        startExecution(command);
    }
}

void ping::startExecution(const QString& command)
{
    outputArea->append("Executing command: " + command);

    QStringList args = {"-c", command};
    QString shell = "/bin/sh";

    process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
        QString output = process->readAllStandardOutput();
        if (modeComboBox->currentIndex() == 1) { // Standard Mode
            if (output.contains("transmitted")) {
                QRegularExpression regex("(\\d+) packets transmitted, (\\d+) received");
                QRegularExpressionMatch match = regex.match(output);

                if (match.hasMatch()) {
                    int transmitted = match.captured(1).toInt();
                    int received = match.captured(2).toInt();

                    if (transmitted > 0 && received > 0) {
                        updateOutput("System is UP");
                        return;
                    }
                }
                updateOutput("System is DOWN");
            }
        } else {
            updateOutput(output);
        }
    });

    // Connect the stop button to stopExecution slot
    connect(stopButton, &QPushButton::clicked, this, &ping::stopExecution);

    // Start the process
    process->start(shell, args);
    process->waitForStarted();

    // Use a timer to periodically check for process termination
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        if (process->state() == QProcess::NotRunning) {
            timer->stop();
            int exitCode = process->exitCode();
            QString error = process->readAllStandardError();

            if (exitCode != 0)
            {
                updateOutput("Command execution failed with exit code: " + QString::number(exitCode));
            }

            if (!error.isEmpty())
            {
                updateOutput("Error: " + error);
            }

            updateOutput("Command execution finished.");

            process->deleteLater();
        }
    });

    timer->start(100); // Check every 100 milliseconds
}



void ping::standardMode()
{
    packetCountInput->show();
}

void ping::verboseMode()
{
    packetCountInput->show();
}

void ping::floodingMode()
{
    packetCountInput->hide();
}

void ping::onModeChanged(int index)
{
    switch (index)
    {
    case 0:
        commandDisplay->setPlaceholderText("Command will be displayed here");
        break;
    case 1:
        standardMode();
        break;
    case 2:
        verboseMode();
        break;
    case 3:
        floodingMode();
        break;
    default:
        break;
    }
    updateCommandDisplay();
}

void ping::updateCommandDisplay()
{
    QString domain = domainInput->text();
    QString packetCountStr = packetCountInput->text();
    bool ok;
    int count = packetCountStr.toInt(&ok);

    if (isValidInput(domain))
    {
        QString modeText;
        switch (modeComboBox->currentIndex())
        {
        case 1:
            modeText = QString("ping %1 -c %2").arg(domain).arg(count);
            break;
        case 2:
            modeText = QString("ping -v -D %1 -c %2").arg(domain).arg(count);
            break;
        case 3:
            modeText = QString("ping %1 -i 0.002").arg(domain);
            break;
        default:
            commandDisplay->clear();
            return;
        }
        commandDisplay->setText(modeText);
    }
    else
    {
        commandDisplay->clear();
    }
}


void ping::stopExecution()
{
    if (process && process->state() != QProcess::NotRunning) {
        process->terminate();
        outputArea->append("Command execution stopped.");
    }
}
