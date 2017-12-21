#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include<QPainter>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QGraphicsScene>
#include<QStandardPaths>
#include<QFileDialog>
#include<QGraphicsItem>
#include"mapprofilereader.h"
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
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    QString getLogTime();
    void refresh();
private slots:
    void on_maximizeButton_clicked();


    void on_pushButton_clicked();


    void on_findWay_clicked();

    void on_refresh_clicked();

private:
    Ui::MainWindow *ui;

signals:





};

#endif // MAINWINDOW_H
