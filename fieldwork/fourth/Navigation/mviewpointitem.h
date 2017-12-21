#ifndef MVIEWPOINTITEM_H
#define MVIEWPOINTITEM_H

#include <QGraphicsItem>
#include<QRectF>
#include"mapprofilereader.h"
class MViewPointItem : public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MViewPointItem(QWidget *parent = nullptr);
    static MViewPointItem getObjectFromViewPoint(ViewPoint& point);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mous
    void paint();
    QRectF boundingRect();
signals:

public slots:
private:
    QString m_name;
    QString m_decs;
    QString m_imgSrc;
   int m_index;
   double m_x;
   double m_y;
   int m_type;
};

#endif // MVIEWPOINTITEM_H
