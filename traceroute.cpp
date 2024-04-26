#include "traceroute.h"
#include "ui_traceroute.h"
#include <QVBoxLayout>
#include <QtConcurrent>

traceroute::traceroute(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::traceroute)
{
    ui->setupUi(this);
    resize(800, 650);

    domainInput = new QLineEdit(this);
    domainInput->setPlaceholderText("Enter domain");

    traceButton = new QPushButton("Trace", this);
    clearButton = new QPushButton("Clear", this);
    outputArea = new QTextEdit(this);
    traceProcess = new QProcess(this);

    connect(traceButton, &QPushButton::clicked, this, &traceroute::onTraceButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &traceroute::onClearButtonClicked);

    connect(domainInput, &QLineEdit::returnPressed, this, &traceroute::onTraceButtonClicked);

    connect(traceProcess, &QProcess::readyReadStandardOutput, [=]() {
        outputArea->append(traceProcess->readAllStandardOutput());
    });

    connect(traceProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nTraceroute command finished with exit code: " + QString::number(exitCode));
                traceButton->setDisabled(false);
            });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(traceButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);

    setLayout(layout);

    setWindowTitle("Traceroute Tool");
    outputArea->setReadOnly(true);
}

traceroute::~traceroute()
{
    delete ui;
}

bool traceroute::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(
        R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)"
        );

    return domainPattern.match(input).hasMatch();
}

QString traceSystem(const QString& host) {
    QString command = "traceroute " + host;
    QProcess traceProcess;
    QStringList arguments;
    arguments << host;
    traceProcess.start("traceroute", arguments);
    traceProcess.waitForFinished();

    return traceProcess.readAllStandardOutput();
}

void traceroute::onTraceButtonClicked()
{
    outputArea->clear();
    outputArea->append("Tracing... Please wait.");

    QString domain = domainInput->text();

    if (isValidInput(domain))
    {
        // Start trace process asynchronously
        QFuture<void> future = QtConcurrent::run([=]() {
            QString result = traceSystem(domain);

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

void traceroute::updateOutput(const QString& result)
{
    // Remove the "Tracing..." message
    outputArea->clear();

    // Append the actual trace result
    outputArea->append(result);
}

void traceroute::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
}
