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
    commandOutput = new QTextEdit(this);
    traceProcess = new QProcess(this);
    commandComboBox = new QComboBox(this);
    commandComboBox->addItem("Default");
    commandComboBox->addItem("-m : Set the max number of hops");
    commandComboBox->addItem("-f : Start from the first TTL hop");
    commandComboBox->addItem("-F : Do not fragment packet");

    optionInput = new QLineEdit(this);
    optionInput->setPlaceholderText("Option Value");
    optionLabel = new QLabel("Option:", this);

    connect(traceButton, &QPushButton::clicked, this, &traceroute::onTraceButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &traceroute::onClearButtonClicked);
    connect(domainInput, &QLineEdit::returnPressed, this, &traceroute::onTraceButtonClicked);
    connect(commandComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &traceroute::updateCommand);

    connect(traceProcess, &QProcess::readyReadStandardOutput, [=]() {
        outputArea->append(traceProcess->readAllStandardOutput());
    });

    connect(traceProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nTraceroute command finished with exit code: " + QString::number(exitCode));
                traceButton->setEnabled(true);
            });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(commandComboBox);
    layout->addWidget(optionLabel);
    layout->addWidget(optionInput);
    layout->addWidget(traceButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);
    layout->addWidget(commandOutput);

    setLayout(layout);

    setWindowTitle("Traceroute Tool");
    outputArea->setReadOnly(true);
    commandOutput->setReadOnly(true);

    // Initially, hide the option input
    optionLabel->setVisible(false);
    optionInput->setVisible(false);
}

traceroute::~traceroute(){
    delete ui;
}

bool traceroute::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(
        R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)"
        );

    return domainPattern.match(input).hasMatch();
}

QString traceSystem(const QString& host, const QString& option, const QString& optionValue)
{
    QStringList arguments;
    if (option == "Default") {
        arguments << host;
    } else if (option == "-m" || option == "-f") {
        if (!optionValue.isEmpty()) {
            arguments << option << optionValue << host;
        } else {
            arguments << option << host;
        }
    }
    else {
        arguments << option << host;
    }

    QProcess traceProcess;
    traceProcess.start("traceroute", arguments);
    traceProcess.waitForFinished();

    return traceProcess.readAllStandardOutput();
}

void traceroute::onTraceButtonClicked()
{
    outputArea->clear();
    outputArea->append("Tracing... Please wait.");

    QString domain = domainInput->text();
    QString option = commandComboBox->currentText();
    QString optionValue = optionInput->text();

    if ((option == "-m" || option == "-f") && optionValue.isEmpty()) {
        outputArea->append("Please provide a value for the option.");
        return;
    }

    if (isValidInput(domain))
    {
        // Start trace process asynchronously
        QFuture<void> future = QtConcurrent::run([=]() {
            QString result = traceSystem(domain, option, optionValue);

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

    // Update command output
    QString command = "traceroute ";
    QString option = commandComboBox->currentText();
    QString optionValue = optionInput->text();
    if (option == "-m" || option == "-f" || option == "-F") {
        if (!optionValue.isEmpty()) {
            command += option + " " + optionValue + " " + domainInput->text();
        }
        else {
            command += option + " " + domainInput->text();
        }
    } else {
        command += domainInput->text();
    }
    commandOutput->setText(command);
}

void traceroute::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    optionInput->clear();
    commandOutput->clear();
    commandComboBox->setCurrentIndex(0);
}

void traceroute::updateCommand(){
    QString option = commandComboBox->currentText();
    if (option == "Default" || option == "-F") {
        optionInput->clear();
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    }
    else {
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
    }

    updateOutput(""); // Update command output when the option changes
}
