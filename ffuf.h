#ifndef FFUF_H
#define FFUF_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>

namespace Ui {
class ffuf;
}

class ffuf : public QWidget
{
    Q_OBJECT

public:
    explicit ffuf(QWidget *parent = nullptr);
    ~ffuf();

private slots:
    void browseWordlist();
    void generateCommand();
    void startBruteForce();

private:
    Ui::ffuf *ui;

    QLineEdit *urlInput;
    QLineEdit *wordlistInput;
    QTextEdit *commandOutput;
    QPushButton *browseButton;
    QPushButton *generateButton;
    QPushButton *startButton;

    QString generatedCommand;

    void setupUiElements();
    void executeCommand(const QString &command);
};

#endif // FFUF_H
