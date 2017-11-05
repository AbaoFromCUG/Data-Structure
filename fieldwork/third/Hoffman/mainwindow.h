#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QLabel>
#include<QThread>
#include<QPainter>
#include<QTime>
#include<QMessageBox>
#include<QMouseEvent>
#include<QDebug>
#include<QFile>
#include<QMessageBox>
#include<QTimer>
#include<QFileInfo>
#include<QFileDialog>
#include"lib/framlessHelper/qwidget/framelesshelper.h"
#include<QThread>
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
    void getFile(QString fileName);

signals:

private:
    Ui::MainWindow* ui;


};

#endif // MAINWINDOW_H
