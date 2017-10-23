#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QPainter>
#include<QDebug>
#include<QClipboard>
#include<QLabel>
#include<QMouseEvent>
#include<QScrollBar>
#include<QPixmap>
#include<math.h>
#include"lib/framlessHelper/qwidget/framelesshelper.h"
#include"struct/CharTree.h"
#include"struct/myQueue.h"
#include"loghelper.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);



public slots:
private slots:

    void on_maximizeButton_clicked();

    void on_btn_log_clicked();

    void on_btn_parst_clicked();   //粘贴按钮

    void on_btn_front_clicked(); //前序生成二叉树的按钮

    void on_btn_layout_clicked();

    void on_btn_find_clicked();

    void on_btn_swap_clicked();

    void on_btn_refrer_clicked();

    void on_btn_saveImg_clicked();
    void initPixmap();
    void updatePixmap();        //更新二叉树的图像
    void paintDirLine(QPoint start,QPoint end);
    void paintCircle(QPoint center,QChar c);
    //绘制子树,传入子树根节点的位置,以及根节点的层数
    void  paintSonTree(TreeNode<char>* node, int x,int l);
private:
    Ui::MainWindow *ui;
    LogHelper* logHelper;
    CharTree myTree;
    QPixmap pixMap;
    QLabel *picLabel;
    double circleR=15;
    int fontSize=15;
    int rootSpace=20;//根节点上方空出的位置
    int imgWidth=2000;
    int imgHeight=700;
    double rowSpace=100;
    double columnSpace[6]={500,250,125,62.5,31,16};
protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

};

#endif // MAINWINDOW_H
