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
    void executeCommand();
    void updateCommandOutput(const QString& result);
    void updateCommandDisplay();

private:
    Ui::nmap *ui;
    QLineEdit *targetInput;
    QPushButton *scanButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QLineEdit *commandDisplay;
    QComboBox *modeComboBox;

    bool isValidInput(const QString &input);
    QLineEdit* createLineEdit(const QString& placeholder);
    QPushButton* createButton(const QString& text);
    QComboBox* createComboBox(const QStringList& items);
    void initializeUI();
    void connectSignalsSlots();
};

#endif // NMAP_H
