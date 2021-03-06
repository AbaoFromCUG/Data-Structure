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
    initCountArray();
    QFile file(fileName);
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

void Hoffman::makeTree()
{
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
        if(num1==num2){
            qDebug()<<"Error";
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
        if(node!=root){
            qDebug()<<"kfjdlksf";
        }
    }
}

void Hoffman::enCodeFile()
{
    qint64 allLength=0;
    QFile inFile(fileName);
    QFile outFile(enCodeFileName);
    inFile.open(QIODevice::ReadOnly);
    outFile.open(QIODevice::WriteOnly);
    QDataStream inStream(&inFile);
    QDataStream outStream(&outFile);
    unsigned char readChar[1024000];
    QString readCache;
    unsigned char* writeCache;
    while (!inStream.atEnd()) {
        /*
         * 编码环节
         * 一次读入1024000个字符,然后再写入
         */
        int reallLength=inStream.readRawData((char*)readChar,1024000);
        allLength+=reallLength;
        for(int i=0;i<reallLength;i++){
            readCache.append(enCodeMap[(unsigned char)readChar[i]]);
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
    }
    qDebug()<<allLength;
    inFile.close();
    outFile.close();

}

void Hoffman::deCodeFile()
{
    qint64 allLength=0;
    QFile inFile(enCodeFileName);
    QFile deFile(enCodeFileName+".jpg");
    inFile.open(QIODevice::ReadOnly);
    deFile.open(QIODevice::WriteOnly);
    QDataStream inStream(&inFile);
    QDataStream deStream(&deFile);

    unsigned char readChar[1024000];
    QString readCache;
    while (!inStream.atEnd()) {
        /*
         * 跟压缩相反,就是每次读进1024000个字符,
         * 然后再通过二叉搜索树?进行解码
         */
        int reallReadLength=inStream.readRawData((char*)readChar,1024000);
        for(int i=0;i<reallReadLength;i++){
            readCache.append(QString("%1").arg(readChar[i],8,2,QChar('0'))); //将所有缓存转换为二进制
        }
        /*
         * 作为一个缓存的话
         * 先写入很多的缓存,
         * 然后再解码,
         * 因为一个编码最长的的编码是256
         */
        if(inStream.atEnd()){
            //读完了
            QString writeCache;
            HoffmanNode* workNode=root;
            for(qint64 i=0;i<readCache.length();i++){
                if(readCache.at(i)=='0'){
                    workNode=workNode->left;
                }else{
                    workNode=workNode->right;
                }
                if(workNode->isLastNode()){
                    //当搜索到尾部节点,就把叶节点的字符加进去
                    writeCache.append(workNode->key);
                    workNode=root;
                    //每当解码一个字符,就将工作指针从新指向root
                }
            }
            unsigned char* l=new unsigned char[writeCache.length()];
            for(int i=0;i<writeCache.length();i++){
                l[i]=writeCache.at(i).toLatin1();
            }
            qDebug()<<allLength+writeCache.length();
            deStream.writeRawData((char*)l,writeCache.length());
            deFile.close();
            inFile.close();
            return;

        }
        //当读剩下的长度小于256,且刚好上一个码解码完毕,那么就结束
        qint64 readMax=readCache.length()-256;
        qint64 nowNum=0;        //当前
        HoffmanNode* workNode=root;
        QString writeCache;
        qint64 i=0;
        while (!(workNode==root&&nowNum>readMax)) {
            if(readCache.at(nowNum)=='0'){
                workNode=workNode->left;
            }else{
                workNode=workNode->right;
            }
            if(workNode->isLastNode()){
                //当搜索到尾部节点,就把叶节点的字符加进去
                writeCache.append(workNode->key);
                i++;
                workNode=root;
                //每当解码一个字符,就将工作指针从新指向root
            }
            nowNum++;
        }
        readCache=readCache.mid(nowNum);
        unsigned char *l=new unsigned char[i];
        for(qint64 j=0;j<i;j++){
            l[j]=writeCache.at(j).toLatin1();
        }
        allLength+=writeCache.length();
        deStream.writeRawData((char*)l,writeCache.length());
        delete[] l;
        //deStream<<writeCache;


    }




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

unsigned char Hoffman::toUChar(const QString &str)
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
