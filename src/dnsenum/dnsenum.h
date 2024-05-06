#ifndef DNSENUM_H
#define DNSENUM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>

namespace Ui {
class dnsenum;
}

class Dnsenum : public QWidget
{
    Q_OBJECT

public:
    explicit Dnsenum(QWidget *parent = nullptr);
    ~Dnsenum();

private slots:
    void onRunButtonClicked();
    void onClearButtonClicked();

private:
    Ui::dnsenum *ui;
    QLineEdit *domainInput;
    QPushButton *runButton;
    QPushButton *clearButton;
    QTextEdit *outputArea;
    QProcess *dnsenumProcess;

    bool isValidInput(const QString &input);
};

#endif // DNSENUM_H
