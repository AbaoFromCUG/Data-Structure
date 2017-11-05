#include "decoder.h"

DeCoder::DeCoder(QObject *parent) : QObject(parent)
{

}

void DeCoder::deCodeFile(QString fromName)
{
    m_fromName=fromName;
    getToName();
    signal_deCoder(0,2);
    makeTree();
    signal_deCoder(1,5);
    deCode();
    signal_deCoder(3,100);

}

void DeCoder::getToName()
{
    QFile file(m_fromName);
    file.open(QIODevice::ReadOnly);
    QDataStream inStream(&file);
    QString str;
    inStream>>str;

    str=str.mid(0,str.length()-1);
    QStringList list=str.split('#');

    m_toName=QFileInfo(list[1]).path()+"/hoff_"+QFileInfo(list[1]).fileName();
    for(int i=0;i<256;i++){
        countArray[i]=list[2+i].toDouble();
    }
}


void DeCoder::makeTree()
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
        list[num1]=new HoffmanNode(list[num1]->weight+list[num2]->weight,list[num1],list[num2]);
        list[num2]=0;
    }

}

void DeCoder::deCode()
{
    //用于统计工作量的两个数字
    QFileInfo infor(m_fromName);
    double countTimes=infor.size()/1024000+1;
    qint64 countSize=0;


    qint64 allLength=0;
    QFile inFile(m_fromName);
    QFile deFile(m_toName);
    inFile.open(QIODevice::ReadOnly);
    deFile.open(QIODevice::WriteOnly);
    QDataStream inStream(&inFile);
    QDataStream deStream(&deFile);
    QString header;
    inStream>>header;  //刷掉前面的头部信息


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
        countSize++;
        emit signal_deCoder(2,countSize/countTimes*100);


    }




}
