#pragma once
#include<iostream>
using namespace std;
//单向链表
template<typename T>
struct DListNode {
	T date;
	DListNode* RLink;
	DListNode* LLink;
	DListNode(DListNode<T> *l=0,DListNode<T>* r=0) {
		LLink = l;
		RLink = r;
	}
	DListNode(T t, DListNode<T> *l, DListNode<T>* r) {
		date = t;
		LLink = l;
		RLink = r;
	}
};


template<typename T>
class DoublyList
{
public:
	DoublyList();
	virtual ~DoublyList();
	bool prepend(T t);		//在头上插入
	bool append(T t);		//在尾部追加
	void makeEmpty();						//清空链表，保存头节点

	DoublyList<T>& operator<<(T t);
	int getSize();

	DListNode<T>* locate(int index);
	DListNode<T>* getFirst();
	DListNode<T>* getLast();
	void output();
protected:
	DListNode<T>* first;
	DListNode<T>* last;
	int size;
};

template<typename T>
inline DoublyList<T>::DoublyList()
{
	first = new DListNode<T>;
	last = first;
}

template<typename T>
inline DoublyList<T>::~DoublyList()
{
	makeEmpty();
	delete first;
	first = NULL;
}

template<typename T>
inline bool DoublyList<T>::prepend(T t)
{
	DListNode<T>* newNode = new DListNode<T>(t, first, first->RLink);
	if (!newNode->RLink) {
		last = newNode;
	}
	else
	{
		first->RLink = newNode;
		newNode->RLink->LLink = newNode;
	}
	
	return true;
}

template<typename T>
inline bool DoublyList<T>::append(T t)
{
	DListNode<T>* newNode = new DListNode<T>(t, last, NULL);
	last->RLink = newNode;
	last = last->RLink;
	return false;
}

template<typename T>
inline void DoublyList<T>::makeEmpty()
{
	
	while (first->RLink)
	{
		DListNode<T>* item = first->RLink;
		first->RLink = item->RLink;
		delete item;
	}
	first->RLink = NULL;
	last = first;
}
