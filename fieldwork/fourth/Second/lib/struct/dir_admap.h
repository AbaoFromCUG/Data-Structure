#ifndef DIR_ADMAP_H
#define DIR_ADMAP_H
#include<limits>
#include<limits.h>
#include"admap.h"
#include"sstack.h"
#include"squeque.h"


//有向图-邻接表


/*
 * 一些懒得写太长的宏定义
 */
#define DA_edge ADEdge<T>
#define DA_node ADNode<D,ADEdge<T>>




/*
 * 模板参数
 * D: 点存的数据类型
 * T: 边存的数据类型
 */

template<typename D,typename T>
class Dir_ADMap:
        public ADMap<D,T>
{
public:
    Dir_ADMap(int capacity):
        ADMap<D,T>(capacity)
    {
        this->m_tMap=MapType::dirMap;//有向
    }
    Dir_ADMap(const Dir_ADMap<D,T>& old);
    ~Dir_ADMap();


    void breadthFirstTraverse(int from,auto fun);
    void depthFirstTraverse(int from,auto fun);

    //实现的函数
    virtual void insertEdge(int v1, int v2, int cost);
    virtual void setEdge(int v1,int v2,int cost);
    virtual void updateEdge(int v1, int v2, T cost);
    virtual void removeEdge (int v1, int v2);
    virtual void removeVertex (int v);
    virtual D getValue (int i);
    virtual T getWeight (int v1, int v2);

    //一个测试函数，没什么用的
    void printSelf();


protected:
    void deleteEdgeList(DA_edge** edge);
};





template<typename D, typename T>
Dir_ADMap<D,T>::~Dir_ADMap(){
    //析构函数
    for(int i=0;i<this->m_iNodeCount;i++){
        this->deleteEdgeList(&this->m_pNodeArray[i].m_edge);
    }
}
template<typename D, typename T>
Dir_ADMap<D,T>::Dir_ADMap(const Dir_ADMap<D, T> &old):
    ADMap<D,T>(old)
{
    for(int i=0;i<this->m_iNodeCount;i++){
        //先把节点链的节点复制
        /*
         * 老师要用指针来用，
         * but　，
         * 二级指针不是一样的？
         */
        this->m_pNodeArray[i].m_data=old.m_pNodeArray[i].m_data;
        DA_edge** edge=&this->m_pNodeArray[i].m_edge;
        DA_edge** oldEdge=&old.m_pNodeArray[i].m_edge;
        while (*oldEdge) {
            //实现边的拷贝
            (*edge)=new DA_edge((*oldEdge)->m_iV,(*oldEdge)->m_data);
            oldEdge=&(*oldEdge)->m_eNext;
            edge=&(*edge)->m_eNext;
        }

    }
}

template<typename D, typename T>
void Dir_ADMap<D,T>::breadthFirstTraverse(int from,auto fun)
{
    if(from>=this->m_iNodeCount||from<0){
        throw "error !!!,because from is !!!";
    }
    if(this->m_iNodeCount<1){
        return ;
    }else if (this->m_iNodeCount==1) {
        fun(this->m_pNodeArray,nullptr);
    }
    //fun的类型//
    //邻接表存有向带权图
    //广度优先算法

    bool *isVisit=new bool[this->m_iNodeCount];
    for(int i=0;i<this->m_iNodeCount;i++){
        isVisit[i]=false;
    }
    fun(this->m_pNodeArray+from,nullptr);    //访问开始的节点
    isVisit[from]=true;


    SQueque<int> s;//保存下标的队列
    s.enqueque(from);
    while (!s.isEmpty()) {
        //获得头结点的弧指针（出弧指针）
        DA_edge* workEdge=this->m_pNodeArray[s.getFirstData()].m_edge;
        while (workEdge) {
            //
            int toIndex=workEdge->m_iV;
            if(!isVisit[toIndex]){
                fun(this->m_pNodeArray+toIndex,workEdge);    //传入将要访问的点和走的边
                isVisit[toIndex]=true;
                s.enqueque(toIndex);
            }
            workEdge=workEdge->m_eNext;
        }
        s.dequeque();//出队列
    }
    delete []isVisit;
}

template<typename D, typename T>
void Dir_ADMap<D,T>::depthFirstTraverse(int from,auto fun)
{
    if(from>=this->m_iNodeCount||from<0){
        throw "error !!!,because from is error!!!";
    }
    if(this->m_iNodeCount<1){
        throw "map is empty";
        return ;
    }else if (this->m_iNodeCount==1) {
        fun(this->m_pNodeArray,nullptr);
    }
    /*
     * 深度优先算法，栈式的，，，，
     * 在我写这段代码时，只有我和上帝知道怎么写
     * 现在只有上帝了
     */

    bool *isVisit=new bool[this->m_iNodeCount];
    for(int i=0;i<this->m_iNodeCount;i++){
        isVisit[i]=false;
    }
    fun(this->m_pNodeArray+from,nullptr);
    isVisit[from]=true;
    int workIndex=from;
    SStack<int> s;  //保存栈向前搜索的节点
    SStack<DA_edge*> n;  //保存对应没有搜索过的边链
    s.push(from);
    n.push(this->m_pNodeArray[from].m_edge);
    DA_edge* edge;      //中转的指针
    edge=this->m_pNodeArray[workIndex].m_edge;
    while (!s.isEmpty()) {
        if(edge){
            if(isVisit[edge->m_iV]){
                //如果已经访问过了，那就跳过这个节点
                edge=edge->m_eNext;
            }else {
                //如果没有访问过目标节点，
                //那么保存当前的状态
                s.push(workIndex);
                n.push(edge->m_eNext);
                workIndex=edge->m_iV;
                fun(this->m_pNodeArray+workIndex,edge);
                isVisit[workIndex]=true;
                edge=this->m_pNodeArray[workIndex].m_edge;
            }
        }else{
            workIndex=s.pop();
            edge=n.pop();
        }

    }
    delete []isVisit;
}

template<typename D, typename T>
void Dir_ADMap<D,T>::insertEdge(int v1, int v2, int cost)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    //v1是起始点
    DA_edge** edge=&this->m_pNodeArray[v1].m_edge;
   //这里重构了一次，代码更加整洁
    while ((*edge)&&(*edge)->m_iV!=v2) {
        edge=&(*edge)->m_eNext;
    }
    if(*edge){
        throw "sorry ,there is a edge";
    }else {
        //如果没有找到这条边，那么就追加上这条边
        (*edge)=new DA_edge(v2,cost);
    }
}

template<typename D, typename T>
void Dir_ADMap<D,T>::setEdge(int v1, int v2, int cost)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    //这里也重构了一下，统一遍历方法
    DA_edge** edge=&this->m_pNodeArray[v1].m_edge;
    while ((*edge)&&(*edge)->m_iV!=v2) {
        edge=&(*edge)->m_eNext;
    }
    if(*edge){
        (*edge)->m_data=cost;
    }else{
        (*edge)=new DA_edge(v2,cost);
    }
}

template<typename D, typename T>
void Dir_ADMap<D,T>::updateEdge(int v1, int v2, T cost)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    DA_edge** edge=&this->m_pNodeArray[v1].m_edge;
   //这里重构了一次，代码更加整洁
    while ((*edge)&&(*edge)->m_iV!=v2) {
        edge=&(*edge)->m_eNext;
    }
    if(*edge){
            (*edge)=new DA_edge(v2,cost);
    }else {
        //如果没有找到这条边，那么就异常

        throw "sorry ,there is a edge";
    }
}

template<typename D, typename T>
void Dir_ADMap<D,T>::removeEdge(int v1, int v2)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    //移除一条边，下面这个方法是比较优美的
    DA_edge** edge=&this->m_pNodeArray[v1].m_edge;
    while ((*edge)&&(*edge)->m_iV!=v2) {
        edge=&(*edge)->m_eNext;
    }
    if(*edge){
        DA_edge*del=(*edge);
        (*edge)=(*edge)->m_eNext;
        delete del;  //删除边
        this->m_iEdgeCount--;
    }else {
        throw "there is No edge";
    }
}

template<typename D, typename T>
void Dir_ADMap<D,T>::removeVertex(int v)
{
    if(v<0||v>=this->m_iNodeCount){
        throw "out of range";
    }

    //以下是愚蠢的代码
    this->deleteEdgeList(&this->m_pNodeArray[v].m_edge);
    this->m_pNodeArray[v].m_data=this->m_pNodeArray[this->m_iNodeCount-1].m_data;
    this->m_pNodeArray[v].m_edge=this->m_pNodeArray[this->m_iNodeCount-1].m_edge;
    this->m_pNodeArray[this->m_iNodeCount-1].m_edge=nullptr;
    //接下来使用搜索算法搜索其他相关的边，删除掉
    for(int i=0;i<this->m_iNodeCount-1;i++){
        DA_edge** edge=&this->m_pNodeArray[i].m_edge;
        while (*edge) {
            if((*edge)->m_iV==v){
                DA_edge* delEdge=(*edge);
                (*edge)=(*edge)->m_eNext;
                delete delEdge;
                if(*edge){
                    //如果不是当前节点最后的一个　边，记得要往后搜索
                    //这个可以防止多重边
                    edge=&(*edge)->m_eNext;
                }
            }else {
                edge=&(*edge)->m_eNext;
            }
        }
    }
    //以下是更加愚蠢且没有用的代码
//    this->breadthFirstTraverse(0,[&](const DA_node* &n,const DA_edge* &e){
//        if(e&&e->m_iV==v){
//            if(e->m_eNext){
//                DA_edge* del=e->m_eNext;
//                e->m_eNext=e->m_eNext->m_eNext;
//                e->m_data=e->m_eNext->m_data;
//                e->m_iV=e->m_eNext->m_iV;
//                delete del;
//            }else {
//                delete e;
//                e=nullptr;
//            }
//        }
//    });
    this->m_iNodeCount--;
}

template<typename D, typename T>
D Dir_ADMap<D,T>::getValue(int i)
{
    if(i<this->m_iNodeCount&&i>=0){
        return this->m_pNodeArray[i].m_data;
    }else {
        throw "out of length";
    }
}



template<typename D, typename T>
T Dir_ADMap<D,T>::getWeight(int v1, int v2)
{
    if(v1>this->m_iNodeCount||v1<0){
        throw "error ,the row value is out of range";
    }

    if(v2>this->m_iNodeCount||v2<0){
        throw "error ,the col value is out of range";
    }
    DA_edge* edge=this->m_pNodeArray[v1].m_edge;
    while (edge&&edge->m_iV!=v2) {
        edge=edge->m_eNext;
    }
    if(edge){
        return edge->m_data;
    }else {
        throw "error, edge is null";
    }

}

template<typename D, typename T>
void Dir_ADMap<D,T>::printSelf(){
    for(int i=0;i<this->m_iNodeCount;i++){
        DA_node* node=this->m_pNodeArray+i;
        DA_edge** edge=&node->m_edge;
        while (*edge) {
            cout<<"节点"<<this->m_pNodeArray[i].m_data<<"出边"<<(*edge)->m_data<<"  连接的是下标"<<(*edge)->m_iV<<endl;
            edge=&(*edge)->m_eNext;
        }
    }
}

template<typename D, typename T>
void Dir_ADMap<D,T>::deleteEdgeList(DA_edge **edge)
{
    while (*edge) {
        DA_edge* del=*edge;
        edge=&(*edge)->m_eNext;
        delete del;
    }
    (*edge)=nullptr;
}
#endif // DIR_ADMAP_H

