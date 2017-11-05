#ifndef FILECOVERDIALOG_H
#define FILECOVERDIALOG_H
#include<QPainter>
#include<QDragEnterEvent>
#include <QWidget>
#include<QFont>
#include<QMimeData>
#include<QFileInfo>
#include<QLabel>
#include<QDebug>
#include<QTextEdit>
class FileCoverDialog : public QWidget
{
    Q_OBJECT
public:
    explicit FileCoverDialog(QWidget *parent = nullptr);

signals:
    void signal_getFile(QString fileName);

public slots:
    void setNormalStatus();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void updateUi();
    QLabel *m_img;
    QLabel* m_text;
};

#endif // FILECOVERDIALOG_H
