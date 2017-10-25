#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QObject>
#include<QTextBrowser>
class LogHelper : public QObject
{
    Q_OBJECT
public:
    explicit LogHelper(QObject *parent = nullptr);
    void setOutWidget(QTextBrowser* widget);
    QString stringToHtml(QString str,QColor crl);
protected:

    QTextBrowser* outWidget;  //输出的日志区域
    QString logFileName="./BinTree.log";
signals:

public slots:
    void outLog(QString message);
    void outWarm(QString message);
    void outErr(QString message);
};

#endif // LOGHELPER_H
