#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QProcess>
#include <QElapsedTimer>
#include <QtConcurrent>

QT_BEGIN_NAMESPACE
namespace Ui { class traceroute; }
QT_END_NAMESPACE

class traceroute : public QWidget
{
    Q_OBJECT

public:
    traceroute(QWidget *parent = nullptr);
    ~traceroute();

private:
    Ui::traceroute *ui;
    QLineEdit *domainInput;
    QLineEdit *optionInput;
    QLabel *optionLabel;
    QPushButton *traceButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QComboBox *modeComboBox;
    QLineEdit *commandDisplay;
    QCheckBox *tcpCheckbox;
    QLineEdit *portInput;

    void setupUI();
    void setupConnections();
    void setLayoutAndTitle();
    QLineEdit *createLineEdit(const QString &placeholder);
    QPushButton *createButton(const QString &text);
    QComboBox *createComboBox(const QStringList &items);
    bool isValidInput(const QString &input);
    void updateCommandOutput(const QString &result);
    void onModeChanged(int index);
    void updateCommandDisplay();
    void updateOutput(const QString &result);
    void onClearButtonClicked();
    void executeCommand();

};

#endif // TRACEROUTE_H
