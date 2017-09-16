#pragma once
#include"SuperList.h"
class LargeFactorial
{
public:
	LargeFactorial(int l);
	~LargeFactorial();
	void start(int maxNum);
	void multiplication(int num);
	void output();
	void coutItem(ListNode<int>* t);
protected:
	int storeLong;   //一个节点所存的最大数
	SuperList<int> list;	//用来存储数据的链表
	int maxNum;			//求的大数
};

