#ifndef NMAP_H
#define NMAP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>
#include <QComboBox>

namespace Ui {
class nmap;
}

class Nmap : public QWidget
{
    Q_OBJECT

public:
    explicit Nmap(QWidget *parent = nullptr);
    ~Nmap();

private slots:
    void onClearButtonClicked();
    void onLoadButtonClicked();
    void executeCommand();
    void updateCommandOutput(const QString& result);

private:
    Ui::nmap *ui;
    QLineEdit *targetInput;
    QLineEdit *passwordInput;
    QPushButton *scanButton;
    QPushButton *clearButton;
    QPushButton *loadCmdButton; // New load button
    QTextEdit *outputArea;
    QLineEdit *commandDisplay;  // New command display box
    QComboBox *modeComboBox;    // New combo box for scan modes
    QProcess *scanProcess;

    bool isValidInput(const QString &input);
    QLineEdit* createLineEdit(const QString& placeholder);
    QPushButton* createButton(const QString& text);
    QComboBox* createComboBox(const QStringList& items);
};

#endif // NMAP_H
