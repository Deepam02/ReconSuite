#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QTabWidget>
#include <QListWidget> // Include QListWidget header
#include "ui_widget.h"
#include <QSplitter>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QMainWindow
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    void on_actionPing_triggered();
    void on_actionNmap_triggered();
    void on_actionTraceroute_triggered();
    void on_actionSubfinder_triggered();
    void on_actionDig_triggered();
    void on_actionWhois_triggered();
    void on_actionDnsenum_triggered();
    void on_actionFfuf_triggered();

private:
    Ui::widget *ui;
    QTabWidget *tabWidget;
    QSplitter *splitter;

    void addToolTab(QWidget *toolWidget, const QString &label);
};

#endif // WIDGET_H
