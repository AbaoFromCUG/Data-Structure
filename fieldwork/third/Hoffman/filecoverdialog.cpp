#include "filecoverdialog.h"

FileCoverDialog::FileCoverDialog(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    m_img=new QLabel(this);

    m_text=new QLabel(this);
    m_text->setText("拖拽你的文件到此");
    m_img->setPixmap(QPixmap(":/res/moveBackground.png"));
}

void FileCoverDialog::setNormalStatus()
{
    m_text->setText("拖拽你的文件到此");
    m_img->setPixmap(QPixmap(":/res/moveBackground.png"));
}

void FileCoverDialog::resizeEvent(QResizeEvent *event)
{
    m_img->setGeometry(rect());

    m_img->setScaledContents(true);
    m_text->setGeometry(rect());

    QFont font;
    font.setPixelSize(this->width()/12);
    font.setBold(true);
    m_text->setStyleSheet("color:#D3D3D3");
    m_text->setFont(font);
    m_text->setAlignment(Qt::AlignCenter);

}

void FileCoverDialog::paintEvent(QPaintEvent *event)
{
}

void FileCoverDialog::dropEvent(QDropEvent *event)
{

    m_img->setPixmap(QPixmap(":/res/moveBackground.png"));
    m_text->setText("正在处理");
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }


    QFileInfo fileInfor(fileName);
    if(fileInfor.isFile()){
        emit signal_getFile(fileName);
    }


    QWidget::dropEvent(event);
}

void FileCoverDialog::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    m_img->setPixmap(QPixmap(":/res/moveBackground2.png"));
    event->acceptProposedAction();
    QWidget::dragEnterEvent(event);
}

void FileCoverDialog::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_img->setPixmap(QPixmap(":/res/moveBackground.png"));
    m_text->setText("拖拽你的文件到此");
    event->accept();
    QWidget::dragLeaveEvent(event);
}
