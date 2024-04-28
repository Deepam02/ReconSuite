#include "ffuf.h"
#include "ui_ffuf.h"
#include <QProcess>
#include <QThread>

ffuf::ffuf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ffuf)
{
    ui->setupUi(this);
    setupUiElements();
}

ffuf::~ffuf()
{
    delete ui;
}

void ffuf::setupUiElements()
{
    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter URL");

    wordlistInput = new QLineEdit(this);
    wordlistInput->setPlaceholderText("Select Wordlist Location");

    browseButton = new QPushButton("Browse", this);
    connect(browseButton, &QPushButton::clicked, this, &ffuf::browseWordlist);

    commandOutput = new QTextEdit(this);
    commandOutput->setReadOnly(true);

    generateButton = new QPushButton("Generate Command", this);
    connect(generateButton, &QPushButton::clicked, this, &ffuf::generateCommand);

    startButton = new QPushButton("Start Brute Force", this);
    connect(startButton, &QPushButton::clicked, this, &ffuf::startBruteForce);
    startButton->setEnabled(false); // Disable start button initially

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(urlInput);
    layout->addWidget(wordlistInput);
    layout->addWidget(browseButton);
    layout->addWidget(generateButton);
    layout->addWidget(startButton);
    layout->addWidget(new QLabel("Generated Command:", this));
    layout->addWidget(commandOutput);

    setLayout(layout);
}

void ffuf::browseWordlist()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Wordlist File"), QDir::homePath(), tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        wordlistInput->setText(fileName);
        startButton->setEnabled(true); // Enable start button when wordlist is selected
    }
}

void ffuf::generateCommand()
{
    QString url = urlInput->text();
    QString wordlist = wordlistInput->text();

    if (url.isEmpty() || wordlist.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter URL and select Wordlist Location.");
        return;
    }

    generatedCommand = QString("ffuf -u \"%1/FUZZ\" -w \"%2\"").arg(url).arg(wordlist);
    commandOutput->setPlainText(generatedCommand);
}

void ffuf::startBruteForce()
{
    if (generatedCommand.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please generate the command first.");
        return;
    }

    QFile file(wordlistInput->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open wordlist file.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QString command = generatedCommand;
        command.replace("FUZZ", line);

        // Execute the modified command
        executeCommand(command);
        QThread::msleep(100); // Sleep for a short time to avoid flooding the UI
        QCoreApplication::processEvents(); // Process events to update the UI
    }

    file.close();
}

void ffuf::executeCommand(const QString &command)
{
    QProcess process;
    process.start(command);
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QTextStream stream(output);
    QString result = stream.readAll();

    // Display the result for each attempt
    commandOutput->append("Command: " + command);
    commandOutput->append("Result:\n" + result + "\n");
}
