#include "dig.h"
#include <QVBoxLayout>
#include <QtConcurrent>

DigTool::DigTool(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::dig)
{
    ui->setupUi(this);
    resize(800, 650);

    domainInput = new QLineEdit(this);
    domainInput->setPlaceholderText("Enter domain");

    digButton = new QPushButton("Dig", this);
    clearButton = new QPushButton("Clear", this);
    outputArea = new QTextEdit(this);

    connect(digButton, &QPushButton::clicked, this, &DigTool::onDigButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &DigTool::onClearButtonClicked);

    connect(domainInput, &QLineEdit::returnPressed, this, &DigTool::onDigButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(digButton);
    layout->addWidget(clearButton);
    layout->addWidget(outputArea);

    setLayout(layout);

    setWindowTitle("Dig Tool");
    outputArea->setReadOnly(true);
}

DigTool::~DigTool()
{
    delete ui;
}

bool DigTool::isValidInput(const QString &input)
{
    static QRegularExpression domainPattern(
        R"(^([a-zA-Z0-9-]+\.){1,}[a-zA-Z]{2,}$)");

    return domainPattern.match(input).hasMatch();
}

void DigTool::onDigButtonClicked()
{
    outputArea->clear();
    outputArea->append("Querying... Please wait.");

    QString domain = domainInput->text();

    if (isValidInput(domain))
    {
        // Start dig process asynchronously
        QFuture<void> future = QtConcurrent::run([=]() {
            QProcess digProcess;

            QString command = "dig " + domain;
            digProcess.start("dig", QStringList() << domain);
            digProcess.waitForFinished();

            QString result = digProcess.readAllStandardOutput();

            // Update GUI in the main thread
            QMetaObject::invokeMethod(this, "updateOutput", Qt::QueuedConnection,
                                      Q_ARG(QString, result));
        });
    }
    else
    {
        outputArea->append("Enter a valid Domain Name");
    }
}

void DigTool::updateOutput(const QString& result)
{
    // Remove the "Querying..." message
    outputArea->clear();

    // Append the actual dig result
    outputArea->append(result);
}

void DigTool::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
}
