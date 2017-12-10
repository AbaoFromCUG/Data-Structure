#pragma once

#include"vmap.h"
#include"slist.h"
#include"squeque.h"
#include<iostream>

#include"sstack.h"
using namespace std;


#include"limits.h"

#include"dir_admap.h"
#include"undir_admap.h"



//Adjacency Matrix
//邻接矩阵法---带权---{有向or 无向}
/*
 * 邻接矩阵法需要两个变量
 * 第一个：顶点数组（继承而来）
 * 第二个：记录了边的int型的数组（二维数组）值，０代表不存在，大于１的权重
 *
 */




template<typename T>
struct AMNode
{
	T data;
};


//模板参数D是点的数据域的数据类型
template<typename D>
class AMMap :
    public VMap<AMNode<D>,D,int>
{
public:
	AMMap(int capacity);
    AMMap(const AMMap<D>& old);     //拷贝构造函数
	~AMMap();


    //广度优先:队列式
    void *breadthFirstTraverse(int,auto fun);
    //深度优先：栈式
    void* depthFirstTraverse(int,auto fun);

    int edge(int row,int col);

    Dir_ADMap<D,int> toDir_ADMap();     //提供转换的函数
    Undir_ADMap<D,int> toUndir_ADMap(); //提供转换到无向图的函数

    //实现的函数
    virtual void insertEdge(int v1, int v2, int cost);
    virtual void setEdge(int v1,int v2,int cost);
    virtual void removeEdge (int v1, int v2);
    virtual void removeVertex (int v);
    virtual D getValue (int i);
    virtual int getWeight (int v1, int v2);

    //两个废弃了的方法
//    void setVauleToMatrixForDirectedGraph(int row,int col,int val=1);
//    void setVauleToMatrixForUndirectedGraph(int row,int col,int val=1);
protected:
    int* m_iMatrix;	//邻接矩阵
};


template<typename D>
inline AMMap<D>::AMMap(int capacity):
    VMap<AMNode<D>,D,int>(capacity)
{
    this->setTSave(SaveType::AdMatrix);         //邻接矩阵的存储方式
    this->m_iMatrix = new int[capacity*capacity];
    //将矩阵数组设置为0，即代表没有链接的边
    for(int i=0;i<capacity*capacity;i++){
        this->m_iMatrix[i]=INT32_MAX;       //初始化为极大值
    }
}

template<typename D>
AMMap<D>::AMMap(const AMMap<D> &old):
    VMap<AMNode<D>,D,int>(old)  //调用父类的构造函数
{
    this->setTSave(SaveType::AdMatrix);         //邻接矩阵的存储方式
    this->m_iMatrix = new int[this->m_iCapacity*this->m_iCapacity];
    //将矩阵数组设置为0，即代表没有链接的边
    for(int i=0;i<this->m_iCapacity*this->m_iCapacity;i++){
        this->m_iMatrix[i]=old.m_iMatrix[i];       //初始化为极大值
    }
}

template<typename D>
inline AMMap<D>::~AMMap()
{
    delete[] this->m_iMatrix;
}

//template<typename D>
//void AMMap<D>::setVauleToMatrixForDirectedGraph(int row, int col, int val)
//{
//    if(row>this->m_iCapacity||row<0){
//        throw "error ,the row value is out of range";
//    }

//    if(col>this->m_iCapacity||col<0){
//        throw "error ,the col value is out of range";
//    }

//    m_iMatrix[row*this->m_iCapacity+col]=val;
//}

//template<typename D>
//void AMMap<D>::setVauleToMatrixForUndirectedGraph(int row, int col, int val)
//{
//    if(row>this->m_iCapacity||row<0){
//        throw "error ,the row value is out of range";
//    }

//    if(col>this->m_iCapacity||col<0){
//        throw "error ,the col value is out of range";
//    }

//    m_iMatrix[row*this->m_iCapacity+col]=val;
//    m_iMatrix[col*this->m_iCapacity+row]=val;

//}


template<typename D>
void *AMMap<D>::breadthFirstTraverse(int from,auto fun)
{
    if(from>=this->m_iNodeCount||from<0){
        throw "error !!!,because from is !!!";
    }
    if(this->m_iNodeCount<1){
        return nullptr;
    }else if (this->m_iNodeCount==1) {
        fun(this->m_pNodeArray,INT32_MAX);
    }
    /*
     * 队列
     * 广度优先算法
     */
    SQueque<int> s;     //队列
    bool *isVisit=new bool[this->m_iNodeCount];
    for(int i=0;i<this->m_iNodeCount;i++){
        isVisit[i]=false;
    }
    s.enqueque(from);      //把第一个节点入队列
    fun(this->m_pNodeArray+from,INT32_MAX);      //先把第一个节点访问
    isVisit[from]=true;
    int workIndex=from;
    while (!s.isEmpty()) {
        workIndex=s.getFirstData();
        for(int i=0;i<this->m_iNodeCount;i++){
            bool iv=isVisit[i];
            int e=this->edge(workIndex,i);
            if(iv||e==INT32_MAX){
                continue;
            }else {
                fun(this->m_pNodeArray+i,e);        //传入边与下一个要访问的节点
                isVisit[i]=true;
                s.enqueque(i);  //如果没有访问过，那么就入队列
            }
        }
        s.dequeque();       //出队列

    }
    delete []isVisit;
}


template<typename D>
void *AMMap<D>::depthFirstTraverse(int from,auto fun)
{
    if(from>=this->m_iNodeCount||from<0){
        throw "error !!!,because from is !!!";
    }
    if(this->m_iNodeCount<1){
        return nullptr;
    }else if (this->m_iNodeCount==1) {
        fun(this->m_pNodeArray,INT32_MAX);
    }
    bool* isVisit=new bool[this->m_iNodeCount];
    for(int i=0;i<this->m_iNodeCount;i++){
        isVisit[i]=false;
    }
    //因为深度优先不能用递归,所以就只能用栈
    /*
     * 代码说明
     * 非递归式深度优先搜索图
     * 传入的函数必须是形如void *Fun(Node* v,Edge* e);
     */
    SStack<int> s;  //保存当前栈里的节点下标
    SStack<int> ss;  //保存当前访问到的边
    int workIndex=from;
    int a=0;
    fun(this->m_pNodeArray+from,INT32_MAX); //访问第一个节点ex
    isVisit[from]=true;
    s.push(workIndex);
    ss.push(0);
    while (!s.isEmpty()) {
        if(a<this->m_iNodeCount){
            int e=edge(workIndex,a);
            bool iv=isVisit[a];
            if(e==INT32_MAX|| iv){
                //跳过不存在的边和访问过的点
                a++;
            }else {
                //否则,通过这条边访问下一个节点
                fun(this->m_pNodeArray+a,edge(workIndex,a));
                isVisit[a]=true;
                s.push(a+1);
                ss.push(workIndex);
                workIndex=a;
                a=0;
            }
        }else {
            a=s.pop();
            workIndex=ss.pop();
        }
    }
    delete []isVisit;
}

template<typename D>
int AMMap<D>::edge(int row, int col)
{
    int a=m_iMatrix[row*this->m_iCapacity+col];
    //cout<<"|<--"<<a<<"-->|";
    return a;
}

template<typename D>
Dir_ADMap<D,int> AMMap<D>::toDir_ADMap()
{
    if(this->m_tMap==MapType::undirMap){
        throw "error, this map is undirMap";
    }
    /*
     * 讲老实话，这个方法并不好，
     * 相当于在Dir_ADMap<D,int>类内部挖了个洞，
     * 需要直接操纵Dir_ADMap<D,int>的保护型成员
     */
    Dir_ADMap<D,int> result(this->m_iCapacity);
    result.setNodeCount(this->m_iNodeCount);
    result.setEdgeCount(this->m_iEdgeCount);
    for(int i=0;i<this->m_iNodeCount;i++){
        result.getNodeArray()[i].m_data=this->m_pNodeArray[i].data;
        ADEdge<int>** edge=&result.getNodeArray()[i].m_edge;
        for(int j=0;j<this->m_iNodeCount;j++){
            if(getWeight(i,j)!=INT32_MAX){
                (*edge)=new ADEdge<int>(j,getWeight(i,j));
                edge=&(*edge)->m_eNext;
            }
        }
    }
    return result;
}

template<typename D>
Undir_ADMap<D, int> AMMap<D>::toUndir_ADMap()
{
    if(this->m_tMap==MapType::dirMap){
        throw "error, this map is dirMap";
    }
    Undir_ADMap<D,int> result(this->m_iCapacity);
    result.setNodeCount(this->m_iNodeCount);
    result.setEdgeCount(this->m_iEdgeCount);
    for(int i=0;i<this->m_iNodeCount;i++){
        result.getNodeArray()[i].m_data=this->m_pNodeArray[i].data;
        ADEdge<int>** edge=&result.getNodeArray()[i].m_edge;
        for(int j=0;j<this->m_iNodeCount;j++){
            if(getWeight(i,j)!=INT32_MAX){
                (*edge)=new ADEdge<int>(j,getWeight(i,j));
                edge=&(*edge)->m_eNext;
            }
        }
    }
    return result;

}

template<typename D>
void AMMap<D>::insertEdge(int v1, int v2, int cost)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    if(m_iMatrix[v1*this->m_iCapacity+v2]!=INT32_MAX){
        throw "sorry ,there is a edge";
    }else {
        m_iMatrix[v1*this->m_iCapacity+v2]=cost;
        if(this->tMap()==MapType::undirMap){
            m_iMatrix[v2*this->m_iCapacity+v1]=cost;
        }
        this->m_iEdgeCount++;
    }
}

template<typename D>
void AMMap<D>::setEdge(int v1, int v2, int cost)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    if(this->m_iMatrix[v1*this->m_iCapacity+v2]!=INT32_MAX){
        this->m_iEdgeCount++;
    }
    this->m_iMatrix[v1*this->m_iCapacity+v2]=cost;
    if(!this->tMap()==MapType::undirMap){
        this->m_iMatrix[v2*this->m_iCapacity+v1]=cost;
    }
}

template<typename D>
void AMMap<D>::removeEdge(int v1, int v2)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    if(m_iMatrix[v1*this->m_iCapacity+v2]==INT32_MAX){
        throw "sorry ,there is no edge";
    }else {
        m_iMatrix[v1*this->m_iCapacity+v2]=INT32_MAX;
        if(!this->tMap()==MapType::undirMap){
            m_iMatrix[v2*this->m_iCapacity+v1]=INT32_MAX;
        }
        this->m_iEdgeCount--;
    }
}

template<typename D>
void AMMap<D>::removeVertex(int v)
{
    if(v<0||v>=this->m_iNodeCount){
        throw "error ,the  value is out of range";
    }
    for(int i=0;i<this->m_iNodeCount;i++){
        //把最后一行的数据移动到我们需要消掉的一行
        this->setEdge(v,i,this->edge(this->m_iNodeCount-1,i));
        this->setEdge(this->m_iNodeCount-1,i,INT32_MAX);
    }

    for(int i=0;i<this->m_iNodeCount;i++){
        this->setEdge(i,v,this->edge(i,this->m_iNodeCount-1));
        this->setEdge(i,this->m_iNodeCount-1,INT32_MAX);
    }
    this->m_pNodeArray[v].data=this->m_pNodeArray[this->m_iNodeCount-1].data;
    this->m_iNodeCount--;
}

template<typename D>
D AMMap<D>::getValue(int i)
{
    if(i<this->m_iNodeCount&&i>=0){
        return this->m_pNodeArray[i].data;
    }else {
        throw "out of length";
    }
}

template<typename D>
int AMMap<D>::getWeight(int v1, int v2)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    return this->m_iMatrix[v1*this->m_iCapacity+v2];
}
