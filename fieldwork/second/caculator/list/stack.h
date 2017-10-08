#ifndef STACK_H
#define STACK_H
#include"stable.h"
#include"doubleList.h"
template<typename T>
class Stack
{
public:
    Stack();
    ~Stack();
    bool push(T t);
    T pop();
    T top();
    bool empty();
    int getLength();
    void clear();
protected:
    DoublyList<T> list;
};
template<typename T>
Stack<T>::Stack()
{


}


template<typename T>
Stack<T>::~Stack()
{
}

template<typename T>
bool Stack<T>::push(T t)
{
    list.append(t);
    return true;
}


template<typename T>
T Stack<T>::pop()
{
    if(list.empty()){
        throw QString("栈为空,无法出栈顶");
    }
    else{
        T t=list.getLast()->date;
        list.deleteLast();
        return t;
    }

}


template<typename T>
T Stack<T>::top()
{
    if(list.empty()){
        qDebug()<<"栈为空，无栈顶元素";
        throw "error";
    }else {
        return list.getLast()->date;
    }
}

template<typename T>
bool Stack<T>::empty()
{
    return list.empty();
}

template<typename T>
int Stack<T>::getLength()
{
    return list.getSize();

}

template<typename T>
void Stack<T>::clear()
{
    list.makeEmpty();

}

#endif // STACK_H
