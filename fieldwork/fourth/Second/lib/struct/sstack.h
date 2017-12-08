#ifndef SSTACK_H
#define SSTACK_H
#include"slist.h"

template<typename D>
class SStack{
protected:
    SList<D> m_list;
public:
    SStack();
    ~SStack();
    bool push(D t);
    D pop();
    D top();
    bool isEmpty();
    int getLength();
    void clear();
};
template<typename D>
SStack<D>::SStack()
{

}

template<typename D>
SStack<D>::~SStack()
{

}

template<typename D>
bool SStack<D>::push(D t)
{
    m_list.append(t);
    return true;
}

template<typename D>
D SStack<D>::pop()
{
    if(m_list.isEmpty()){
        throw "stack is empty";
    }
    D result=m_list.getLast()->date;
    m_list.remove(m_list.getSize()-1);  //删掉末尾的数据
    return result;
}

template<typename D>
D SStack<D>::top()
{
    return m_list.getLast()->date;
}

template<typename D>
bool SStack<D>::isEmpty()
{
    return m_list.isEmpty();
}

template<typename D>
int SStack<D>::getLength()
{
    return m_list.getSize();
}

template<typename D>
void SStack<D>::clear()
{

    m_list.makeEmpty();
}




#endif // SSTACK_H

