#pragma once
#include<iostream>
struct Item
{
	int data;
	Item* link;
};
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList& old);
	virtual ~LinkedList();
	
	bool  append(const int& num);
	bool insertBefore(int index,const int& data);  //在第index前面插入
	bool insertBehind(int index, const int& data);	//在第index后面插入
	int deleteItem(int index);
	int getData(int i) const;	//取出第i元素值
	void setData(int i, int x);		//更新第i元素值

	bool sortJ();		//降序排,不增加空间复杂度
	bool sortZ();		//增序排序
	Item* indexAt(int index) const;          /*类似数组，0 为第一个，1为第二个*/
	bool makeEmpty();


	LinkedList& operator<<(int num);
	//合并算法
	/*
		设ha和hb分别是两个带表头结点的非递减有序单链表的表头指针，试设计一个算法，
		将这两个有序链表合并成一个非递增有序的单链表。
	*/
	bool Merge(LinkedList& list);

	//cout?
	void output();
	
protected:
	/*
	* 把一个位置的切出来，但是空间不delete掉
	* index 从0开始
	* 因为空间并不会delete，但是地址返回来了，所以设置为protect
	*/
	Item * head;
	int size;
	Item* last;
	Item* getItemAt(int index);	
};

