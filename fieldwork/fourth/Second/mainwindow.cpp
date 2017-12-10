#include "mainwindow.h"
#include"ui_mainwindow.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
    ,pixMap(1200,900)
    ,m_map(7)

{
    ui->setupUi(this);
    pixMap.fill(Qt::white);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("第二题:村庄修路");
    initGUI();
    pixLabel=new QLabel(this);
    pixLabel->setPixmap(pixMap);

    ui->mapArea->setWidget(pixLabel);


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
    this->m_map.addNode("村庄A");
    this->m_map.addNode("村庄B");
    this->m_map.addNode("村庄C");
    this->m_map.addNode("村庄D");
    this->m_map.addNode("村庄E");
    this->m_map.addNode("村庄F");
    this->m_map.addNode("村庄G");

    this->m_map.insertEdge(0,1,28);
    this->m_map.insertEdge(0,5,10);

    this->m_map.insertEdge(1,2,16);
    this->m_map.insertEdge(1,6,14);

    this->m_map.insertEdge(2,3,12);

    this->m_map.insertEdge(3,4,22);
    this->m_map.insertEdge(3,6,18);

    this->m_map.insertEdge(4,5,25);
    this->m_map.insertEdge(4,6,24);


    this->m_minMap=new AMMap<QString>(this->m_map.getMinTree());
    initPointMap();
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

void MainWindow::timerEvent(QTimerEvent *event)
{


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
    QPainter painter(&pixMap);
    QPen pen;
    pen.setBrush(Qt::black);
    pen.setWidth(5);

    painter.setPen(pen);
    //在这里绘制最西小生成树
    QList<MinEdge> min=this->getEdgeFromMinMap();
    for(auto i : min){
        painter.drawLine(m_pointMap[i.index1],m_pointMap[i.index2]);

    }
    painter.end();
    this->m_minMap=new AMMap<QString>(this->m_map.getMinTree());
    for(int i=0;i<7;i++){
        drawRect(m_map.getValue(i),m_pointMap[i]);
    }

    this->pixLabel->setPixmap(pixMap);
}

QList<MinEdge> MainWindow::getEdgeFromMinMap()
{
    return KMinTree(*m_minMap).getEdge();
}

void MainWindow::drawRect(QString str, QPoint p)
{
    QPainter painter(&pixMap);
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setBrush(QBrush(QColor(237, 212, 0),Qt::SolidPattern));//设置画刷形式
    QRect rect(p.x()-this->m_rectW/2,p.y()-this->m_rectH/2,this->m_rectW,this->m_rectH);
    painter.drawEllipse(rect);
    painter.drawText(rect, Qt::AlignCenter,str);
    painter.end();
}

void MainWindow::drawLine(int i, int j, QString name)
{
    QPainter painter(&pixMap);
    QPen pen(Qt::DotLine);
    pen.setWidth(5);
    pen.setBrush(Qt::gray);
    painter.setPen(pen);
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    painter.setFont(font);
    QPoint a=m_pointMap[i];
    QPoint b=m_pointMap[j];
    QPoint t=b-a;/*
    a=a+t/t.manhattanLength()*40.;
    b=b-t/t.manhattanLength()*40.;*/
    painter.drawLine(a,b);
    painter.setPen(Qt::red);
    painter.drawText(QRect(a,b),Qt::AlignCenter,name);

}

void MainWindow::initPointMap()
{
    m_pointMap[0]=QPoint(50,450); //A
    m_pointMap[1]=QPoint(400,350); //B
    m_pointMap[2]=QPoint(150,50); //C
    m_pointMap[3]=QPoint(700,100);  //D
    m_pointMap[4]=QPoint(600,600);  //E
    m_pointMap[5]=QPoint(300,650);  //F
    m_pointMap[6]=QPoint(850,300); //G

}

void MainWindow::on_pushButton_2_clicked()
{
    this->pixMap.fill(Qt::white);
    QList<MinEdge> e=m_map.getEdge();
    for(auto i:e){
        drawLine(i.index1,i.index2,QString::number(i.weight));
    }
    for(int i=0;i<7;i++){
        drawRect(m_map.getValue(i),m_pointMap[i]);
    }
    this->pixLabel->setPixmap(pixMap);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                tr("Open Image"),QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0], tr("Image Files (*.png *.jpg *.bmp)"));
    if(fileName.isEmpty()){
        QMessageBox::warning(this,"sorry","抱歉，你没有选择任何的文件");
        return;
    }
    else {
        pixMap.save(fileName);
    }
}
