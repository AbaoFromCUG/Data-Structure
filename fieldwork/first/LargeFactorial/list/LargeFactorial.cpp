#include "LargeFactorial.h"
#include<iostream>
using namespace std;

LargeFactorial::LargeFactorial()
{
    connect(this,&LargeFactorial::ok,[=](int num){
        if(num==1){
            QTimer::singleShot(0,this,SLOT(saveDate()));
        }
    });
}


LargeFactorial::~LargeFactorial()
{
}

void LargeFactorial::start(int l,int maxNum)
{
    list.makeEmpty();
    list.append(1);
    storeLong = pow(10, l);
    length = l;
    //高位在尾部
    for (int i = 2; i <= maxNum; i++)
	{
        DListNode<int>* node=list.getLast();       //用来计算的node
        DListNode<int>* mNode;      //用来进位的node
        while (node!=list.getFirst()->LLink) {
             long long n= node->date*i;
             node->date=n%storeLong;
             n=n/storeLong;
             //如果需要进位的数非零的话
             mNode=node->RLink;
             //循环进位
             while (n) {
                 if(!mNode){
                     list.append(0);
                     mNode = list.getLast();
                     mNode->date = n%storeLong;
                     n /= storeLong;
                 }else {
                    n=mNode->date+n;
                    mNode->date=n%storeLong;
                    n=n/storeLong;
                 }
                 mNode=mNode->RLink;
             }
             node = node->LLink;
        }
    }
    emit ok(1);
}

void LargeFactorial::saveDate()
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        DListNode<int>* node=list.getLast();
        QString cache;  //保存缓存

        cache.append(QString::number(node->date));
        node=node->LLink;
        int t=list.getSize()%3;
        for(int i=1;i<t;i++){
            cache.append(QString("%1").arg(node->date,this->length,10,QChar('0')));
            node=node->LLink;
        }
        //把高位的不能三个三个输出的格式化
        int spaceNum=cache.length()%3==0?(cache.length()/3):(cache.length()/3+1);
        int strL=cache.length()%3;
        for(int i=0;i<spaceNum;i++){
            cache.insert((strL==0?3:strL)+3*i,' ');        //每隔3个插入个空格
        }
        qDebug()<<cache;
        out<<cache;
        cache.clear();
        while (node!=list.getFirst()->LLink) {
            for(int i=0;i<3000&&node!=list.getFirst()->LLink;i++){
                if(node->date<0||node->date>=storeLong){
                    qDebug()<<node->date;
                }
                cache.append(QString("%1").arg(node->date,this->length,10,QChar('0')));
                node=node->LLink;
            }
            int strLegth=cache.length()/3;
            for(int i=0;i<strLegth;i++){
                cache.insert(3+4*i,' ');        //每隔3个插入个空格
            }
            out<<cache;
            //qDebug()<<cache;
            cache.clear();
        }
        out<<"size:  ";
        out<<QString::number(list.getSize());
        emit ok(2);

    }else {
        //打开失败
        qDebug()<<"文件打开失败";
        emit error(1);
    }
    file.close();

}

void LargeFactorial::saveFilePath(QString fileName)
{
    this->fileName=fileName;
}


void LargeFactorial::output()
{
    cout << list.getLast()->date;
	coutItem(list.getLast()->LLink);
}

void LargeFactorial::coutItem(DListNode<int>* t)
{
	if (t!=list.getFirst()->LLink) {
		cout.fill('0');
		cout.width(length);
		cout << t->date;
		coutItem(t->LLink);
	}
	
}

int LargeFactorial::getSize()
{
    return list.getSize();
}



