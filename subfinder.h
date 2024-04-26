#ifndef SUBFINDER_H
#define SUBFINDER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>

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
    void updateOutput(const QString &result);

private:
    Ui::Subfinder *ui;
    QLineEdit *domainInput;
    QPushButton *findButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QProcess *subfinderProcess;

    bool isValidInput(const QString &input);
};

#endif // SUBFINDER_H
