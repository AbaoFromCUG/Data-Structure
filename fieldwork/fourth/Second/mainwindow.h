#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include<QLabel>
#include<QMouseEvent>
#include<QPainter>
#include<QFileDialog>
#include<QMessageBox>
#include<QStandardPaths>
#include<QThread>
#include"lib/struct/kmintree.h"
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
    void timerEvent(QTimerEvent *event);
private slots:
    void on_maximizeButton_clicked();


    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pixMap;
    QLabel* pixLabel;

    AMMap<QString>* m_minMap;
    QPoint m_pointMap[7];
    int m_rectW=100;
    int m_rectH=50;
    int m_status;
    KMinTree m_map;
    QList<MinEdge> getEdgeFromMinMap();
    void drawRect(QString str,QPoint p);
    void drawLine(int i,int j,QString name);
    void initPointMap();


};

#endif // MAINWINDOW_H
