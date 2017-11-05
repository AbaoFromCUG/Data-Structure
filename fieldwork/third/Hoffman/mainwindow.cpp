#include "mainwindow.h"
#include"ui_mainwindow.h"
#include"encodedialog.h"
#include"decodedialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowTitle("霍夫曼牌压缩软件");
    initGUI();
    connect(ui->fileWidget,FileCoverDialog::signal_getFile,this,MainWindow::getFile);

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
    QImage backgroundImage(QString(":/res/background.png"));
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

void MainWindow::getFile(QString fileName)
{

    int ret=QMessageBox::question(this,
                          tr("choose"),
                          tr("请选择进行压缩还是解压，yes代表压缩，No代表解压"),
                          QMessageBox::Yes | QMessageBox::No|QMessageBox::Cancel,
                          QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Yes:
    {
        EnCodeDialog* dialog=new EnCodeDialog(this);
        dialog->exec();
        break;
    }
    case QMessageBox::No:
    {
        DeCodeDialog* dialog=new DeCodeDialog(this);
        dialog->exec();
        break;
    }
    case QMessageBox::Cancel:
    {
        break;
    }
    default:
        break;
    }
    QTimer::singleShot(0,ui->fileWidget,&FileCoverDialog::setNormalStatus);
}
