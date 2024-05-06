#include "gui.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QApplication>

GUI::GUI(QWidget *parent) : QWidget(parent) {
    lastActivityTime = QDateTime::currentDateTime();

    // Create GUI elements
    label = new QLabel("Welcome to CLI Tool GUI");
    quitButton = new QPushButton("Quit");
    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit); // Corrected

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(quitButton);

    // Timer for checking idle time
    idleTimer = new QTimer(this);
    connect(idleTimer, &QTimer::timeout, this, &GUI::checkIdle);
    idleTimer->start(1000); // Check every second
}

void GUI::mouseMoveEvent(QMouseEvent *event) {
    updateActivityTime();
    QWidget::mouseMoveEvent(event);
}

void GUI::keyPressEvent(QKeyEvent *event) {
    updateActivityTime();
    QWidget::keyPressEvent(event);
}

void GUI::updateActivityTime() {
    lastActivityTime = QDateTime::currentDateTime();
}

void GUI::checkIdle() {
    QDateTime currentTime = QDateTime::currentDateTime();
    int idleTime = lastActivityTime.secsTo(currentTime);

    // Set the time limit for idle (in seconds)
    int idleLimit = 300; // 5 minutes

    if (idleTime >= idleLimit) {
        // Handle idle timeout, e.g., display a message or reset the GUI
        qDebug() << "Idle timeout reached. Resetting GUI.";
        // Reset the GUI or take necessary action here
        // For example, you can reset the GUI by closing and reopening it
        close();
        QApplication::quit();
    }
}
