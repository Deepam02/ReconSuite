#include "whois.h"
#include <QVBoxLayout>
#include <QRegularExpression>

whois::whois(QWidget *parent) : QWidget(parent) {
    setWindowTitle("whois");
    initUI();
}

void whois::initUI() {
    QVBoxLayout *layout = new QVBoxLayout();

    // Input field for domain
    domainLabel = new QLabel("Enter Domain:");
    domainInput = new QLineEdit();
    layout->addWidget(domainLabel);
    layout->addWidget(domainInput);

    // Output field
    outputLabel = new QLabel("whois Information:");
    outputText = new QTextEdit();
    layout->addWidget(outputLabel);
    layout->addWidget(outputText);

    // Search button
    searchButton = new QPushButton("Search");
    connect(searchButton, &QPushButton::clicked, this, &whois::runwhois);
    layout->addWidget(searchButton);

    connect(domainInput, &QLineEdit::returnPressed, this, &whois::runwhois);

    setLayout(layout);
}

void whois::runwhois() {

    QString domain = domainInput->text();
    if (!domain.isEmpty()) {
        QProcess process;
        process.start("whois", QStringList() << domain);
        process.waitForFinished();
        QString whoisOutput = process.readAllStandardOutput();

        QString simplifiedOutput = simplifyOutput(whoisOutput);
        outputText->setPlainText(simplifiedOutput);
    }
}

QString whois::simplifyOutput(const QString& output) {
    QString simplifiedOutput;
    QRegularExpression regex("(Registrant.*\\n|Registrant Email.*\\n|Registrar.*\\n)");
    QRegularExpressionMatchIterator i = regex.globalMatch(output);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        simplifiedOutput.append(match.captured(0));
    }
    return simplifiedOutput;
}
