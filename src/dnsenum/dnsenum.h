#ifndef DNSENUM_H
#define DNSENUM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class dnsenum; }
QT_END_NAMESPACE

class dnsenum : public QWidget
{
    Q_OBJECT

public:
    explicit dnsenum(QWidget *parent = nullptr);
    ~dnsenum();

private:
    Ui::dnsenum *ui;

    QLineEdit *domainInput;
    QComboBox *modeComboBox;
    QLineEdit *commandDisplay;
    QPushButton *enumerateButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;

    QLineEdit *createLineEdit(const QString &placeholder);
    QPushButton *createButton(const QString &text);
    QComboBox *createComboBox(const QStringList &items);

private slots:
    void setupUI();
    void setupConnections();
    void setLayoutAndTitle();
    void updateCommandDisplay();
    void executeCommand();
    void onClearButtonClicked();
    void updateCommandOutput(const QString &result);
};

#endif // DNSENUM_H
