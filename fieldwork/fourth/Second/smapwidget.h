#ifndef SMAPWIDGET_H
#define SMAPWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QPoint>
#include"lib/struct/kmintree.h"
#include"lib/struct/ammap.h"
#include<QChart>
#include<QChartView>
#include<QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include<qchartview.h>
class SMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SMapWidget(QWidget *parent = nullptr);
    ~SMapWidget();

signals:
protected:
    void paintEvent(QPaintEvent *event);
    void initPointMap();

    void drawRect(QString str,QPoint p);
public slots:
    void startPaint();
    void timerEvent(QTimerEvent *event);


private:
    int m_rectW=100;
    int m_rectH=50;
    int m_status;
    KMinTree m_map;
    AMMap<QString>* m_minMap;
    QPoint m_pointMap[7];

    QCharts *m_chart;
    QLineSeries* m_scatter;

};

#endif // SMAPWIDGET_H


