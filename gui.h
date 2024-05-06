#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>

class GUI : public QWidget {
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel *label;
    QPushButton *quitButton;
    QDateTime lastActivityTime;
    QTimer *idleTimer;

    void updateActivityTime();
    void checkIdle();
};

#endif // GUI_H
