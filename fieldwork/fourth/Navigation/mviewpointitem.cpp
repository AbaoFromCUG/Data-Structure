#include "mviewpointitem.h"

MViewPointItem::MViewPointItem(QWidget *parent) : QGraphicsItem(parent)
{

}

MViewPointItem::getObjectFromViewPoint(ViewPoint &point)
{
    MViewPointItem item;
    item.m_name=point.name;
    item.m_decs=point.desc;
    item.m_index=point.index;
    item.m_x=point.x;
    item.m_y=point.y;
    item.m_type=point.type;
    item.m_imgSrc=point.imgSrc;

}

void MViewPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


}

void MViewPointItem::paint()
{

}

QRectF MViewPointItem::boundingRect()
{

}
