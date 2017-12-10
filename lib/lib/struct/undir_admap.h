#ifndef UNDIR_ADMAP_H
#define UNDIR_ADMAP_H
#include"dir_admap.h"

//无向图-邻接表

//为了偷懒的宏定义，，真的是懒得写了
#define dirParent Dir_ADMap<D,T>
#define UA_edge Undir_ADEdge<T>
#define UA_node ADNode<D,Undir_ADEdge<T>>

#define  Undir_ADEdge<T> Dir_ADEdge<T>;

//模板参数分别是点存的数据类型,和边存的数据类型
template<typename D,typename T>
class Undir_ADMap:
    public dirParent
{
public:
    Undir_ADMap(int capacity):
        dirParent(capacity)
    {
        this->setTMap(MapType::undirMap);
        this->setTSave(SaveType::AdjacencyList);
    }
    Undir_ADMap(const Undir_ADMap<D,T>& old):
        dirParent(old)
    {
        this->setTMap(MapType::undirMap);
        this->setTSave(SaveType::AdjacencyList);
    }
    virtual void insertEdge(int v1, int v2, T cost);
    virtual void setEdge(int v1,int v2,T cost);
    virtual void updateEdge(int v1, int v2, T cost);

    virtual void removeEdge (int v1, int v2);

    //下面的几个函数都可以直接用有向图的，真的是无聊
    //但是，你也可以针对无向图进行优化
    //比如移除一个点的函数，
    //可以针对其特性进行优化，
    //由v出发的边，所连接点有a,c,d的话，
    //我们在移除其他点上的重边的时候，就只需要关注与a,c,d
    //但是我懒！！！！
//    virtual void removeVertex (int v);
//    virtual D getValue (int i);
//    virtual int getWeight (int v1, int v2);

//    virtual void breadthFirstTraverse(int from,auto fun);
//    virtual void depthFirstTraverse(int from,auto fun);
};



template<typename D, typename T>
void Undir_ADMap<D,T>::insertEdge(int v1, int v2, T cost)
{
    dirParent::insertEdge(v1,v2,cost);
    dirParent::insertEdge(v2,v1,cost);
}

template<typename D, typename T>
void Undir_ADMap<D,T>::setEdge(int v1, int v2, T cost)
{
    dirParent::setEdge(v1,v2,cost);
    dirParent::setEdge(v2,v1,cost);
}

template<typename D, typename T>
void Undir_ADMap<D,T>::updateEdge(int v1, int v2, T cost)
{
    dirParent::updateEdge(v1,v2,cost);
    dirParent::updateEdge(v2,v1,cost);
}

template<typename D, typename T>
void Undir_ADMap<D,T>::removeEdge(int v1, int v2)
{
    dirParent::removeEdge(v1,v2);
    dirParent::removeEdge(v2,v1);
}


//下面的注释，实在是，非常无聊
//    //恶魔妈妈摸妹妹
//    //emmmmmmm
//    //实在是看不出有向图的索算法和无向图的搜索算法有什么区别,,
//template<typename D, typename T>
//void Undir_ADMap<D,T>::removeVertex(int v)
//{
//    dirParent;:removeVertex(v);
//}

//template<typename D, typename T>
//D Undir_ADMap<D,T>::getValue(int i)
//{
//    return dirParent::getValue(i);
//}

//template<typename D, typename T>
//int Undir_ADMap<D,T>::getWeight(int v1, int v2)
//{
//    return dirParent::getWeight(v1,v2);
//}


//template<typename D, typename T>
//void Undir_ADMap<D,T>::depthFirstTraverse(int from, auto fun)
//{


//}

//template<typename D, typename T>
//void Undir_ADMap<D,T>::breadthFirstTraverse(int from, auto fun)
//{

//}
#endif // UNDIR_ADMAP_H
