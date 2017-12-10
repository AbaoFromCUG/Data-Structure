#pragma once
#include"ammap.h"

enum MapType{
    dirMap,
    undirMap
};


enum SaveType{
    AdMatrix,           //邻接矩阵
    AdjacencyList,      //邻接表
    CrossLinkedList,    //十字表
    AdjacentMultipleList//邻接多重表
};
/*
 * 表示链式类
 * 链式存储：
 *  １．十字链表法存有向图
 *  ２．邻接表法存有向表
 *  ３．链接多重表存无向链表
 */
//模板参数是,节点的结构体类型，节点存储的数据类型和边存储的数据类型
template<typename VN,typename V,typename T>
class VMap
{
public:
    VMap(int capacity);
    VMap(const VMap<VN,V,T>& old);
	~VMap();
    MapType tMap() const;
    void setTMap(const MapType &tMap);

    SaveType tSave() const;
    void setTSave(const SaveType &tSave);
    bool isEmpty();
    int NumberOfVertices ();      //返回当前顶点数
    int NumberOfEdges ();         //返回当前边数
    VN* getNodeArray();

    /*
     * 一些需要实现的纯虚函数
     *　抛出异常，抛出异常！！！
     */
    void addNode(V v);
    void setNodeValue(int index,V v);
    //在两个顶点之间插入边，如果边已经存在那么抛出异常
    virtual void insertEdge (int v1, int v2, T cost)=0;
    //设置两个顶点间的边，不管有没有直接设置,
    virtual void setEdge(int v1,int v2,T cost)=0;
    virtual void updateEdge(int v1,int v2,T cost)=0;
    //移除两个点间的边，如果边不存在那么抛出异常
    virtual void removeEdge (int v1, int v2)=0;
    //移除一个顶点，并把所有跟其相互关联的边删除,如果边不存在就抛出异常
    virtual void removeVertex (int v)=0;

    //取顶点 i 的值域
    virtual V getValue (int i)=0;
    //取两个顶点间权值
    virtual T getWeight (int v1, int v2)=0;



    //下面两个函数是个脏函数（影响整个封装性的函数）
    void setNodeCount(int count);
    void setEdgeCount(int count);
protected:

    int m_iCapacity;	//最大的容量
    int m_iNodeCount;	//已经存放的节点数量
    int m_iEdgeCount;   //存在的边数
    VN * m_pNodeArray;	//顶点的指针数组
    MapType m_tMap;     //图的类型  //有向图 or无向图
    SaveType m_tSave;   //保存类型

};

template<typename VN,typename V,typename T>
inline VMap<VN,V,T>::VMap(int capacity) {
	m_iCapacity = capacity;
    m_iEdgeCount=0;
	m_iNodeCount = 0;
    m_pNodeArray=new VN[capacity];
}

template<typename VN, typename V, typename T>
VMap<VN,V,T>::VMap(const VMap<VN, V, T> &old)
{
    this->m_iCapacity=old.m_iCapacity;
    this->m_iEdgeCount=old.m_iEdgeCount;
    this->m_iNodeCount=old.m_iNodeCount;
    m_pNodeArray=new VN[m_iCapacity];
}

template<typename VN,typename V,typename T>
inline VMap<VN,V,T>::~VMap() {
    delete []m_pNodeArray;
}


template<typename VN,typename V,typename T>
MapType VMap<VN,V,T>::tMap() const
{
    return m_tMap;
}
template<typename VN,typename V,typename T>
void VMap<VN,V,T>::setTMap(const MapType &tMap)
{
    m_tMap = tMap;
}
template<typename VN,typename V,typename T>
SaveType VMap<VN,V,T>::tSave() const
{
    return m_tSave;
}
template<typename VN,typename V,typename T>
void VMap<VN,V,T>::setTSave(const SaveType &tSave)
{
    m_tSave = tSave;
}

template<typename VN, typename V, typename T>
bool VMap<VN,V,T>::isEmpty()
{
    return m_iNodeCount<1;
}

template<typename VN, typename V, typename T>
int VMap<VN,V,T>::NumberOfVertices() {
    return m_iNodeCount;
}

template<typename VN, typename V, typename T>
int VMap<VN,V,T>::NumberOfEdges() {
    return m_iEdgeCount;
}

template<typename VN, typename V, typename T>
VN *VMap<VN,V,T>::getNodeArray()
{
    return m_pNodeArray;

}

template<typename VN, typename V, typename T>
void VMap<VN,V,T>::addNode(V v)
{
    if (this->m_iCapacity <= this->m_iNodeCount) {
        throw "error, out of capacity";
    }
    else
    {
        this->m_pNodeArray[this->m_iNodeCount].m_data = v;
        this->m_iNodeCount++;
    }
}
template<typename VN, typename V, typename T>
void VMap<VN,V,T>::setNodeValue(int index,V v)
{
    if(index<0||index>this->m_iNodeCount){
        throw "error,value is out of range";
    }else{
        this->m_pNodeArray[this->m_iNodeCount].m_data = v;
    }
}
template<typename VN, typename V, typename T>
void VMap<VN,V,T>::setNodeCount(int count){
    this->m_iNodeCount=count;
}

template<typename VN, typename V, typename T>
void VMap<VN,V,T>::setEdgeCount(int count)
{
    this->m_iEdgeCount=count;
}

