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


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* m_scene;



};

#endif // MAINWINDOW_H
