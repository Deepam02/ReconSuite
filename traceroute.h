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

class traceroute : public QWidget{
    Q_OBJECT

public:
    explicit traceroute(QWidget *parent = nullptr);
    ~traceroute();
    void updateCommandOutput(const QString& result);

public slots:
    void onModeChanged(int index);


private slots:
    void onClearButtonClicked();
    void executeCommand();
    void updateOutput(const QString &result);
    void updateCommandDisplay();

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

    bool isValidInput(const QString &input);
    QString traceSystem(const QString& host, const QString& option, const QString& optionValue);
    QLineEdit* createLineEdit(const QString& placeholder);
    QPushButton* createButton(const QString& text);
    QComboBox* createComboBox(const QStringList& items);
    void setupUI();
    void setupConnections();
    void setLayoutAndTitle();
};

#endif // TRACEROUTE_H
