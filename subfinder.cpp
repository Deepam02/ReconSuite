#include "subfinder.h"
#include "ui_subfinder.h"
#include <QRegularExpression>
#include <QVBoxLayout>

Subfinder::Subfinder(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Subfinder)
{
    ui->setupUi(this);
    resize(800, 650);

    domainInput = new QLineEdit(this);
    domainInput->setPlaceholderText("Enter domain");

    findButton = new QPushButton("Find Subdomains", this);
    clearButton = new QPushButton("Clear", this);
    outputArea = new QTextEdit(this);
    commandDisplay = new QLineEdit(this);
    commandDisplay->setPlaceholderText("command will be displayed here");
    subfinderProcess = new QProcess(this);

    connect(findButton, &QPushButton::clicked, this, &Subfinder::onFindButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &Subfinder::onClearButtonClicked);

    connect(domainInput, &QLineEdit::returnPressed, this, &Subfinder::onFindButtonClicked);

    connect(subfinderProcess, &QProcess::readyReadStandardOutput, [=]() {
        outputArea->append(subfinderProcess->readAllStandardOutput());
    });

    connect(subfinderProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nSubfinder command finished with exit code: " + QString::number(exitCode));
                findButton->setDisabled(false);
            });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(findButton);
    layout->addWidget(clearButton);
    layout->addWidget(commandDisplay);
    layout->addWidget(outputArea);

    setLayout(layout);
    setWindowTitle("Subfinder Tool");
    outputArea->setReadOnly(true);
}

Subfinder::~Subfinder()
{
    delete ui;
}

bool Subfinder::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(
        R"(^(?:(?:https?|ftp):\/\/)?(?:www\.)?([a-zA-Z0-9-]+(?:\.[a-zA-Z]{2,})+|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(?:\/[^\s]*)?$)"
        );

    return domainPattern.match(input).hasMatch();
}

QString runSubfinder(const QString& domain) {
    QString command = "subfinder -d " + domain;
    QProcess subfinderProcess;
    subfinderProcess.start("subfinder", QStringList() << "-d" << domain);
    subfinderProcess.waitForFinished();

    return subfinderProcess.readAllStandardOutput();
}

void Subfinder::onFindButtonClicked()
{
    outputArea->clear();
    outputArea->append("Finding subdomains... Please wait.");

    QString domain = domainInput->text();

    if (isValidInput(domain))
    {

        QString result = runSubfinder(domain);
        updateOutput(result);
    }
    else
    {
        outputArea->append("Enter a valid Domain or IP Address");
    }
}

void Subfinder::updateOutput(const QString& result)
{
    // Remove the "Finding subdomains..." message
    outputArea->clear();

    // Append the actual subfinder result
    outputArea->append(result);
}

void Subfinder::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
}
