#include "loghelper.h"

LogHelper::LogHelper(QObject *parent) : QObject(parent)
{

}

void LogHelper::setOutWidget(QTextBrowser *widget)
{
    outWidget=widget;
    connect(outWidget,&QTextBrowser::cursorPositionChanged,[=](){
        QTextCursor cursor=outWidget->textCursor();
        cursor.movePosition(QTextCursor::End);
        outWidget->setTextCursor(cursor);
    });
}

QString LogHelper::stringToHtml(QString str, QColor crl)
{
    QByteArray array;
    array.append(crl.red());
    array.append(crl.green());
    array.append(crl.blue());
    QString strC(array.toHex());
    return QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str);
}

void LogHelper::outLog(QString message)
{
    outWidget->append(stringToHtml(QString(">Log: %1").arg(message),QColor(Qt::green)));
}

void LogHelper::outWarm(QString message)
{
    outWidget->append(stringToHtml(QString(">Warm: %1").arg(message),QColor(Qt::yellow)));
}

void LogHelper::outErr(QString message)
{
    outWidget->append(stringToHtml(QString(">Error: %1").arg(message),QColor(Qt::red)));
}
