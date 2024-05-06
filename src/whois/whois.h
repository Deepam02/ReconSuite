#ifndef WHOIS_H
#define WHOIS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>

class whois : public QWidget {
    Q_OBJECT

public:
    whois(QWidget *parent = nullptr);

public slots:
    void initUI(); // Declaration of initUI function

private slots:
    void runwhois();
    QString simplifyOutput(const QString& output);

private:
    QLabel *domainLabel;
    QLineEdit *domainInput;
    QLabel *outputLabel;
    QTextEdit *outputText;

    QPushButton *searchButton;
};

#endif // WHOIS_H
