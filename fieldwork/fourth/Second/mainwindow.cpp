#include "mainwindow.h"
#include"ui_mainwindow.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("第二题:村庄修路");
    initGUI();

    mapWidget=new SMapWidget(this);
    ui->mapArea->setWidget(mapWidget);
    connect(this,SIGNAL(sig_startPaint()),this->mapWidget,SLOT(startPaint()));


    //
    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(60);  //设置窗体的标题栏高度
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
//    catPic=new QLabel(this);
//    catPic->setPixmap(QPixmap(":/img/res/redCat.png"));
//    catPic->setScaledContents(true);

    ui->maximizeButton->setIcon(QIcon(":/img/res/maximize-button1.png"));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QImage backgroundImage(QStringLiteral(":/img/res/background.png"));
    painter.drawImage(rect(), backgroundImage);

    painter.setPen(QColor(237, 212, 0));
    painter.setBrush(QBrush(QColor(237, 212, 0),Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,this->width(),26);
    painter.end();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

    if(event->y()<26&&event->button()==Qt::LeftButton){
        if(isFullScreen()){
            showNormal();
            ui->maximizeButton->setIcon(QIcon(":/img/res/maximize-button1.png"));
        }else{
            showFullScreen();
            ui->maximizeButton->setIcon(QIcon(":/img/res/maximize-button2.png"));
        }
    }

}



void MainWindow::on_maximizeButton_clicked()
{
    if(isFullScreen()){
        showNormal();
        ui->maximizeButton->setIcon(QIcon(":/img/res/maximize-button1.png"));
    }else{
        showFullScreen();
        ui->maximizeButton->setIcon(QIcon(":/img/res/maximize-button2.png"));
    }

}
