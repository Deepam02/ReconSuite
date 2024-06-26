#include "traceroute.h"
#include "ui_traceroute.h"
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QtConcurrent>

traceroute::traceroute(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::traceroute)
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
    modeComboBox = createComboBox({"Select Mode",
                                   "Standard Mode",
                                   "-m : Set the max number of hops",
                                   "-f : Start from the first TTL hop",
                                   "-F : Do not fragment packet"});
    commandDisplay = createLineEdit("Command will be displayed here");
    tcpCheckbox = new QCheckBox("Use TCP SYN for tracerouting", this);
    udpCheckbox = new QCheckBox("Use UDP for tracerouting", this);
    portInput = createLineEdit("Port Number");
    portInput->setValidator(new QIntValidator(1, 65535, this)); // Port range validator
}

void traceroute::setupConnections()
{
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &traceroute::onModeChanged);
    connect(traceButton, &QPushButton::clicked, this, &traceroute::executeCommand);
    connect(clearButton, &QPushButton::clicked, this, &traceroute::onClearButtonClicked);
    connect(domainInput, &QLineEdit::returnPressed, this, &traceroute::executeCommand);
    connect(modeComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &traceroute::updateCommandDisplay);
    connect(optionInput, &QLineEdit::returnPressed, this, &traceroute::executeCommand);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &traceroute::executeCommand);
    connect(optionInput,
            &QLineEdit::textChanged,
            this,
            &traceroute::updateCommandDisplay);
    connect(domainInput,
            &QLineEdit::textChanged,
            this,
            &traceroute::updateCommandDisplay);
    connect(tcpCheckbox, &QCheckBox::stateChanged, this, &traceroute::updateCommandDisplay);
    connect(udpCheckbox, &QCheckBox::stateChanged, this, &traceroute::updateCommandDisplay);
    connect(portInput, &QLineEdit::returnPressed, this, &traceroute::executeCommand); // Add this line
}

void traceroute::setLayoutAndTitle()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainInput);
    layout->addWidget(optionLabel);
    layout->addWidget(optionInput);
    layout->addWidget(commandDisplay);
    layout->addWidget(tcpCheckbox);
    layout->addWidget(udpCheckbox);
    layout->addWidget(portInput);
    layout->addWidget(traceButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("Traceroute Tool");
    outputArea->setReadOnly(true);
}

QLineEdit *traceroute::createLineEdit(const QString &placeholder)
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton *traceroute::createButton(const QString &text)
{
    return new QPushButton(text, this);
}

QComboBox *traceroute::createComboBox(const QStringList &items)
{
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

bool traceroute::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(
        R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)");
    return domainPattern.match(input).hasMatch();
}

void traceroute::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    optionInput->clear();
    commandDisplay->clear();
    tcpCheckbox->setChecked(false);
    udpCheckbox->setChecked(false);
}

void traceroute::executeCommand()
{
    QString command = commandDisplay->text();

    if (command.isEmpty()) {
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

        if (exitCode != 0) {
            updateCommandOutput("Command execution failed with exit code: "
                                + QString::number(exitCode));
        }

        if (!error.isEmpty()) {
            updateCommandOutput("Error: " + error);
        }
        QApplication::restoreOverrideCursor();
        updateCommandOutput("Output:\n" + output);

        // Adding time measurement using QElapsedTimer
        QString timeOutput = "Time taken: " + QString::number(timer.elapsed()) + " ms";
        updateCommandOutput(timeOutput);
    });
}

void traceroute::updateCommandOutput(const QString &result)
{
    outputArea->append(result);
}

void traceroute::onModeChanged(int index)
{
    switch (index) {
    case 0:
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
        tcpCheckbox->setChecked(false); // Uncheck TCP checkbox
        udpCheckbox->setChecked(false); // Uncheck UDP checkbox
        tcpCheckbox->setEnabled(false); // Disable TCP checkbox
        udpCheckbox->setEnabled(false); // Disable UDP checkbox
        portInput->setEnabled(false);
        break;
    case 1:
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
        tcpCheckbox->setChecked(false); // Uncheck TCP checkbox
        udpCheckbox->setChecked(false); // Uncheck UDP checkbox
        tcpCheckbox->setEnabled(true); // Disable TCP checkbox
        udpCheckbox->setEnabled(true); // Disable UDP checkbox
        portInput->setEnabled(true);
        break;

    case 2:
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        tcpCheckbox->setChecked(false); // Uncheck TCP checkbox
        udpCheckbox->setChecked(false); // Uncheck UDP checkbox
        tcpCheckbox->setEnabled(false); // Disable TCP checkbox
        udpCheckbox->setEnabled(false); // Disable UDP checkbox
        portInput->setEnabled(false);
        break;

    case 3:
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        tcpCheckbox->setChecked(false); // Uncheck TCP checkbox
        udpCheckbox->setChecked(false); // Uncheck UDP checkbox
        tcpCheckbox->setEnabled(false); // Disable TCP checkbox
        udpCheckbox->setEnabled(false); // Disable UDP checkbox
        portInput->setEnabled(false);
        break;

    case 4:
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        tcpCheckbox->setChecked(false); // Uncheck TCP checkbox
        udpCheckbox->setChecked(false); // Uncheck UDP checkbox
        tcpCheckbox->setEnabled(false); // Disable TCP checkbox
        udpCheckbox->setEnabled(false); // Disable UDP checkbox
        portInput->setEnabled(false);

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

    if (tcpCheckbox->isChecked()) {
        command += "-T ";
        QString portNumber = portInput->text();
        if (!portNumber.isEmpty()) {
            command += "-p " + portNumber + " ";
        } else {
            command += "-p 80 "; // Default port is 80
        }
    } else if (udpCheckbox->isChecked()) {
        command += "-U ";
        QString portNumber = portInput->text();
        if (!portNumber.isEmpty()) {
            command += "-p " + portNumber + " ";
        } else {
            command += "-p 53 "; // Default port is 53 for UDP
        }
    }

    if (option == "Standard Mode") {
        command += domain;
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "-m : Set the max number of hops") {
        command += "-m ";
        if (!optionValue.isEmpty()) {
            command += optionValue + " ";
        }
        command += domain;
        optionLabel->setText("Max Hops:");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
    } else if (option == "-f : Start from the first TTL hop") {
        command += "-f ";
        if (!optionValue.isEmpty()) {
            command += optionValue + " ";
        }
        command += domain;
        optionLabel->setText("Start TTL:");
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
    } else if (option == "-F : Do not fragment packet") {
        command += "-F ";
        command += domain;
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    }

    commandDisplay->setText(command);
}
