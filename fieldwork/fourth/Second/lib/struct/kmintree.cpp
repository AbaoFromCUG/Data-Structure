#include"kmintree.h"
#include<QList>
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
        vset[a.index1*this->m_iNodeCount+a.index2]=true;
        vset[a.index2*this->m_iNodeCount+a.index1]=true;
        r[a.index1].append(a);
        r[a.index2].append(a.getT());
        workNode=workNode->link;
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
