#include"kmintree.h"
#include<QVector>
#include<QDebug>
KMinTree::KMinTree(int capacity):
    AMMap<QString>(capacity)
{
    this->setTMap(MapType::undirMap);
}

KMinTree::KMinTree(const AMMap<QString> &old):
    AMMap<QString>(old)
{

}





KMinTree::~KMinTree()
{

}



AMMap<QString> KMinTree::getMinTree()
{
    //申请容量为节点数的作为结果树
    AMMap<QString> result(this->m_iNodeCount);
    //先把所有的边存到集合里
    SList<MinEdge> edges;
    QVector<QVector<int>> nodeVec;
    for(int i=0;i<this->m_iNodeCount;i++){
        result.addNode(this->getValue(i));
        for(int j=0;j<i;j++){
            if(this->edge(i,j)!=INT32_MAX){
                edges.append(MinEdge(i,j,this->edge(i,j)));
            }
        }
    }
    //用自己写的排序函数将边集排序
    edges.sort(true);

    SNode<MinEdge>* workNode=edges.getFirst();
    while (workNode&&result.NumberOfEdges()!=this->m_iNodeCount-1) {
        MinEdge a=workNode->date;
        int nodeAInSetIndex=-1;
        int nodeBInSetIndex=-1;
        for(int i=0;i<nodeVec.size();i++){
            for(int j=0;j<nodeVec[i].size();j++){
                if(nodeVec[i][j]==a.index1){
                    nodeAInSetIndex=i;
                }
                if(nodeVec[i][j]==a.index2){
                    nodeBInSetIndex=i;
                }
            }
        }
        if(nodeAInSetIndex==-1){
            if(nodeBInSetIndex==-1){
                QVector<int> vec;
                vec.append(a.index1);
                vec.append(a.index2);
                nodeVec.append(vec);
            }else {
                nodeVec[nodeBInSetIndex].append(a.index1);
            }
        }else {
            if(nodeBInSetIndex==-1){
                nodeVec[nodeAInSetIndex].append(a.index2);
            }else {
                //如果两个点在同的集合里
                if(nodeAInSetIndex==nodeBInSetIndex){
                    //如果已经在同一个集合里，也就是说，会形成环形
                    workNode=workNode->link;
                    continue;
                }else{
                //，那么就把这两个集合合并
                nodeVec[nodeAInSetIndex]+=nodeVec[nodeBInSetIndex];
                nodeVec.removeAt(nodeBInSetIndex);
                }
            }
        }
        result.insertEdge(a.index1,a.index2,a.weight);
        workNode=workNode->link;
    }
    return result;
}

QList<MinEdge> KMinTree::getEdge()
{
    QList<MinEdge> a;
    for(int i=0;i<this->m_iNodeCount;i++){
        for(int j=0;j<i;j++){
            if(this->edge(i,j)!=INT32_MAX){
                a.append(MinEdge(i,j,this->edge(i,j)));
            }
        }
    }
    return a;
}



//void KMinTree::logVset()
//{
//    for(int i=0;i<7;i++){
//        qDebug()<<vset[i*this->m_iNodeCount+0]<<\
//                  vset[i*this->m_iNodeCount+1]<<\
//                  vset[i*this->m_iNodeCount+2]<<\
//                  vset[i*this->m_iNodeCount+3]<<\
//                  vset[i*this->m_iNodeCount+4]<<\
//                  vset[i*this->m_iNodeCount+5]<<\
//                  vset[i*this->m_iNodeCount+6];
//    }
//}

//bool KMinTree::addMap(int a, int b)
//{
//    //增加一条新的边的时候
//    //也就是说，a
//    for(int i=0;i<this->m_iNodeCount;i++){
//        if(loc(a,i)){
//            //也就是说，i任何与a联通的量，都会与b联通
//            if(!loc(i,b)){
//                setV(i,b);
//                addMap(i,b);
//            }
//        }
//        if(loc(b,i)){
//            if(!loc(i,a)){
//                setV(i,a);
//                addMap(i,a);
//            }
//        }
//    }
//}
