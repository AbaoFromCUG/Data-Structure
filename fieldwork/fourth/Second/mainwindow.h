#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include<QLabel>
#include<QMouseEvent>
#include<QPainter>
#include"smapwidget.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void initGUI();
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void on_maximizeButton_clicked();


signals:
    void sig_startPaint();

private:
    Ui::MainWindow *ui;
    SMapWidget* mapWidget;


};

#endif // MAINWINDOW_H
