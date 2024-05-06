#include "subfinder.h"
#include "ui_subfinder.h"
#include <QVBoxLayout>
#include <QHBoxLayout> // Include for QHBoxLayout
#include <QRegularExpressionValidator>
#include <QComboBox>
#include <QProcess>
#include <QElapsedTimer>
#include <QtConcurrent>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QClipboard>


Subfinder::Subfinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subfinder)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    QString lastExecutionOutput = "";

}

void Subfinder::setupConnections()
{
    connect(findButton, &QPushButton::clicked, this, &Subfinder::onFindButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &Subfinder::onClearButtonClicked);
    connect(domainInput, &QLineEdit::textChanged, this, &Subfinder::updateCommandDisplay);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Subfinder::onModeChanged);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Subfinder::updateCommandDisplay);
    connect(commandDisplay, &QLineEdit::returnPressed, this, &Subfinder::executeCommand);
    connect(domainInput, &QLineEdit::returnPressed, this, &Subfinder::executeCommand);
    connect(copyOutputButton, &QPushButton::clicked, this, &Subfinder::onCopyOutputClicked);
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
    copyOutputButton = createButton("Copy Output");


    modeComboBox = new QComboBox(this);
    modeComboBox->addItem("Standard Mode");
    modeComboBox->addItem("Thorough Scan");
    modeComboBox->addItem("Fast & Thorough Scan");
    modeComboBox->addItem("Verbose Output");
    modeComboBox->addItem("Custom Mode");
    // Create checkboxes and add them to a horizontal layout
    QHBoxLayout *checkboxLayout = new QHBoxLayout;
    pingProbeCheckBox = createCheckBox("Active Subdomain Checker");
    silentOutputCheckBox = createCheckBox("Silent Output");
    allSourcesCheckBox = createCheckBox("All Sources");
    fastCheckBox = createCheckBox("Fast Scan");
    // Add more checkboxes as needed

    pingProbeCheckBox->setEnabled(false);
    silentOutputCheckBox->setEnabled(false);
    allSourcesCheckBox->setEnabled(false);
    fastCheckBox->setEnabled(false);

    checkboxLayout->addWidget(pingProbeCheckBox);
    checkboxLayout->addWidget(silentOutputCheckBox);
    checkboxLayout->addWidget(allSourcesCheckBox);
    checkboxLayout->addWidget(fastCheckBox);
    checkboxLayout->addWidget(copyOutputButton);

    // Add more checkboxes as needed

    // Create a vertical layout for the entire UI
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(domainInput);
    layout->addWidget(modeComboBox);
    layout->addLayout(checkboxLayout); // Add the checkbox layout
    layout->addWidget(findButton);
    layout->addWidget(clearButton);
    layout->addWidget(commandDisplay);
    layout->addWidget(outputArea);
    setLayout(layout);
    setWindowTitle("Subfinder Tool");
    outputArea->setReadOnly(true);
}

QCheckBox *Subfinder::createCheckBox(const QString &text)
{
    return new QCheckBox(text, this);
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

void Subfinder::onCopyOutputClicked()
{
    if (!lastExecutionOutput.isEmpty()) {
        QApplication::clipboard()->setText(lastExecutionOutput);
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


    QStringList args = command.split(" ");

    QtConcurrent::run([=]() {
        QProcess process;
        QElapsedTimer timer;
        timer.start();

        process.start(args[0], args.mid(1));
        process.waitForFinished();

        int exitCode = process.exitCode();
        QString output = process.readAllStandardOutput(); // Read output

        lastExecutionOutput = output; // Update lastExecutionOutput

        QString error = process.readAllStandardError();

        if (exitCode != 0)
        {
            updateCommandOutput("Command execution failed with exit code: " + QString::number(exitCode));
        }

        if (!error.isEmpty())
        {
            updateCommandOutput("Error: " + error);
        }

        QString mode = modeComboBox->currentText();
        if(mode=="Verbose Output"){
            // Move GUI operation to the main thread
            QMetaObject::invokeMethod(this, "showVerboseOutputAsTable", Qt::QueuedConnection, Q_ARG(QString, output));
        } else {
            // Move GUI operation to the main thread
            QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection, Q_ARG(QString, "Output:\n" + output));
        }

        // Adding time measurement using QElapsedTimer
        QString timeOutput = "Time taken: " + QString::number(timer.elapsed()) + " ms";
        // Move GUI operation to the main thread
        QMetaObject::invokeMethod(this, "updateCommandOutput", Qt::QueuedConnection, Q_ARG(QString, timeOutput));
    });
}


void Subfinder::showVerboseOutputAsTable(const QString& output)
{
    // Clear existing table data

    outputArea->clear();

    // Parse CSV data and display in a table
    QStringList rows = output.split('\n');
    QStringList header = {"Subdomain", "IP", "Source"};
    QList<QStringList> rowData;

    // Parsing remaining rows
    for (const QString& row : rows) {
        QStringList columns = row.split(',');
        rowData.append(columns);
    }

    // Create table widget
    QTableWidget* tableWidget = new QTableWidget(rowData.size(), header.size(), this);
    tableWidget->setHorizontalHeaderLabels(header);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Expand columns to fill the available space

    // Populate table with data
    for (int i = 0; i < rowData.size(); ++i) {
        const QStringList& rowDataList = rowData[i];
        for (int j = 0; j < rowDataList.size(); ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(rowDataList[j]);
            tableWidget->setItem(i, j, item);
        }
    }

    // Show table
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableWidget);
    outputArea->setLayout(layout);
}





void Subfinder::onClearButtonClicked()
{
    outputArea->clear();
    domainInput->clear();
    commandDisplay->clear();
    lastExecutionOutput="";
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

    if (mode == "Thorough Scan") {
        command += " -all";
    } else if (mode == "Fast & Thorough Scan") {
        command += " -all -r 8.8.8.8";
    } else if (mode == "Verbose Output") {
        command += " -ip -nW";
    } else{
        if(pingProbeCheckBox->isChecked()){
            command+=" -nW";
        }
        if(fastCheckBox->isChecked()){
            command+=" -r 8.8.8.8";
        }
        if(allSourcesCheckBox->isChecked()){
            command+=" -all";
        }
        if(silentOutputCheckBox->isChecked()){
            command+=" -silent";
        }
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
    QString mode = modeComboBox->currentText();
    if (!(mode =="Custom Mode")){
        pingProbeCheckBox->setEnabled(false);
        silentOutputCheckBox->setEnabled(false);
        allSourcesCheckBox->setEnabled(false);
        fastCheckBox->setEnabled(false);
    }
    else {
        pingProbeCheckBox->setEnabled(true);
        silentOutputCheckBox->setEnabled(true);
        allSourcesCheckBox->setEnabled(true);
        fastCheckBox->setEnabled(true);
    }
    Q_UNUSED(index);
}
