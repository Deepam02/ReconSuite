#ifndef DIG_H
#define DIG_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QProcess>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class dig; }
QT_END_NAMESPACE

class dig : public QWidget
{
    Q_OBJECT

public:
    dig(QWidget *parent = nullptr);
    ~dig();

private:
    Ui::dig *ui;

    QLineEdit *domainInput;
    QLineEdit *optionInput;
    QLabel *optionLabel;
    QPushButton *digButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QComboBox *modeComboBox;
    QLineEdit *commandDisplay;

    QLineEdit *createLineEdit(const QString &placeholder);
    QPushButton *createButton(const QString &text);
    QComboBox *createComboBox(const QStringList &items);
    bool isValidInput(const QString &input);

private slots:
    void setupUI();
    void setupConnections();
    void setLayoutAndTitle();
    void onClearButtonClicked();
    void executeCommand();
    void updateCommandOutput(const QString &result);
    void onModeChanged(int index);
    void updateCommandDisplay();
};

#endif // DIG_H
