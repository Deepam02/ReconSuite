#ifndef FFUF_H
#define FFUF_H

#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QRegularExpression>

namespace Ui {
class ffuf;
}

class ffuf : public QWidget {
    Q_OBJECT

public:
    explicit ffuf(QWidget *parent = nullptr);
    ~ffuf();

private slots:
    void browseWordlist();
    void generateSubdomainCommand();
    void generateDirectoryCommand();
    void startBruteForce();

private:
    Ui::ffuf *ui;

    QLineEdit *urlInput;
    QLineEdit *wordlistInput;
    QTextEdit *commandOutput;
    QTextEdit *generatedCommandText;
    QPushButton *browseButton;
    QPushButton *generateSubdomainButton;
    QPushButton *generateDirectoryButton;
    QPushButton *startButton;
    QString generatedCommand;

    void setupUiElements();
    void executeCommand(const QString &command);
};

#endif // FFUF_H
