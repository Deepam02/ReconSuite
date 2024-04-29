#include "traceroute.h"
#include "ui_traceroute.h"
#include <QVBoxLayout>
#include <QtConcurrent>
#include <QRegularExpression>

traceroute::traceroute(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::traceroute)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    setLayoutAndTitle();
}

traceroute::~traceroute()
{
    delete ui;
}

void traceroute::setupUI()
{
    domainInput = createLineEdit("Enter domain");
    optionInput = createLineEdit("Option Value");
    optionLabel = new QLabel("Option:", this);
    optionLabel->setVisible(false);
    optionInput->setVisible(false);
    traceButton = createButton("Trace");
    clearButton = createButton("Clear");
    outputArea = new QTextEdit(this);
    modeComboBox = createComboBox({"Select Mode", "Standard Mode", "-m : Set the max number of hops", "-f : Start from the first TTL hop", "-F : Do not fragment packet"});
    commandDisplay = createLineEdit("Command will be displayed here");
}

void traceroute::setupConnections() {
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &traceroute::onModeChanged);
    connect(traceButton, &QPushButton::clicked, this, &traceroute::onTraceButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &traceroute::onClearButtonClicked);
    connect(domainInput, &QLineEdit::returnPressed, this, &traceroute::executeCommand);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &traceroute::updateCommandDisplay);
    connect(optionInput, &QLineEdit::returnPressed, this, &traceroute::executeCommand);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &traceroute::executeCommand);
    connect(optionInput, &QLineEdit::textChanged, this, &traceroute::updateCommandDisplay); // Changed here
    connect(domainInput, &QLineEdit::textChanged, this, &traceroute::updateCommandDisplay);   // Changed here
}



void traceroute::setLayoutAndTitle()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainInput);
    layout->addWidget(optionLabel);
    layout->addWidget(optionInput);
    layout->addWidget(commandDisplay);
    layout->addWidget(traceButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("Traceroute Tool");
    outputArea->setReadOnly(true);
}

QLineEdit* traceroute::createLineEdit(const QString& placeholder)
{
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton* traceroute::createButton(const QString& text)
{
    return new QPushButton(text, this);
}

QComboBox* traceroute::createComboBox(const QStringList& items)
{
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

bool traceroute::isValidInput(const QString& input)
{
    static QRegularExpression domainPattern(R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)");
    return domainPattern.match(input).hasMatch();
}

void traceroute::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    optionInput->clear();
    commandDisplay->clear();
}

void traceroute::executeCommand()
{
    QString command = commandDisplay->text();

    if (command.isEmpty())
    {
        outputArea->append("Command is empty.");
        return;
    }

    outputArea->clear();
    outputArea->append("Executing command: " + command);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QStringList args = command.split(" ");

    QtConcurrent::run([=]() {
        QProcess process;
        QElapsedTimer timer;
        timer.start();

        process.start(args[0], args.mid(1));
        process.waitForFinished();

        int exitCode = process.exitCode();
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        if (exitCode != 0)
        {
            updateCommandOutput("Command execution failed with exit code: " + QString::number(exitCode));
        }

        if (!error.isEmpty())
        {
            updateCommandOutput("Error: " + error);
        }
        QApplication::restoreOverrideCursor();
        updateCommandOutput("Output:\n" + output);


        // Adding time measurement using QElapsedTimer
        QString timeOutput = "Time taken: " + QString::number(timer.elapsed()) + " ms";
        updateCommandOutput(timeOutput);
    });
}

void traceroute::updateCommandOutput(const QString& result){
    outputArea->append(result);
}

void traceroute::onModeChanged(int index)
{
    switch (index) {
    case 0:
        // Handle case 0
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
        break;
    case 1:
        // Handle case 1
        optionLabel->setText("-m : Set the max number of hops");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        break;
    case 2:
        // Handle case 2
        optionLabel->setText("-f : Start from the first TTL hop");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        break;
    case 3:
        // Handle case 3
        optionLabel->setText("-F : Do not fragment packet");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        break;
    default:
        break;
    }
    updateCommandDisplay(); // Update the command display based on the mode change
}

void traceroute::updateCommandDisplay()
{
    QString domain = domainInput->text();
    QString option = modeComboBox->currentText();
    QString optionValue = optionInput->text();
    QString command = "traceroute ";

    if (option == "Standard Mode") {
        command += domain;
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "-m") {
        command += "-m ";
        optionLabel->setText("Max Hops:");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
    } else if (option == "-f") {
        command += "-f ";
        optionLabel->setText("Start TTL:");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
    } else if (option == "-F") {
        command += "-F ";
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    }

    if (!optionValue.isEmpty()) {
        command += optionValue + " ";
    }
    // command += domain;

    commandDisplay->setText(command);
}

QString traceroute::traceSystem(const QString& host, const QString& option, const QString& optionValue)
{
    QStringList arguments;
    if (option == "Default" || option == "-F") {
        arguments << host;
    } else if (option == "-m" || option == "-f") {
        if (!optionValue.isEmpty()) {
            arguments << option << optionValue << host;
        } else {
            arguments << option << host;
        }
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
    QString option = modeComboBox->currentText();
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


void traceroute::updateOutput(const QString& result){
    // Remove the "Tracing..." message
    outputArea->clear();

    // Append the actual trace result
    outputArea->append(result);

    QString command = commandDisplay->text();
}
