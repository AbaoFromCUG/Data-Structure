#ifndef KMINTREE_H
#define KMINTREE_H
#include"ammap.h"
#include"slist.h"
#include<QString>
using namespace std;
//用无向邻接表来实现?,
//感觉有点太罗嗦

struct MinEdge{
    int index1;  //下标一
    int index2;  //下标二
    int weight;//权重
    MinEdge(int a=-1,int b=-1,int w=-1){
        index1=a;
        index2=b;
        weight=w;
    }
    MinEdge(const  MinEdge& old){
        this->index1=old.index1;
        this->index2=old.index2;
        this->weight=old.weight;
    }
    MinEdge getT(){
        return MinEdge(index2,index1,weight);
    }

    bool operator <(const MinEdge& a){
        return weight<a.weight;
    }
    bool operator >(const MinEdge& a){
        return weight>a.weight;
    }
    bool operator ==(const MinEdge& a){
        return weight==a.weight;
    }
};


class KMinTree:public AMMap<QString>
{
public:
    KMinTree(int capacity);
    ~KMinTree();
    AMMap<QString> getMinTree();
    int isSet(); //检查联通性
    void logVset();


    bool* vset;
    bool loc(int v1,int v2);
    bool addMap(int a,int b);
private:
    AMMap<QString>* result;


};




#endif // KMINTREE_H
