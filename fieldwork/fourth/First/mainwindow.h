#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QWidget>
#include<QPainter>
#include<QMouseEvent>
#include<QLabel>
#include<QMessageBox>
#include<QDebug>

#include"lib/struct/ammap.h"
#include"lib/struct/undir_admap.h"
#include"lib/logHelper/loghelper.h"
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

    void on_addPointBtn_clicked();

    void on_changePointBtn_clicked();

    void on_addLineBtn_clicked();

    void on_changeLineBtn_clicked();

    void on_DFS_clicked();

    void on_BFS_clicked();

    void on_newMap_clicked();

signals:

private:
    Ui::MainWindow *ui;
    LogHelper* log;
//    QLabel *catPic;
    Undir_ADMap<double,double>* map;


//    int m_type;
//    /* 0代表为初始化
//     * 1代表边为double的矩阵
//     * 2代表边为string 的矩阵
//     * 3代表边为double，顶点为double 的领接表
//     * ４代表边为double, 顶点为string 的邻接表
//     * 5代表边为string,顶点为double 的领接表
//     * ６代表边为string，顶点为string 的领接表
//     */

};

#endif // MAINWINDOW_H
