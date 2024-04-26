#include "nslookup.h"
#include "ui_nslookup.h"
#include <QVBoxLayout>
#include <QtConcurrent>

nslookup::nslookup(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::nslookup)
{
    ui->setupUi(this);
    resize(800, 650);

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Enter domain or IP address");

    lookupButton = new QPushButton("Lookup", this);
    clearButton = new QPushButton("Clear", this);
    outputArea = new QTextEdit(this);
    nslookupProcess = new QProcess(this);

    connect(lookupButton, &QPushButton::clicked, this, &nslookup::onLookupButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &nslookup::onClearButtonClicked);

    connect(inputField, &QLineEdit::returnPressed, this, &nslookup::onLookupButtonClicked);

    connect(nslookupProcess, &QProcess::readyReadStandardOutput, [=]() {
        outputArea->append(nslookupProcess->readAllStandardOutput());
    });

    connect(nslookupProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nNSLookup command finished with exit code: " + QString::number(exitCode));
                lookupButton->setDisabled(false);
            });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(inputField);
    layout->addWidget(lookupButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);

    setLayout(layout);

    setWindowTitle("NSLookup Tool");
    outputArea->setReadOnly(true);
}

nslookup::~nslookup()
{
    delete ui;
}

bool nslookup::isValidInput(const QString &input)
{
    // Regular expression to validate domain or IP address
    static QRegularExpression pattern(
        R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)"
        );

    return pattern.match(input).hasMatch();
}

QString nslookupSystem(const QString& host)
{
    QString command = "nslookup " + host;
    QProcess nslookupProcess;
    nslookupProcess.start("nslookup", QStringList() << host);
    nslookupProcess.waitForFinished();

    QString output = nslookupProcess.readAllStandardOutput();
    return output;
}

void nslookup::onLookupButtonClicked()
{
    outputArea->clear();
    outputArea->append("Performing NSLookup... Please wait.");

    QString input = inputField->text();

    if (isValidInput(input))
    {
        // Start nslookup process asynchronously
        QFuture<void> future = QtConcurrent::run([=]() {
            QString result = nslookupSystem(input);

            // Update GUI in the main thread
            QMetaObject::invokeMethod(this, "updateOutput", Qt::QueuedConnection,
                                      Q_ARG(QString, result));
        });
    }
    else
    {
        outputArea->append("Enter a valid Domain or IP Address");
    }
}

void nslookup::updateOutput(const QString& result)
{
    // Remove the "Performing NSLookup..." message
    outputArea->clear();

    // Append the actual nslookup result
    outputArea->append(result);
}

void nslookup::onClearButtonClicked()
{
    outputArea->clear();
    inputField->clear();
}
