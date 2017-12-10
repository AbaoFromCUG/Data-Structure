#ifndef SQUEQUE_H
#define SQUEQUE_H
#include"slist.h"
template<typename T>
struct SQuequeNode{

    SQuequeNode(const T& t,SQuequeNode<T>* l=nullptr){
        this->data=t;
        this->link=l;
    }

    T data;
    SQuequeNode<T> *link;
};

template<typename T>
class SQueque
{
private:
    SQuequeNode<T>* first,*last;
    int length;
public:
    SQueque();
    SQueque(const SQueque<T>& t);
    T dequeque();
    void enqueque(const T& t);
    T getFirstData();
    bool isEmpty();
};




template<typename T>
SQueque<T>::SQueque()
{
    length=0;
    last=first=nullptr;
}
template<typename T>
SQueque<T>::SQueque(const SQueque<T> &t) {
    if(t.length>0){
        first=last=new SQuequeNode<T>(t.last->data);
        SQuequeNode<T>* node=t.last->link;
        while (node) {
            last->link=new SQuequeNode<T>(node->data);
            last=last->link;
            node=node->link;
        }
    }
    length=t.length;
}
template<typename T>
T SQueque<T>::dequeque()
{
    if(length<=0){
        throw "Queque is empty";
    }else {
        T result=first->data;
        SQuequeNode<T>* node=first;
        first=first->link;
        delete node;
        length--;
        return result;
    }


}

template<typename T>
void SQueque<T>::enqueque(const T &t)
{
    if(last){
        last->link=new SQuequeNode<T>(t);
        last=last->link;
    }else {
        first=last=new SQuequeNode<T>(t);
    }
    length++;

}

template<typename T>
T SQueque<T>::getFirstData()
{
    return first->data;

}

template<typename T>
bool SQueque<T>::isEmpty()
{

    return length<=0;
}


#endif // SQUEQUE_H
