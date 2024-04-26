#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

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

    // Declare the createButton method
    QPushButton* createButton(int row, int col);

    // Declare the setupToolScreen method
    void setupToolScreen(QWidget *toolScreen);

private slots:
    void onButtonClicked(int row, int col);
};

#endif // WIDGET_H
