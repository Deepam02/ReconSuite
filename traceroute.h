#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>

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

private:
    Ui::traceroute *ui;
    QLineEdit *domainInput;
    QPushButton *traceButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QProcess *traceProcess;

    bool isValidInput(const QString &input);
};

#endif // TRACEROUTE_H
