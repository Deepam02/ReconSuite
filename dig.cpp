#include "dig.h"
#include "ui_dig.h"
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QApplication>
#include <QtConcurrent>

dig::dig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dig)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    setLayoutAndTitle();
}

dig::~dig(){
    delete ui;
}

void dig::setupUI(){
    domainOrIpInput = createLineEdit("Enter domain or IP address"); // Changed name
    optionInput = createLineEdit("Option Value");
    optionLabel = new QLabel("Option:", this);
    optionLabel->setVisible(false);
    optionInput->setVisible(false);
    digButton = createButton("Dig");
    clearButton = createButton("Clear");
    outputArea = new QTextEdit(this);
    modeComboBox = createComboBox({"Select Mode",
                                   "Standard Mode",
                                   "NS : To find name servers",
                                   "+trace: Delegation path to your DNS Zone",
                                   "+nssearch: Mail server for your domain",
                                   "Reverse DNS Lookup"}); // Added new option
    commandDisplay = createLineEdit("Command will be displayed here");
}

void dig::setupConnections()
{
    connect(modeComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &dig::onModeChanged);
    connect(digButton, &QPushButton::clicked, this, &dig::executeCommand);
    connect(clearButton, &QPushButton::clicked, this, &dig::onClearButtonClicked);
    connect(domainOrIpInput, &QLineEdit::returnPressed, this, &dig::executeCommand); // Changed connection
    connect(modeComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &dig::updateCommandDisplay);
    connect(optionInput, &QLineEdit::returnPressed, this, &dig::executeCommand);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &dig::executeCommand);
    connect(optionInput,
            &QLineEdit::textChanged,
            this,
            &dig::updateCommandDisplay);
    connect(domainOrIpInput, // Changed connection
            &QLineEdit::textChanged,
            this,
            &dig::updateCommandDisplay);
}

void dig::setLayoutAndTitle(){
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainOrIpInput); // Changed name
    layout->addWidget(optionLabel);
    layout->addWidget(optionInput);
    layout->addWidget(commandDisplay);
    layout->addWidget(digButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("Dig Tool");
    outputArea->setReadOnly(true);
}

void dig::updateCommandDisplay()
{
    QString domainOrIp = domainOrIpInput->text(); // Changed name
    QString option = modeComboBox->currentText();
    QString optionValue = optionInput->text();
    QString command = "dig ";

    if (option == "Standard Mode") {
        command += domainOrIp; // Changed name
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "NS : To find name servers") {
        command += "NS " + domainOrIp; // Changed name
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "+trace: Delegation path to your DNS Zone") {
        command += domainOrIp + " +trace"; // Changed name
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "+nssearch: Mail server for your domain") {
        command += domainOrIp + " +nssearch"; // Changed name
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "-x: Reverse DNS Lookup") { // Added new option
        command += "-x " + domainOrIp; // Changed name
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    }

    commandDisplay->setText(command);
}

void dig::executeCommand()
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

        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        if (!error.isEmpty()) {
            updateCommandOutput("Error: " + error);
            return;
        }

        QStringList lines = output.split("\n");

        // Filtering lines to extract website names
        QStringList websites;
        foreach (const QString &line, lines) {
            if (line.contains("PTR")) {
                QString website = line.split("PTR")[1].trimmed();
                websites.append(website);
            }
        }

        if (websites.isEmpty()) {
            updateCommandOutput("No website found for the entered IP address.");
        } else {
            updateCommandOutput("Websites associated with the entered IP:");
            foreach (const QString &website, websites) {
                updateCommandOutput(website);
            }
        }

        // Adding time measurement using QElapsedTimer
        QString timeOutput = "Time taken: " + QString::number(timer.elapsed()) + " ms";
        updateCommandOutput(timeOutput);

        QApplication::restoreOverrideCursor();
    });
}


void dig::onModeChanged(int index)
{
    switch (index) {
    case 0:
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        break;
    default:
        break;
    }
    updateCommandDisplay(); // Update the command display based on the mode change
}

void dig::onClearButtonClicked()
{
    outputArea->clear();
    domainOrIpInput->clear(); // Changed name
    optionInput->clear();
    commandDisplay->clear();
}

QLineEdit *dig::createLineEdit(const QString &placeholder)
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton *dig::createButton(const QString &text)
{
    return new QPushButton(text, this);
}

QComboBox *dig::createComboBox(const QStringList &items)
{
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItems(items);
    return comboBox;
}

bool dig::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(
        R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)");
    return domainPattern.match(input).hasMatch();
}

void dig::updateCommandOutput(const QString &result){
    outputArea->append(result);
}
