#include "smapwidget.h"
#include<QTimer>
SMapWidget::SMapWidget(QWidget *parent) :
    QWidget(parent)
  ,m_map(7)

{
    this->setGeometry(0,0,1000,1000);

    m_status=0;
    this->m_map.addNode("村庄A");
    this->m_map.addNode("村庄B");
    this->m_map.addNode("村庄C");
    this->m_map.addNode("村庄D");
    this->m_map.addNode("村庄E");
    this->m_map.addNode("村庄F");
    this->m_map.addNode("村庄G");

    this->m_map.insertEdge(0,1,28);
    this->m_map.insertEdge(0,5,10);

    this->m_map.insertEdge(1,0,28);
    this->m_map.insertEdge(1,2,16);
    this->m_map.insertEdge(1,6,14);

    this->m_map.insertEdge(2,1,16);
    this->m_map.insertEdge(2,3,0);

    this->m_map.insertEdge(3,2,12);
    this->m_map.insertEdge(3,4,22);
    this->m_map.insertEdge(3,6,18);

    this->m_map.insertEdge(4,3,22);
    this->m_map.insertEdge(4,5,25);
    this->m_map.insertEdge(4,6,24);

    this->m_map.insertEdge(5,0,10);
    this->m_map.insertEdge(5,4,25);

    this->m_map.insertEdge(6,1,14);
    this->m_map.insertEdge(6,3,18);
    this->m_map.insertEdge(6,4,24);

    this->m_minMap=new AMMap<QString>(this->m_map.getMinTree());
    initPointMap();
}

SMapWidget::~SMapWidget()
{
    if(m_minMap){
        delete m_minMap;
    }
}

void SMapWidget::paintEvent(QPaintEvent *event)
{
    for(int i=0;i<7;i++){
        drawRect(m_map.getValue(i),m_pointMap[i]);
    }
    if(m_status==1){
        //在这写绘制函数
    }

}

void SMapWidget::initPointMap()
{
    m_pointMap[0]=QPoint(100,500);
    m_pointMap[1]=QPoint(200,100);
    m_pointMap[2]=QPoint(150,400);
    m_pointMap[3]=QPoint(300,150);
    m_pointMap[4]=QPoint(300,600);
    m_pointMap[5]=QPoint(500,50);
    m_pointMap[6]=QPoint(500,450);


    m_chart=new QCharts();
    m_scatter=new QScatterSeries();
}

void SMapWidget::drawRect(QString str, QPoint p)
{
    QPainter painter(this);
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

void SMapWidget::startPaint()
{
    //    QTimer::s

}

void SMapWidget::timerEvent(QTimerEvent *event)
{

}
