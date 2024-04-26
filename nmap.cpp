#include "nmap.h"
#include "ui_nmap.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtConcurrent>


Nmap::Nmap(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::nmap)
{
    ui->setupUi(this);
    resize(800, 650);

    targetInput = createLineEdit("Enter target IP range");
    scanButton = createButton("Scan");
    passwordInput = createLineEdit("enter root password");
    clearButton = createButton("Clear");
    loadCmdButton = createButton("Load");
    outputArea = new QTextEdit(this);
    commandDisplay = createLineEdit("Command will be displayed here");
    scanProcess = new QProcess(this);
    modeComboBox = createComboBox({"Select Mode", "Intense Scan", "Quick Scan", "Stealth Scan"});

    connect(scanButton, &QPushButton::clicked, this, &Nmap::executeCommand);
    connect(clearButton, &QPushButton::clicked, this, &Nmap::onClearButtonClicked);
    connect(loadCmdButton, &QPushButton::clicked, this, &Nmap::onLoadButtonClicked);

    connect(targetInput, &QLineEdit::returnPressed, this, &Nmap::executeCommand);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &Nmap::executeCommand);

    connect(scanProcess, &QProcess::readyReadStandardOutput, [=]() {
        outputArea->append(scanProcess->readAllStandardOutput());
    });

    connect(scanProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nScan command finished with exit code: " + QString::number(exitCode));
                scanButton->setEnabled(true);
            });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(targetInput);
    layout->addWidget(passwordInput);
    layout->addWidget(modeComboBox);
    layout->addWidget(scanButton);
    layout->addWidget(clearButton);
    layout->addWidget(loadCmdButton);
    layout->addWidget(commandDisplay);
    layout->addWidget(outputArea);

    setLayout(layout);

    setWindowTitle("Network Scanner");
    outputArea->setReadOnly(true);
}

Nmap::~Nmap()
{
    delete ui;
}

QLineEdit* Nmap::createLineEdit(const QString& placeholder)
{
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton* Nmap::createButton(const QString& text)
{
    return new QPushButton(text, this);
}

QComboBox* Nmap::createComboBox(const QStringList& items)
{
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

bool Nmap::isValidInput(const QString &input)
{
    return !input.isEmpty();
}



void Nmap::onClearButtonClicked()
{
    outputArea->clear();
    targetInput->clear();
    commandDisplay->clear();
}

void Nmap::executeCommand()
{
    QString command = commandDisplay->text();

    if (command.isEmpty()) {
        outputArea->append("Command is empty.");
        return;
    }

    outputArea->clear();
    outputArea->append("Executing command: " + command);

    QStringList args = command.split(" ");
    QString shell = "/bin/sh";

    QtConcurrent::run([=]() {
        QProcess process;
        QElapsedTimer timer;
        timer.start();

        process.start(args[0], args.mid(1));
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

        QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                  Q_ARG(QString, "Output:\n" + output));

        // Display the number of open ports
        QRegularExpression portRegex("(\\d+)\\/open");
        QRegularExpressionMatchIterator matches = portRegex.globalMatch(output);
        int openPortsCount = 0;
        while (matches.hasNext()) {
            matches.next();
            openPortsCount++;
        }
        QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                  Q_ARG(QString, "Number of open ports found: " + QString::number(openPortsCount)));

        // Adding time measurement using QElapsedTimer
        QString timeOutput = "Time taken: " + QString::number(timer.elapsed()) + " ms";
        QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection,
                                  Q_ARG(QString, timeOutput));
    });
}


void Nmap::updateCommandOutput(const QString& result)
{
    outputArea->append(result);
}



void Nmap::onLoadButtonClicked()
{
    QString target = targetInput->text();
    QString password = passwordInput->text();
    QString mode = modeComboBox->currentText();

    if (isValidInput(target))
    {
        QString modeText;
        if (mode == "Intense Scan")
        {
            modeText = QString("echo %1 | nmap -A %2").arg(password,target);
        }
        else if (mode == "Quick Scan")
        {
            modeText = QString("nmap %1").arg(target);
        }
        else if (mode == "Stealth Scan")
        {
            modeText = QString("nmap -sS %1").arg(target);
        }
        commandDisplay->setText(modeText);
    }
    else
    {
        outputArea->append("Enter a valid target IP range");
    }
}
