#ifndef DIG_H
#define DIG_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QProcess>
#include <QElapsedTimer>
#include <QIntValidator>
#include <QtConcurrent>

QT_BEGIN_NAMESPACE
namespace Ui { class dig; }
QT_END_NAMESPACE

class dig : public QWidget
{
    Q_OBJECT

public:
    dig(QWidget *parent = nullptr);
    ~dig();

private slots:
    void onClearButtonClicked();
    void executeCommand();
    void onModeChanged();
    void updateCommandDisplay();

private:
    Ui::dig *ui;
    QLineEdit *domainInput;
    QLineEdit *optionInput; // Add this line
    QLabel *optionLabel;
    QLineEdit *optionValue;
    QPushButton *digButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QComboBox *modeComboBox;
    QLineEdit *commandDisplay;
    QLineEdit *createLineEdit(const QString &placeholder);
    QPushButton *createButton(const QString &text);
    QComboBox *createComboBox(const QStringList &items);
    bool isValidInput(const QString &input);
    void setLayoutAndTitle();
    void setupUI();
    void setupConnections();
    void updateCommandOutput(const QString &result);
};

#endif // DIG_H
