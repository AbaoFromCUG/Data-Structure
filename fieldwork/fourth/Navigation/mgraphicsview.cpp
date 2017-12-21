#include "mgraphicsview.h"

MGraphicsView::MGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene=0;
    refresh();
}

MGraphicsView::~MGraphicsView()
{
    m_scene->deleteLater();
    m_lineScene->deleteLater();
}

void MGraphicsView::refresh()
{
    if(m_scene){
       m_scene->deleteLater();
    }
    //我的逻辑代码
    m_scene=new QGraphicsScene();
    m_lineScene=new QGraphicsScene();
    this->setScene(m_scene);
    m_scale=1;
    m_line=0;
    m_mouseStatus=false;    //初始化鼠标状态为释放


    MapProfileReader* reader= MapProfileReader::getInstance();

    m_scene->addPixmap(QPixmap(reader->getMapImg()));
    QList<ViewPoint> points=reader->getAllPoint();
    for(auto i: points){
        QGraphicsEllipseItem* item=new QGraphicsEllipseItem(QRectF(QPointF(i.x-10,i.y-10),QPointF(i.x+10,i.y+10)));
        item->setBrush(Qt::SolidPattern);
        this->m_scene->addItem(item);
    }
}

void MGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers()==Qt::CTRL)
    if(event->delta()<0){
        QMatrix mat;
        m_scale*=0.9;
        mat.scale(m_scale,m_scale);
        this->setMatrix(mat);
    }else{
        QMatrix mat;
        m_scale*=1.1;
        mat.scale(m_scale,m_scale);
        this->setMatrix(mat);
    }

}

void MGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPointF p=this->mapToScene(QPoint(event->pos().x(),event->pos().y()));
    if(event->button()==Qt::LeftButton&&QApplication::keyboardModifiers()==Qt::CTRL){
        this->m_mouseStatus=true;
        m_line=new QGraphicsLineItem();
        QPen pen(Qt::SolidLine);
        pen.setWidth(20);
        m_line->setPen(pen);
        m_startPoint=p;
        m_line->setLine(QLineF(p,p));
        this->m_scene->addItem(m_line);
    }
    if(event->button()==Qt::RightButton){
        QMenu menu;
        QAction *addNewPoint = menu.addAction("建立新的关键点");
        QAction *addPoint=menu.addAction("添加拐角点");

        connect(addNewPoint,&QAction::triggered,[=](){
            AddPointDialog::addPoint(p);
        });
        connect(addPoint,&QAction::triggered,[=](){
            MapProfileReader* reader=MapProfileReader::getInstance();
            reader->addPoint(p);
        });


//        connect()
        menu.exec(QPoint(event->screenPos().x(),event->screenPos().y()));
    }
}

void MGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    m_mouseStatus==false;
    if(m_line)
        m_scene->removeItem(m_line);

}

void MGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF p=this->mapToScene(QPoint(event->pos().x(),event->pos().y()));
    if(m_mouseStatus&&QApplication::keyboardInputInterval()==Qt::CTRL){
        m_line->setLine(QLineF(this->m_startPoint,p));
    }

}

void MGraphicsView::trigerMenu(QAction *act,QPointF& pos)
{
    if(act->text()=="建立新的关键点"){
//        AddPointDialog::addPoint()
    }

}
