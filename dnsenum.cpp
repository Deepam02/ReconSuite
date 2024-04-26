#include "dnsenum.h"
#include "ui_dnsenum.h"
#include <QVBoxLayout>

Dnsenum::Dnsenum(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::dnsenum)
{
    ui->setupUi(this);
    resize(800, 650);

    domainInput = new QLineEdit(this);
    domainInput->setPlaceholderText("Enter domain name");

    runButton = new QPushButton("Run", this);
    clearButton = new QPushButton("Clear", this);
    outputArea = new QTextEdit(this);
    dnsenumProcess = new QProcess(this);

    connect(runButton, &QPushButton::clicked, this, &Dnsenum::onRunButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &Dnsenum::onClearButtonClicked);

    connect(domainInput, &QLineEdit::returnPressed, this, &Dnsenum::onRunButtonClicked);

    connect(dnsenumProcess, &QProcess::readyReadStandardOutput, [=]() {
        outputArea->append(dnsenumProcess->readAllStandardOutput());
    });

    connect(dnsenumProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                outputArea->append("\nDNS enumeration finished with exit code: " + QString::number(exitCode));
                runButton->setEnabled(true);
            });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(runButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);

    setLayout(layout);

    setWindowTitle("DNS Enumeration Tool");
    outputArea->setReadOnly(true);
}

Dnsenum::~Dnsenum()
{
    delete ui;
}

bool Dnsenum::isValidInput(const QString &input)
{
    return !input.isEmpty();
}

void Dnsenum::onRunButtonClicked()
{

    outputArea->clear();

    QString domain = domainInput->text();

    if (isValidInput(domain))
    {
        QStringList enumArguments;
        enumArguments << domain;
        dnsenumProcess->start("dnsenum", enumArguments);
    }
    else
    {
        outputArea->append("Enter a valid domain name");

    }
}

void Dnsenum::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
}
