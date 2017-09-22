#pragma once
#include"DoublyList.h"
class LargeFactorial
{
public:
	LargeFactorial(int l);
	~LargeFactorial();
	void start(int maxNum);
	void output();
	void coutItem(DListNode<int>* t);
	int getSize();
protected:
	int storeLong;   //一个节点所存的最大数
	int length;		//一个节点存的位数
	DoublyList<int> list;	//用来存储数据的链表
	int maxNum;			//求的大数
};

