#include"kmintree.h"
#include<QList>
#include<QDebug>
KMinTree::KMinTree(int capacity):
    AMMap<QString>(capacity)
{
    result=nullptr;
    vset=nullptr;
}





KMinTree::~KMinTree()
{
    if(vset){
        delete vset;
        vset=nullptr;
    }
    if(result){
        delete result;
    }

}



AMMap<QString> KMinTree::getMinTree()
{
    vset=new bool[this->m_iNodeCount*this->m_iNodeCount];   //用来检测两个点之间是否连通
    for(int i=0;i<this->m_iNodeCount*this->m_iNodeCount;i++){
        vset[i]=false;
    }
    AMMap<QString> result(this->m_iNodeCount);
    //先把所有的边存到集合里
    SList<MinEdge> edges;
    SList<MinEdge> r[7];
    for(int i=0;i<this->m_iNodeCount;i++){
        for(int j=0;j<i;j++){
            if(this->edge(i,j)!=INT32_MAX){
                edges.append(MinEdge(i,j,this->edge(i,j)));
            }
        }
    }
    edges.sort(true);
    SNode<MinEdge>* workNode=edges.getFirst();
    while (workNode&&isSet()==-1) {
        MinEdge a=workNode->date;
        int index1=a.index1;
        int index2=a.index2;
        vset[index1*this->m_iNodeCount+index2]=true;
        vset[index2*this->m_iNodeCount+index1]=true;
        for(int t=0;t<this->m_iNodeCount;t++){
            if(vset[])
        }
        r[a.index1].append(a);
        r[a.index2].append(a.getT());
        workNode=workNode->link;
        logVset();
        qDebug()<<endl;
    }
    int i=isSet();

    return result;
}

int KMinTree::isSet()
{
    for(int i=0;i<this->m_iNodeCount;i++){
        bool a=true;
        for(int j=0;j<this->m_iNodeCount;j++){
            a=a&&vset[this->m_iCapacity*i+j];
        }
        if(a){
            return i;
        }
    }
    return -1;
}

void KMinTree::logVset()
{
    for(int i=0;i<7;i++){
        qDebug()<<vset[i*this->m_iNodeCount+0]<<\
                  vset[i*this->m_iNodeCount+1]<<\
                  vset[i*this->m_iNodeCount+2]<<\
                  vset[i*this->m_iNodeCount+3]<<\
                  vset[i*this->m_iNodeCount+4]<<\
                  vset[i*this->m_iNodeCount+5]<<\
                  vset[i*this->m_iNodeCount+6];
    }
}

bool KMinTree::loc(int v1, int v2)
{
    return vset[v1*this->m_iNodeCount+v2];
}

bool KMinTree::addMap(int a, int b)
{
    if(loc(a,b)){

    }
}
