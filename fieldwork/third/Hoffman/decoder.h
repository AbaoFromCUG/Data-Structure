#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include<QFile>
#include<QStringList>
#include<QString>
#include<QFileInfo>
#include<QIODevice>
#include<QDataStream>
#include"encoder.h"
class DeCoder : public QObject
{
    Q_OBJECT
public:
    explicit DeCoder(QObject *parent = nullptr);

signals:
    void signal_deCoder(int status);

public slots:
    void deCodeFile(QString fromName);
protected:
    void getToName();
    void makeTree();
    void deCode();
protected:
    QString m_fromName;
    QString m_toName;
    HoffmanNode* root;
    qint64 countArray[256];
};

#endif // DECODER_H
