#include "mainwindow.h"
#include"ui_mainwindow.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("邻接无项图");
    initGUI();
//    this->m_type=0;
    this->map=nullptr;
    log=new LogHelper(this);
    ui->pointView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mapView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->mapView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);5
    log->setOutWidget(ui->logOut);
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
    Q_UNUSED(event);/*
    catPic->setGeometry(0,this->height()/2,158,103);*/
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QImage backgroundImage(QStringLiteral(":/img/res/background.png"));
    painter.drawImage(rect(), backgroundImage);
//    painter.drawImage(10,200,QImage(QStringLiteral(":/img/res/redCat.png")));
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


void MainWindow::on_addPointBtn_clicked()
{
    if(!map){
        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
        return;
    }
    if(ui->addPoint->text().isEmpty()){
        QMessageBox::warning(this,"非法","对不起，你没有输入你想加入的点的值");
        return;
    }
    double  re=ui->addPoint->text().toDouble();
    try{
        this->map->addNode(re);
        int i=ui->pointView->rowCount();
        ui->pointView->insertRow(i);
        ui->pointView->setItem(i,0,new QTableWidgetItem(QString::number(this->map->NumberOfVertices()-1)));
        ui->pointView->setItem(i,1,new QTableWidgetItem(QString::number(re)));
    }catch(const char* e){
        log->outWarm(e);
        return;
    }

    ui->label_2->setText(QString("当前有%1个点").arg(this->map->NumberOfVertices()));
    log->outLog(QString("插入了一个点,这个点下标为%1,值为%2").arg(map->NumberOfVertices()-1).arg(re));
    ui->addPoint->clear();


//    switch (m_type) {
//    case 0:
//    {
//        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
//        return;
//        break;
//    }
//    case 1:
//    {
//        AMMap<double>* ptr=this->map;
//        return;
//        break;
//    }
//    case 2:
//    {
//        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
//        return;
//        break;
//    }
//    case 3:
//    {
//        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
//        return;
//        break;
//    }
//    case 4:
//    {
//        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
//        return;
//        break;
//    }
//    case 5:
//    {
//        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
//        return;
//        break;
//    }
//    case 6:
//    {
//        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
//        return;
//        break;
//    }
//    default:
//        QMessageBox::warning(this,"error","不知名错误");
//        break;
//    }
}

void MainWindow::on_changePointBtn_clicked()
{
    if(!map){
        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
        return;
    }
    if(ui->changePointIndex->text().isEmpty()||ui->changePoint->text().isEmpty()){
        QMessageBox::warning(this,"非法","对不起，你没有输入你想修改的点的值或者下标");
        return;
    }
    int i=ui->changePointIndex->text().toInt();
    double re=ui->changePoint->text().toDouble();
    try{
        map->setNodeValue(i,re);
        int t=ui->pointView->rowCount();
        for(int j=0;j<t;j++){
            if(ui->pointView->item(j,0)->text().toInt()==i){
                ui->pointView->setItem(j,1,new QTableWidgetItem(QString::number(re)));
            }
        }
        log->outLog(QString("修改了一个点,这个点下标为%1,修改后的值为%2").arg(i).arg(re));
        ui->changePoint->clear();
        ui->changePointIndex->clear();
    }catch(const char* e){
        log->outWarm(e);
    }

}

void MainWindow::on_addLineBtn_clicked()
{
    if(!map){
        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
        return;
    }
    if(ui->addLine->text().isEmpty()|ui->addLineIndex1->text().isEmpty()||ui->addLineIndex2->text().isEmpty()){
        QMessageBox::warning(this,"非法","对不起，存在为空的值");
        return;
    }
    try{
        int v1=ui->addLineIndex1->text().toInt();
        int v2=ui->addLineIndex2->text().toInt();
        double re=ui->addLine->text().toDouble();
        map->insertEdge(v1,v2,re);
        int row=ui->mapView->rowCount();
        qDebug()<<row;
        ui->mapView->insertRow(row);
        ui->mapView->setItem(row,0,new QTableWidgetItem(QString::number(v1)));
        ui->mapView->setItem(row,1,new QTableWidgetItem(QString::number(v2)));
        ui->mapView->setItem(row,2,new QTableWidgetItem(QString::number(re)));

        log->outLog(QString("在%1和%2之间插入了一条边，这条边的权重是%3").arg(v1).arg(v2).arg(re));
        ui->addLine->clear();
        ui->addLineIndex1->clear();
        ui->addLineIndex2->clear();
    }
    catch(const char* c){
        log->outWarm(c);
    }
}

void MainWindow::on_changeLineBtn_clicked()
{
    if(!map){
        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
        return;
    }
    if(ui->changeLineIndex1->text().isEmpty()||ui->changeLineIndex2->text().isEmpty()||ui->changeLIne->text().isEmpty()){
        QMessageBox::warning(this,"非法","对不起，存在为空的值");
        return;
    }
    int v1=ui->changeLineIndex1->text().toInt();
    int v2=ui->changeLineIndex2->text().toInt();
    double re=ui->changeLIne->text().toInt();
    try{
        map->setEdge(v1,v2,re);
        int i=ui->mapView->rowCount();
        for(int j=0;j<i;j++){
            if(ui->mapView->item(j,0)->text().toInt()==v1&&ui->mapView->item(j,1)->text().toInt()==v2){
                ui->mapView->setItem(j,2,new QTableWidgetItem(QString::number(re)));
                break;
            }
        }
        log->outLog(QString("将(%1,%2)的边修改为%3").arg(v1).arg(v2).arg(re));
        ui->changeLIne->clear();
        ui->changeLineIndex1->clear();
        ui->changeLineIndex2->clear();
    }
    catch(const char* e){
        log->outWarm(e);
    }
}

void MainWindow::on_DFS_clicked()
{
    if(!map){
        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
        return;
    }
    int i=ui->fromIndex->text().toInt();
    log->outLog(QString("广度度优先开始，起始点是下标为%1的点").arg(i));
    map->depthFirstTraverse(i,[=](ADNode<double,ADEdge<double>>* n,ADEdge<double>* e){
        if(e){
            log->outLog(QString("通过权为%1边访问数据域为%2的点").arg(e->m_data).arg(n->m_data));
        }else {
            log->outLog(QString("访问的首个节点，数据域%1").arg(n->m_data));
        }
    });
}

void MainWindow::on_BFS_clicked()
{
    if(!map){
        QMessageBox::warning(this,"非法","对不起，图还没有初始化");
        return;
    }
    int i=ui->fromIndex->text().toInt();
    log->outLog(QString("深度优先开始，起始点是下标为%1的点").arg(i));
    map->depthFirstTraverse(i,[=](ADNode<double,ADEdge<double>>* n,ADEdge<double>* e){
        if(e){
            log->outLog(QString("通过权为%1边访问数据域为%2的点").arg(e->m_data).arg(n->m_data));
        }else {
            log->outLog(QString("访问的首个节点，数据域%1").arg(n->m_data));
        }
    });
}

void MainWindow::on_newMap_clicked()
{
        int maxN=ui->maxNum->text().toInt();
        if(maxN<=0){
            QMessageBox::warning(this,"非法输入","对不起，图的最大容量应该是大于零的整数");
            ui->maxNum->clear();
            return;
        }
    try{
            this->map=new Undir_ADMap<double,double>(maxN);
       }
    catch(...){
            log->outErr("建图失败，内存申请失败！！！");
        }
    log->outLog(QString("建图成功，容量%1").arg(maxN));

//    int t1=ui->pointType->currentIndex();
//    int t2=ui->edgeType->currentIndex();
//    if(ui->type->currentIndex()==0){
//        //如果为0，那么就是，矩阵
//        if(t2){
//            //如果边存的数据类型要求是ｓｔｒｉｎｇ,那么就异常
//            QMessageBox::warning(this,"非法输入","对不起，邻接矩阵存储时，边只能为整数型");
//            return;
//        }
//        if(t1){
//            this->map=new AMMap<double>(maxN);
//            m_type=1;
//        }else{
//            m_type=2;
//        }

//    }else{
//        //t1为true为double
//        if(t1){
//            if(t2){
//                this->map=new Undir_ADMap<double,double>(maxN);
//                m_type=3;
//            }else {
//                this->map=new Undir_ADMap<double,QString>(maxN);
//                m_type=4;
//            }
//        }else{
//            if(t2){
//                this->map=new Undir_ADMap<QString,double>(maxN);
//                m_type=5;
//            }else{
//                this->map=new Undir_ADMap<QString,QString>(maxN);
//                m_type=6;
//            }
//        }
//    }
}
