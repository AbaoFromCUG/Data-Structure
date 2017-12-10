#include "mainwindow.h"
#include"ui_mainwindow.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("校园导航");
    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(60);  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放


    //我的逻辑代码
    m_scene=new QGraphicsScene(this);

    ui->graphicsView->setScene(m_scene);
    m_scene->addText("Text");

}

MainWindow::~MainWindow()
{
}





void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //下面代码是绘制背景图片的代码
    QPainter painter(this);
    QImage backgroundImage(QStringLiteral(":/img/res/background.png"));
    painter.drawImage(rect(), backgroundImage);

    painter.setPen(QColor(50, 177, 122));
    painter.setBrush(QBrush(QColor(50, 177, 122),Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,this->width(),26);
    painter.end();

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    //下面是对标题栏双击的全屏的响应函数
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

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Image"),QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0], tr("Image Files (*.png *.jpg *.tif)"));
    QImage img(fileName);
    m_scene->addPixmap(QPixmap::fromImage(img));
}
