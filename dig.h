#ifndef DIG_H
#define DIG_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>

// Include the generated UI header file
#include "ui_dig.h"

class DigTool : public QWidget
{
    Q_OBJECT

public:
    explicit DigTool(QWidget *parent = nullptr);
    ~DigTool();

private slots:
    void onDigButtonClicked();
    void onClearButtonClicked();
    void updateOutput(const QString &result);

private:
    Ui::dig *ui;  // Use the generated UI class
    QLineEdit *domainInput;
    QPushButton *digButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QProcess *digProcess;

    bool isValidInput(const QString &input);
};

#endif // DIG_H
