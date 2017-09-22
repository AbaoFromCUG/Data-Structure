#include "mainwindow.h"
#include"ui_mainwindow.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowTitle("大数阶乘");
    initGUI();

    list=new LargeFactorial;
    runThread=new QThread(this);
    list->moveToThread(runThread);
    runThread->start();
    status=1;
    connect(this,&MainWindow::start,list,&LargeFactorial::start);
    connect(this,&MainWindow::sendFileName,list,&LargeFactorial::saveFilePath);

    //
    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(60);  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放


    connect(list,&LargeFactorial::ok,[=](int num){
        qDebug()<<"ok  "<<num;
        switch (num) {
        case 1:
            ui->time2->setText(QString("运算完成时间%1").arg(getLogTime()));
            status=3;
            break;
        case 2:
            status=1;
            ui->time3->setText(QString("文件写入完成时间%1").arg(getLogTime()));
            break;
        default:
            break;
        }


    });
    /*
     * 两种风格的connect
     */

    connect(list,&LargeFactorial::error,[=](int num){
        switch (num) {
        case 0:
            QMessageBox::warning(this, tr("错误"),
                                 tr("栈溢出了老哥"));
            break;
        case 1:
            QMessageBox::warning(this, tr("错误"),
                                 tr("写入文件出错，没有权限或者文件不存在"));
            break;
        default:
            break;
        }
    });
}

MainWindow::~MainWindow()
{
    delete list;
    runThread->quit();
    runThread->exit();
}

void MainWindow::initGUI()
{
    catPic=new QLabel(this);
    catPic->setPixmap(QPixmap(":/res/redCat.png"));
    catPic->setScaledContents(true);

    ui->maximizeButton->setIcon(QIcon(":/res/maximize-button1.png"));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    catPic->setGeometry(0,this->height()/2,158,103);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QImage backgroundImage(QStringLiteral(":/res/background.png"));
    painter.drawImage(rect(), backgroundImage);

    painter.setPen(QColor(50, 177, 122));
    painter.setBrush(QBrush(QColor(50, 177, 122),Qt::SolidPattern));//设置画刷形式
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

QString MainWindow::getLogTime()
{
    QTime time=QTime::currentTime();   //获取当前时间
    return QString("%1:%2:%3").arg(time.minute()).arg(time.second()).arg(time.msec());

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

void MainWindow::on_fileBtn_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    ".",
                                                    tr("All Files(*)"));
        if(!path.isEmpty()) {
            QFileInfo infor(path);
            ui->fileName->setText(infor.fileName());
            QFile file(path);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Write File"),
                                          tr("不能打开文件:\n%1").arg(path));
                return;
            }
            file.close();
            fileName=path;
            emit sendFileName(fileName);
        } else {
            QMessageBox::warning(this, tr("Path"),
                                 tr("你没有选择任何文件！"));
        }
}

void MainWindow::on_startBtn_clicked()
{
    if(status!=1){
        QString showText;
        if(status==2){
            showText="正在计算上一个大数阶乘，无法重新计算";
        }else {
            showText="正在将计算好的大数阶乘写入文件，无法重新计算";
        }
        QMessageBox::information(this, tr("Hmmm..."), showText);
        return;

    }


    int maxNum=ui->numSliderBar->value();
    int num=ui->num->text().toInt();
    if(num<=1){
        QMessageBox::warning(this,tr("非法"),tr("输入的数非法，请输入大于等于2的整数"));
        return;
    }
    //简单判断下，，，惨戚戚
    if(fileName.isEmpty()){
        QMessageBox::warning(this, tr("Path"),
                             tr("你没有选择任何文件！"));
        return;
    }
    /*
     * 其实这个由于运算速度很快，所以时间基本花费在信号的传递上，
     * 而不同线程信号传递又是队列的，很慢；
     * 下面几个怎么排序都没什么意义，仅供参考
     */
    ui->time2->setText("等待运算结束");
    ui->time3->setText("等待文件保存结束");
    ui->time1->setText(QString("运算开始时间%1").arg(getLogTime()));
    emit start(maxNum,num);

    status=2;

}
