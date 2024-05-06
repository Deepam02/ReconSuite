#include "subfinder.h"
#include "ui_subfinder.h"
#include <QVBoxLayout>
#include <QRegularExpressionValidator>
#include <QComboBox>
#include <QProcess>
#include <QElapsedTimer>
#include <QtConcurrent>

Subfinder::Subfinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subfinder)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    setLayoutAndTitle();
}

Subfinder::~Subfinder()
{
    delete ui;
}

void Subfinder::setupUI()
{
    domainInput = createLineEdit("Enter domain");
    findButton = createButton("Find Subdomains");
    clearButton = createButton("Clear");
    outputArea = new QTextEdit(this);
    commandDisplay = createLineEdit("Command will be displayed here");

    modeComboBox = new QComboBox(this);
    modeComboBox->addItem("Standard Mode");
    modeComboBox->addItem("Brute Force Mode");
    modeComboBox->addItem("Recursive Mode");
    modeComboBox->addItem("Custom DNS Servers Mode");
    modeComboBox->addItem("Output Formatting Options");
}

void Subfinder::setupConnections()
{
    connect(findButton, &QPushButton::clicked, this, &Subfinder::onFindButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &Subfinder::onClearButtonClicked);
    connect(domainInput, &QLineEdit::textChanged, this, &Subfinder::updateCommandDisplay);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Subfinder::onModeChanged);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Subfinder::updateCommandDisplay);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &Subfinder::executeCommand);
}

void Subfinder::setLayoutAndTitle()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(modeComboBox);
    layout->addWidget(findButton);
    layout->addWidget(clearButton);
    layout->addWidget(commandDisplay);
    layout->addWidget(outputArea);
    setLayout(layout);
    setWindowTitle("Subfinder Tool");
    outputArea->setReadOnly(true);
}

QLineEdit *Subfinder::createLineEdit(const QString &placeholder)
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

QPushButton *Subfinder::createButton(const QString &text)
{
    return new QPushButton(text, this);
}

void Subfinder::onFindButtonClicked()
{
    QString domain = domainInput->text();
    if (isValidInput(domain))
    {
        QString command = generateCommand();
        commandDisplay->setText(command);
        executeCommand();
    }
    else
    {
        outputArea->append("Enter a valid Domain or IP Address");
    }
}

void Subfinder::executeCommand()
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


void Subfinder::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    commandDisplay->clear();
}

void Subfinder::updateCommandDisplay()
{
    QString command = generateCommand();
    commandDisplay->setText(command);
}

void Subfinder::updateCommandOutput(const QString &result)
{
    outputArea->append(result);
}

QString Subfinder::generateCommand()
{
    QString domain = domainInput->text();
    QString mode = modeComboBox->currentText();
    QString command = "subfinder -d " + domain;

    if (mode == "Brute Force Mode") {
        command += " -b";
    } else if (mode == "Recursive Mode") {
        command += " -r";
    } else if (mode == "Custom DNS Servers Mode") {
        command += " -dns <custom_dns_server>";
    } else if (mode == "Output Formatting Options") {
        // Add options for output formatting (JSON, CSV, plaintext, etc.)
        // Example: command += " -o json";
    }

    return command;
}

bool Subfinder::isValidInput(const QString &input)
{
    QRegularExpressionValidator validator(QRegularExpression("^(?:https?://)?(?:www\\.)?[^\\s/$.?#].[^\\s]*$"));
    int pos = 0;
    QString inputCopy = input;
    if (validator.validate(inputCopy, pos) == QValidator::Acceptable)

        return true;
    else
        return false;
}

void Subfinder::onModeChanged(int index)
{
    Q_UNUSED(index);
}
