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
    domainInput = createLineEdit("Enter domain");
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
                                   "+nssearch: Mail server for your domain"});
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
    connect(domainInput, &QLineEdit::returnPressed, this, &dig::executeCommand);
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
    connect(domainInput,
            &QLineEdit::textChanged,
            this,
            &dig::updateCommandDisplay);
}

void dig::setLayoutAndTitle(){
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(modeComboBox);
    layout->addWidget(domainInput);
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

void dig::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    optionInput->clear();
    commandDisplay->clear();
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

void dig::updateCommandOutput(const QString &result)
{
    outputArea->append(result);
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
        optionLabel->setVisible(true);
        optionInput->setVisible(true);
        break;
    default:
        break;
    }
    updateCommandDisplay(); // Update the command display based on the mode change
}

void dig::updateCommandDisplay()
{
    QString domain = domainInput->text();
    QString option = modeComboBox->currentText();
    QString optionValue = optionInput->text();
    QString command = "dig ";

    if (option == "Standard Mode") {
        command += domain;
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "NS : To find name servers") {
        command += "NS " + domain;
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "+trace: Delegation path to your DNS Zone") {
        command += domain + " +trace";
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    } else if (option == "+nssearch: Mail server for your domain") {
        command += domain + " +nssearch";
        optionLabel->setVisible(false);
        optionInput->setVisible(false);
    }

    commandDisplay->setText(command);
}
