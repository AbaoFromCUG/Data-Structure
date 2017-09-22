#include "aslider.h"



ASlider::ASlider(QWidget *parent):
    QSlider(parent)
{

    m_displayLabel=new QLabel(this);
    m_displayLabel->setFixedSize(QSize(20,20));
    //设置游标背景为白色
    m_displayLabel->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white);
    m_displayLabel->setPalette(palette);

    m_displayLabel->setAlignment(Qt::AlignCenter);

    m_displayLabel->setVisible(false);
    m_displayLabel->move(0,3);
}

void ASlider::mousePressEvent(QMouseEvent *event)
{
    if(!m_displayLabel->isVisible())
        {
            m_displayLabel->setVisible(true);
            m_displayLabel->setText(QString::number(this->value()));
        }
    QSlider::mousePressEvent(event);
}

void ASlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_displayLabel->isVisible())
      {
          m_displayLabel->setVisible(false);
      }
    QSlider::mouseReleaseEvent(event);
}

void ASlider::mouseMoveEvent(QMouseEvent *event)
{
    m_displayLabel->setText(QString::number(this->value()));
    int xx=(this->width()-m_displayLabel->width())*(this->value()-this->minimum())/(this->maximum()-this->minimum());
    m_displayLabel->move(xx,3);
    QSlider::mouseMoveEvent(event);
}
