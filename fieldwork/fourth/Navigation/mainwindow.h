#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include<QPainter>
#include<QPaintEvent>
#include<QMouseEvent>
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
private slots:
    void on_maximizeButton_clicked();


private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
