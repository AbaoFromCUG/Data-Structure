#include "mainwindow.h"
#include"ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowTitle("大数阶乘");
    initGUI();

    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(26);  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放

}

MainWindow::~MainWindow()
{
}

void MainWindow::initGUI()
{

    ui->maximizeButton->setIcon(QIcon(":/res/maximize-button1.png"));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QImage backgroundImage(QStringLiteral(":/res/background.png"));
    painter.drawImage(rect(), backgroundImage);

    painter.setPen(QColor(255, 205, 65));
    painter.setBrush(QBrush(QColor(255, 205, 65),Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,this->width(),26);
    painter.end();

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

    if(event->y()<26&&event->button()==Qt::LeftButton){
        if(isFullScreen()){
            showNormal();
            ui->maximizeButton->setIcon(QIcon(":/res/maximize-button1.png"));
        }else{
            showFullScreen();
            ui->maximizeButton->setIcon(QIcon(":/res/maximize-button2.png"));
        }
    }

}

void MainWindow::on_maximizeButton_clicked()
{
    if(isFullScreen()){
        showNormal();
        ui->maximizeButton->setIcon(QIcon(":/res/maximize-button1.png"));
    }else{
        showFullScreen();
        ui->maximizeButton->setIcon(QIcon(":/res/maximize-button2.png"));
    }

}

void MainWindow::on_pushButton_clicked()
{
    QThread * thread=new QThread(this);
    Hoffman* workman=new Hoffman();
    connect(thread,&QThread::destroyed,workman,&Hoffman::deleteLater);
    connect(workman,&Hoffman::zipSuccess,[=](){
        thread->wait();
        thread->quit();
    });
    workman->moveToThread(thread);
    connect(this,SIGNAL(startZip(QString,QString )),workman,SLOT(startZip(QString,QString)));
    thread->start();
    emit startZip("/home/abao/Desktop/42737475_xl.jpg","/home/abao/Desktop/test.zip");

}
