#include "encoder.h"

EnCoder::EnCoder(QObject *parent) : QObject(parent)
{

}



void EnCoder::enCodeFile(QString fromName, QString toName)
{
    this->m_fromName=fromName;
    this->m_toName=toName;
    count();
    emit signal_enCoder(0,2);
    makeMap();
    emit signal_enCoder(1,5);
    enCode();

}

void EnCoder::count()
{
    initCountArray();
    QFile file(m_fromName);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    unsigned char readChar[1024000];
    while (!stream.atEnd()) {
        qint64 reallLength=stream.readRawData((char*)readChar,1024000);
        for(qint64 i=0;i<reallLength;i++){
            countArray[readChar[i]]++;
        }
    }
    file.close();
}

void EnCoder::makeMap()
{
    HoffmanNode* root;
    HoffmanNode* store[256];
    HoffmanNode* list[256];
    int num1=0,num2=1;
    for(int i=0;i<256;i++){
        if(!countArray[i]){
            store[i]=list[i]=nullptr;
            continue;
        }
        store[i]=list[i]=new HoffmanNode(countArray[i]);
        store[i]->setKey(i);
    }
    for(int i=0;i<256;i++){
        num1=0;
        num2=0;
        for(int j=0;j<256;j++){
            if(!list[j]){
                continue;
            }else {
                if(!list[num1]){
                    num1=j;
                    continue;
                }else if(!list[num2]){
                    num2=j;
                    continue;
                }else {
                    if(list[num1]->weight>list[j]->weight){
                        num1=j;
                    }else if(list[num2]->weight>list[j]->weight){
                        num2=j;
                    }

                }
            }
        }
        if(!list[num2]){
            //如果只有一个节点了
            root=list[num1];
            break;
        }
        list[num1]=new HoffmanNode(list[num1]->weight+list[num2]->weight,list[num1],list[num2]);
        list[num2]=0;
    }


    for(int i=0;i<256;i++){
        HoffmanNode* node=store[i];
        while (node&&node->parent) {
            if(node->parent->right==node){
                /*
                 * 如果当前节点位于父节点的右边节点,
                 * 那么就在
                 */
                enCodeMap[i].insert(0,"1");
            }else {
                enCodeMap[i].insert(0,"0");
            }
            node=node->parent;
        }
    }
    delete root;
}


void EnCoder::initCountArray()
{

    for(int i=0;i<256;i++){
        countArray[i]=0;
    }
}

void EnCoder::enCode()
{
    //用于统计工作量的两个数字
    QFileInfo infor(m_fromName);
    double countTimes=infor.size()/1024000+1;
    qint64 countSize=0;



    QFile inFile(m_fromName);
    QFile outFile(m_toName);
    inFile.open(QIODevice::ReadOnly);
    outFile.open(QIODevice::WriteOnly);
    QDataStream inStream(&inFile);
    QDataStream outStream(&outFile);
    outStream<<getMessage();    //将文件信息放入其中
    unsigned char readChar[1024000];
    QString readCache;
    unsigned char* writeCache;
    while (!inStream.atEnd()) {
        /*
         * 编码环节
         * 一次读入1024000个字符,然后再写入
         */

        int reallLength=inStream.readRawData((char*)readChar,1024000);
        for(int i=0;i<reallLength;i++){
            readCache.append(enCodeMap[readChar[i]]);
        }

        if(inStream.atEnd()){
            //当读进文件缓存时候时读完了
            //收尾处理
            while(readCache.length()%8!=0)
                readCache.append('0');
        }
        qint64 cacheLength=readCache.length()/8;
        writeCache=new unsigned char[cacheLength];
        unsigned char a;
        qint64 i;
        for(i=0;i<cacheLength;i++){
            writeCache[i]=toUChar(readCache.mid(i*8,8));
        }
        outStream.writeRawData((char*)writeCache,cacheLength);
        readCache=readCache.mid(i*8);
        delete[] writeCache;
        countSize++;
        emit signal_enCoder(2,countSize/countTimes*100);
    }
    inFile.close();
    outFile.close();
}

unsigned char EnCoder::toUChar(const QString &str)
{

    if(str.length()!=8){
        throw "error";
    }
    unsigned char a=0;
    for(qint64 i=0;i<str.length();i++){
        if(str.at(i).toLatin1()=='0')
            a=a<<1;
        else {
            a=a<<1;
            a=a+1;
        }
    }
    //a=a>>1;
    return a;
}


QString EnCoder::getMessage()
{
    //不选择序列化我的树,而选择序列化我的countArray  //
    QString str=QString("#%1#").arg(m_fromName);
    for(int i=0;i<256;i++){
        str.append(QString::number(countArray[i])).append("#");
    }
    return str+"\n";
}



