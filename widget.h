#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>

QT_BEGIN_NAMESPACE
namespace Ui {
class widget;
}
QT_END_NAMESPACE

class widget : public QMainWindow
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private:
    Ui::widget *ui;
    QWidget *currentScreen;


    // Declare the setupToolScreen method
    void setupToolScreen(QWidget *toolScreen);

private slots:

    void on_actionPing_triggered();
    void on_actionNmap_triggered();
    void on_actionTraceroute_triggered();
    void on_actionSubfinder_triggered();
    void on_actionDig_triggered();
    void on_actionWhois_triggered();
    void on_actionDnsenum_triggered();
    void on_actionFfuf_triggered();
};

#endif // WIDGET_H
