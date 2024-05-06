#ifndef SUBFINDER_H
#define SUBFINDER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>
#include <QComboBox>

namespace Ui {
class Subfinder;
}

class Subfinder : public QWidget
{
    Q_OBJECT

public:
    explicit Subfinder(QWidget *parent = nullptr);
    ~Subfinder();

private slots:
    void onFindButtonClicked();
    void onClearButtonClicked();
    void executeCommand();
    void updateCommandDisplay();
    void onModeChanged(int index);
    void updateCommandOutput(const QString &result);

private:
    Ui::Subfinder *ui;
    QLineEdit *domainInput;
    QPushButton *findButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QLineEdit *commandDisplay;
    QComboBox *modeComboBox;

    QLineEdit *createLineEdit(const QString &placeholder);
    QPushButton *createButton(const QString &text);

    void setupUI();
    void setupConnections();
    void setLayoutAndTitle();
    QString generateCommand();
    bool isValidInput(const QString &input);
};

#endif // SUBFINDER_H
