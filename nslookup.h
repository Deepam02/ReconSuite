#ifndef NSLOOKUP_H
#define NSLOOKUP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>

namespace Ui {
class nslookup;
}

class nslookup : public QWidget
{
    Q_OBJECT

public:
    explicit nslookup(QWidget *parent = nullptr);
    ~nslookup();

private slots:
    void onLookupButtonClicked();
    void onClearButtonClicked();
    void updateOutput(const QString &result);

private:
    Ui::nslookup *ui;
    QLineEdit *inputField;
    QPushButton *lookupButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QProcess *nslookupProcess;

    bool isValidInput(const QString &input);
};

#endif // NSLOOKUP_H
