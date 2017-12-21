#ifndef MGRAPHICSVIEW_H
#define MGRAPHICSVIEW_H

#include <QGraphicsView>
#include<QWheelEvent>
#include<QGraphicsScene>
#include<QGraphicsLineItem>
#include<QMenu>
#include<QList>
#include"addpointdialog.h"
#include"mapprofilereader.h"
#include<QInputDialog>
#include<QAction>
#include<QApplication>
#include<QMatrix>
#include<QMouseEvent>
class MGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MGraphicsView(QWidget *parent = nullptr);
    ~MGraphicsView();
signals:

public slots:
    void refresh();
//    void
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void trigerMenu(QAction* act,QPointF& pos);
//    void event(QEvent *event);

private:
    QGraphicsScene* m_scene;
    QGraphicsScene* m_lineScene;
    QGraphicsLineItem* m_line;
    double m_scale;

    bool m_mouseStatus;

    QPointF m_startPoint;
};

#endif // MGRAPHICSVIEW_H
