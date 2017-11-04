#ifndef FILECOVERDIALOG_H
#define FILECOVERDIALOG_H
#include<QPainter>
#include<QDragEnterEvent>
#include <QWidget>
#include<QFont>

class FileCoverDialog : public QWidget
{
    Q_OBJECT
public:
    explicit FileCoverDialog(QWidget *parent = nullptr);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    bool m_status=false;
};

#endif // FILECOVERDIALOG_H
