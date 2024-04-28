#ifndef PING_H
#define PING_H

#include <QComboBox>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

namespace Ui {
class ping;
}

class ping : public QWidget
{
    Q_OBJECT

public:
    explicit ping(QWidget *parent = nullptr);
    ~ping();

private slots:
    void onClearButtonClicked();
    void updateOutput(const QString &result);
    void onModeChanged(int index);
    void executeCommand();
    void updateCommandDisplay();

private:
    Ui::ping *ui;
    QLineEdit *domainInput;
    QPushButton *pingButton;
    QPushButton *clearButton;
    QLineEdit *packetCountInput;
    QTextEdit *outputArea;
    QComboBox *modeComboBox;
    QLineEdit *commandDisplay;

    void setupUI();
    void setupConnections();
    void setLayoutAndTitle();
    QLineEdit *createLineEdit(const QString &placeholder);
    QPushButton *createButton(const QString &text);
    QComboBox *createComboBox(const QStringList &items);
    bool isValidInput(const QString &input);
    void standardMode();
    void verboseMode();
    void floodingMode();
};

#endif // PING_H
