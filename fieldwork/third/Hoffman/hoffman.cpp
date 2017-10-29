#include "hoffman.h"

Hoffman::Hoffman(QObject *parent) : QObject(parent)
{

}

Hoffman::~Hoffman()
{
    if(root)
        delete root;
}

void Hoffman::startZip(QString fileName,QString enCodeFileName)
{
    this->fileName=fileName;
    this->enCodeFileName=enCodeFileName;
    count();
    makeTree();
    enCodeFile();
    deCodeFile();
    emit zipSuccess();
}

void Hoffman::startUnZip(QString enCodeFileName, QString fileName)
{

}


void Hoffman::count()
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    char readChar[100000];
    while (!stream.atEnd()) {
        int reallLength=stream.readRawData(readChar,100000);
        for(int i=0;i<reallLength;i++){
            countArray[(unsigned char)readChar[i]]++;
        }
    }
    file.close();
}

void Hoffman::makeTree()
{
    HoffmanNode* store[256];
    HoffmanNode* list[256];
    int num1=0,num2=1;
    for(int i=0;i<256;i++){
        store[i]=list[i]=new HoffmanNode(countArray[i]);
    }
    for(int i=0;i<255;i++){
        num1=0;
        num2=1;
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
                    if(list[num1]>list[j]){
                        num1=j;
                    }else if(list[num2]>list[j]){
                        num2=j;
                    }

                }
            }
        }
        list[num1]=new HoffmanNode(list[num1]->weight+list[num2]->weight,list[num1],list[num2]);
        list[num2]=0;
    }
    root=list[num1];


    for(int i=0;i<256;i++){
        HoffmanNode* node=store[i];
        while (node->parent) {
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
}

void Hoffman::enCodeFile()
{
    QFile inFile(fileName);
    QFile outFile(enCodeFileName);
    inFile.open(QIODevice::ReadOnly);
    outFile.open(QIODevice::WriteOnly);
    QDataStream inStream(&inFile);
    QDataStream outStream(&outFile);
    char readChar[3200];
    QString writeCache;
    char* enCodeCache;
    while (!inStream.atEnd()) {
        /*
         * 编码环节
         * 一次读入3200个字符,然后再写入
         */
        int reallLength=inStream.readRawData(readChar,3200);
        for(int i=0;i<reallLength;i++){
            writeCache.append(enCodeMap[(unsigned char)readChar[i]]);
        }
        //当读进缓存的字符长度不是8的整数倍,那就补齐到8的整数倍
        while (writeCache.length()%8) {
            writeCache.append('0');
        }
        int cacheLength=writeCache.length()/8;
        uint a;
        enCodeCache=new char[cacheLength];
        for(int i=0;i<cacheLength;i++){
            a=writeCache.mid(i*8,8).toInt(0,2);
            enCodeCache[i]=a;
        }
        outStream.writeRawData(enCodeCache,cacheLength);
        //enCodeCache.clear();
        delete[] enCodeCache;
        writeCache.clear();
    }
    inFile.close();
    outFile.close();
}

void Hoffman::deCodeFile()
{
    QFile file(enCodeFileName);
    QFile deFile(enCodeFileName+".png");
    file.open(QIODevice::ReadOnly);
    deFile.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    QDataStream deStream(&deFile);
    unsigned char a;
    while (!stream.atEnd()) {
        stream>>a;
        QString str=QString::number(a,2);
        int i;
        for(i=0;i<256;i++){
            if(enCodeMap[i]==str){
                deStream<<(char)i;
            }
        }
    }



    deFile.close();
    file.close();
}

void Hoffman::initCountArray()
{

    for(int i=0;i<256;i++){
        countArray[i]=0;
    }
}

QString Hoffman::getString()
{
    QString result;
    for(int i=0;i<256;i++){
        result.append(enCodeMap[i]);
        result.append("#");
    }
    int strLen=256*8;
    while (result.length()<strLen) {
        result.append("#");
    }
    return result;
}
