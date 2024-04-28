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

    outputArea->append("Executing command: " + command);

    QStringList args = {"-c", command};
    QString shell = "/bin/sh";

    QProcess *process = new QProcess(this);

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

    QtConcurrent::run([=]() {
        QElapsedTimer timer;
        timer.start();

        process->start(shell, args);
        process->waitForFinished();

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

        updateOutput("Time taken: " + QString::number(timer.elapsed()) + " ms");

        process->deleteLater();
    });
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
            modeText = QString("ping %1 -c 100 -i 0.1").arg(domain);
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
