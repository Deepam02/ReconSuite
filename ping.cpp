#include "ui_ping.h"
#include "ping.h"
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
    loadCmdButton = createButton("Load");
    outputArea = new QTextEdit(this);
    modeComboBox = createComboBox({"Select Mode", "Standard Mode", "Verbose Output", "Flooding"});
    commandDisplay = createLineEdit("Command will be displayed here");
    pingProcess = new QProcess(this);
}

void ping::setupConnections()
{
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ping::onModeChanged);
    connect(pingButton, &QPushButton::clicked, this, &ping::executeCommand);
    connect(clearButton, &QPushButton::clicked, this, &ping::onClearButtonClicked);
    connect(loadCmdButton, &QPushButton::clicked, this, [=]() { onLoadButtonClicked(commandDisplay->text()); });
    connect(domainInput, &QLineEdit::returnPressed, this, &ping::onPingButtonClicked);
    connect(packetCountInput, &QLineEdit::returnPressed, this, &ping::onPingButtonClicked);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &ping::executeCommand);
    connect(pingProcess, &QProcess::readyReadStandardOutput, [=]() { outputArea->append(pingProcess->readAllStandardOutput()); });
    connect(pingProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nPing command finished with exit code: " + QString::number(exitCode));
                pingButton->setEnabled(true);
            });
}

void ping::setLayoutAndTitle()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainInput);
    layout->addWidget(packetCountInput);
    layout->addWidget(loadCmdButton);
    layout->addWidget(commandDisplay);
    layout->addWidget(pingButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("Ping Tool");
    outputArea->setReadOnly(true);
}

QLineEdit* ping::createLineEdit(const QString& placeholder)
{
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton* ping::createButton(const QString& text)
{
    return new QPushButton(text, this);
}

QComboBox* ping::createComboBox(const QStringList& items)
{
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

bool ping::isValidInput(const QString& input)
{
    static QRegularExpression domainPattern(R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)");
    return domainPattern.match(input).hasMatch();
}

QString pingSystem(const QString& host, int count)
{
    QString command = "ping " + host + " -c " + QString::number(count);
    QProcess pingProcess;
    QStringList arguments;
    arguments << "-c" << QString::number(count) << host;
    pingProcess.start("ping", arguments);
    pingProcess.waitForFinished();
    QString output = pingProcess.readAllStandardOutput();
    QRegularExpression regex("(\\d+) packets transmitted, (\\d+) received");
    QRegularExpressionMatch match = regex.match(output);

    if (match.hasMatch()) {
        int transmitted = match.captured(1).toInt();
        int received = match.captured(2).toInt();
        return (transmitted > 0 && received > 0) ? (command + "\nSystem is UP (running)") : (command + "\nSystem is DOWN (not working)");
    } else {
        return "Failed to parse ping output for command: " + command;
    }
}

void ping::onPingButtonClicked()
{
    outputArea->clear();
    outputArea->append("Pinging... Please wait.");

    QString domain = domainInput->text();
    QString packetCountStr = packetCountInput->text();
    bool ok;
    int count = packetCountStr.toInt(&ok);

    if (!ok || count <= 0) {
        outputArea->append("Enter a valid packet count.");
        return;
    }

    if (isValidInput(domain)) {
        QtConcurrent::run([=]() {
            QString result = pingSystem(domain, count);
            QMetaObject::invokeMethod(this, "updateOutput", Qt::QueuedConnection, Q_ARG(QString, result));
        });
    } else {
        outputArea->append("Enter a valid Domain or IP Address");
    }
}

void ping::updateOutput(const QString& result)
{
    outputArea->clear();
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
    QString command = commandDisplay->text();

    if (command.isEmpty()) {
        outputArea->append("Command is empty.");
        return;
    }

    outputArea->clear();
    outputArea->append("Executing command: " + command);

    QStringList args = {"-c", command};
    QString shell = "/bin/sh";

    QtConcurrent::run([=]() {
        QProcess process;
        QElapsedTimer timer;
        timer.start();

        process.start(shell, args);
        process.waitForFinished();

        int exitCode = process.exitCode();
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        if (exitCode != 0) {
            QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                      Q_ARG(QString, "Command execution failed with exit code: " + QString::number(exitCode)));
        }

        if (!error.isEmpty()) {
            QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                      Q_ARG(QString, "Error: " + error));
        }

        if (modeComboBox->currentIndex() == 1) {  // Standard mode
            // Checking for successful or failed pings
            if (output.contains("transmitted")) {
                QRegularExpression regex("(\\d+) packets transmitted, (\\d+) received");
                QRegularExpressionMatch match = regex.match(output);

                if (match.hasMatch()) {
                    int transmitted = match.captured(1).toInt();
                    int received = match.captured(2).toInt();

                    if (transmitted > 0 && received > 0) {
                        QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                                  Q_ARG(QString, "System is UP"));
                        return;
                    }
                }
                QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                          Q_ARG(QString, "System is DOWN"));
            } else {
                QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                          Q_ARG(QString, "Output:\n" + output));
            }
        } else {
            QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                      Q_ARG(QString, "Output:\n" + output));
        }

        // Adding time measurement using QElapsedTimer
        QString timeOutput = "Time taken: " + QString::number(timer.elapsed()) + " ms";
        QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                  Q_ARG(QString, timeOutput));
    });
}


void ping::updateCommandOutput(const QString& result)
{
    outputArea->append(result);
}

void ping::onLoadButtonClicked(QString cmdvariable)
{
    QString domain = domainInput->text();
    QString packetCountStr = packetCountInput->text();
    bool ok;
    int count = packetCountStr.toInt(&ok);

    if (isValidInput(domain)) {
        QString modeText;
        switch (modeComboBox->currentIndex()) {
        case 1: modeText = QString("ping %1 -c %2").arg(domain).arg(count); break;
        case 2: modeText = QString("ping -v -D %1 -c %2").arg(domain).arg(count); break;
        case 3: modeText = QString("ping %1 -c 100 -i 0.1").arg(domain); break;
        default: outputArea->append("Select a mode first."); return;
        }
        commandDisplay->setText(modeText);
    } else {
        outputArea->append("Enter a valid Domain or IP Address");
    }
}

void ping::standardMode() { packetCountInput->show(); }
void ping::verboseMode() { packetCountInput->show(); }
void ping::floodingMode() { packetCountInput->hide(); }

void ping::onModeChanged(int index)
{
    switch (index) {
    case 0: commandDisplay->setPlaceholderText("Command will be displayed here"); break;
    case 1: standardMode(); break;
    case 2: verboseMode(); break;
    case 3: floodingMode(); break;
    default: break;
    }
}
