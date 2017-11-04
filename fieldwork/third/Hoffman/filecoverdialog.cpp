#include "filecoverdialog.h"

FileCoverDialog::FileCoverDialog(QWidget *parent) : QWidget(parent)
{
    this->setAcceptDrops(true);
}

void FileCoverDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(this->width()/12);
    painter.setFont(font);
    if(m_status){
        painter.setPen(QPen(Qt::lightGray));
        QImage backgroundImage(QString(":/res/moveBackground2.png"));
        painter.drawImage(rect(), backgroundImage);
        painter.drawText(QRect(this->pos().x(),this->pos().y(),this->width(),this->height()),Qt::AlignCenter,QString("释放"));
    }else{
        painter.setPen(QPen(Qt::gray));
        QImage backgroundImage(QString(":/res/moveBackground.png"));
        painter.drawImage(rect(), backgroundImage);
        painter.drawText(QRect(this->pos().x(),this->pos().y(),this->width(),this->height()),Qt::AlignCenter,QString("拖拽你的文件到此"));
    }


    painter.end();

}

void FileCoverDialog::dropEvent(QDropEvent *event)
{
    m_status=false;
}

void FileCoverDialog::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
    m_status=true;
}

void FileCoverDialog::dragLeaveEvent(QDragLeaveEvent *event)
{
     //m_status=false;
}
