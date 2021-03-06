#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"list/LargeFactorial.h"
#include<QLabel>
#include<QThread>
#include<QPainter>
#include<QTime>
#include<QMessageBox>
#include<QMouseEvent>
#include<QDebug>
#include<QFile>
#include<QFileInfo>
#include<QFileDialog>
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

    QString getLogTime();
private slots:
    void on_maximizeButton_clicked();

    void on_fileBtn_clicked();

    void on_startBtn_clicked();
signals:

    void start(int length,int maxNum);
    void startSaveDate();    //开始
    void sendFileName(QString file);

private:
    Ui::MainWindow *ui;
    QLabel*catPic;
    QThread* runThread;
    QString fileName;
    LargeFactorial* list;
    /*
     * 如果为1，表示正常情况，工作线程没有在运算或文件读写
     * 如果为2，表示正在计算
     * 如果为3，表示已经计算完毕，震灾文件读写
     */
    int status;

};

#endif // MAINWINDOW_H
