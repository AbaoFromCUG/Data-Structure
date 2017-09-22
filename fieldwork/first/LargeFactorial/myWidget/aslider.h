#ifndef ASLIDER_H
#define ASLIDER_H

#include<QWidget>
#include<QSlider>
#include<QLabel>
#include<QMouseEvent>
#include<QDebug>
class ASlider : public QSlider
{
public:
    ASlider(QWidget* parent=0);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel* m_displayLabel;
};

#endif // ASLIDER_H
