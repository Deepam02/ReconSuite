// traceroute.h

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>
#include <QComboBox>
#include <QLabel>

namespace Ui {
class traceroute;
}

class traceroute : public QWidget
{
    Q_OBJECT

public:
    explicit traceroute(QWidget *parent = nullptr);
    ~traceroute();

private slots:
    void onTraceButtonClicked();
    void onClearButtonClicked();
    void updateOutput(const QString &result);
    void updateCommand();
    void toggleOptionInput(bool state);

private:
    Ui::traceroute *ui;
    QLineEdit *domainInput;
    QPushButton *traceButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QProcess *traceProcess;
    QComboBox *commandComboBox;
    QLineEdit *optionInput;
    QLabel *optionLabel;

    bool isValidInput(const QString &input);
};

#endif // TRACEROUTE_H
