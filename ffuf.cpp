#include "ffuf.h"
#include <QProcess>
#include <QThread>
#include "ui_ffuf.h"
#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRandomGenerator>
ffuf::ffuf(QWidget *parent)
    : QWidget(parent), ui(new Ui::ffuf) {
    ui->setupUi(this);
    setupUiElements();
}

ffuf::~ffuf() {
    delete ui;
}

void ffuf::setupUiElements() {
    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter URL");

    wordlistInput = new QLineEdit(this);
    wordlistInput->setPlaceholderText("Select Wordlist Location");

    browseButton = new QPushButton("Browse", this);
    connect(browseButton, &QPushButton::clicked, this, &ffuf::browseWordlist);

    generateSubdomainButton = new QPushButton("Generate Subdomain Command", this);
    connect(generateSubdomainButton, &QPushButton::clicked, this, &ffuf::generateSubdomainCommand);

    generateDirectoryButton = new QPushButton("Generate Directory Command", this);
    connect(generateDirectoryButton, &QPushButton::clicked, this, &ffuf::generateDirectoryCommand);

    commandOutput = new QTextEdit(this);
    commandOutput->setReadOnly(true);

    generatedCommandText = new QTextEdit(this);
    generatedCommandText->setReadOnly(true);

    startButton = new QPushButton("Start Brute Force", this);
    connect(startButton, &QPushButton::clicked, this, &ffuf::startBruteForce);
    startButton->setEnabled(false); // Disable start button initially

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(urlInput);
    layout->addWidget(wordlistInput);
    layout->addWidget(browseButton);
    layout->addWidget(generateSubdomainButton);
    layout->addWidget(generateDirectoryButton);
    layout->addWidget(startButton);
    layout->addWidget(new QLabel("Generated Command:", this));
    layout->addWidget(generatedCommandText);  // Added for displaying the generated command
    layout->addWidget(new QLabel("Command Output:", this));
    layout->addWidget(commandOutput);

    setLayout(layout);
}

void ffuf::browseWordlist() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Wordlist File"),
                                                    QDir::homePath(),
                                                    tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        wordlistInput->setText(fileName);
        startButton->setEnabled(true); // Enable start button when wordlist is selected
    }
}


void ffuf::generateSubdomainCommand() {
    QString url = urlInput->text();
    QString wordlist = wordlistInput->text();

    if (url.isEmpty() || wordlist.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter URL and select Wordlist Location.");
        return;
    }

    // Replace "marketplace" with "FUZZ" in the URL
    QString modifiedUrl = url.replace(QRegularExpression("https?://[^.]+"), "https://FUZZ");

    generatedCommand = QString("ffuf -u \"%1\" -w \"%2\"").arg(modifiedUrl).arg(wordlist);
    generatedCommandText->setPlainText(generatedCommand);  // Display the generated command
}

void ffuf::generateDirectoryCommand() {
    QString url = urlInput->text();
    QString wordlist = wordlistInput->text();

    if (url.isEmpty() || wordlist.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter URL and select Wordlist Location.");
        return;
    }

    generatedCommand = QString("ffuf -u \"%1/FUZZ\" -w \"%2\"").arg(url).arg(wordlist);
    generatedCommandText->setPlainText(generatedCommand);  // Display the generated command
}

void ffuf::startBruteForce() {
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

void ffuf::executeCommand(const QString &command) {
    QProcess process;
    process.start(command);
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QTextStream stream(output);
    QString result = stream.readAll();

    // Extract the part of the URL where brute force is happening
    QString urlPart;
    QRegularExpression regex("-u \"(.*?)\"");
    QRegularExpressionMatch match = regex.match(command);
    if (match.hasMatch()) {
        urlPart = match.captured(1);
    }

    // Perform an HTTP request to check if the URL is active
    QNetworkAccessManager manager;
    QNetworkRequest request((QUrl(urlPart)));
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Check the response status code
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // Display the result for each attempt with the URL part and status
    commandOutput->append("URL Part: " + urlPart);
    commandOutput->append("Result: " + QString(statusCode == 200 ? "Active" : "Non-Active") + "\n");

    reply->deleteLater();
}
