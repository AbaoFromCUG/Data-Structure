#ifndef ADMAP_H
#define ADMAP_H
#include"vmap.h"
/*
 *
 * 以下类的基类
 * 邻接表
 *  1. 有向图-邻接表　　Dir_ADMap
 *  2. 无向图-邻接表  Undir_ADMap
 * 邻接多重表
 *  1.无向图-邻接多重表
 */


//D代表点存的数据类型
//ADEdge代表边的结构体类型
template<typename D,typename ADEdge>
struct ADNode
{
    ADNode(D data=D(),ADEdge* edge=nullptr) {
        this->m_data=data;
        this->m_edge=edge;
    }
    D m_data;   //存储了顶点的数据域
    ADEdge * m_edge;     //指向连接该顶点的边的指针
};
//参数模板是T: 代表边存的数据类型
template<typename T>
struct ADEdge{

    ADEdge(int index,T data,ADEdge<T>* next=nullptr);
    int m_iV;   //弧头顶点索引
    T m_data;     //弧数据
    ADEdge<T> * m_eNext;  //下一条弧指针
};
template<typename T>
ADEdge<T>::ADEdge(int index, T data, ADEdge<T> *next){
    this->m_iV=index;
    this->m_data=data;
    this->m_eNext=next;
}


//ADMap的模板参数分别是 V: 顶点存的数据类型,和 T:边的数据域数据类型
template<typename V,typename T>
class ADMap:
        //VMap//模板参数是,节点的结构体类型，节点存储的数据类型和边存储的数据类型
        public VMap<ADNode<V,ADEdge<T>>,V,T>
{
public:
    ADMap(int capacity);

    ADMap(const ADMap<V,T>& old);
};



template<typename V, typename T>
ADMap<V,   T>::ADMap(int capacity):
    VMap<ADNode<V,ADEdge<T>>,V,T>(capacity)
{
    this->setTSave(SaveType::AdjacencyList);
}


template<typename V, typename T>
ADMap<V,   T>::ADMap(const ADMap<V,   T> &old):
    VMap<ADNode<V,ADEdge<T>>,V,T>(old)
{
    this->setTSave(SaveType::AdjacencyList);
}


#endif // ADMAP_H
