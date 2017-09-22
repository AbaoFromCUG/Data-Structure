#pragma once
#include"DoublyList.h"
#include<QObject>
#include<QTimer>
#include<QFile>
#include<QDebug>
#include<QTextStream>
class LargeFactorial:public QObject
{
    Q_OBJECT
public:
    LargeFactorial();
    ~LargeFactorial();
	void output();
	void coutItem(DListNode<int>* t);
	int getSize();
signals:
    void ok(int num);
    void error(int num);
public slots:
    void start(int l,int maxNum);
    void saveDate();
    void saveFilePath(QString fileName);
protected:
	int storeLong;   //一个节点所存的最大数
	int length;		//一个节点存的位数
	DoublyList<int> list;	//用来存储数据的链表
	int maxNum;			//求的大数
    QString fileName;
};

