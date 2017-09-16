// LinkedList.cpp : 定义控制台应用程序的入口点。
//
// 


#include "stdafx.h"
#include"SuperList.h"
#include"FareyList.h"
#include<iostream>
#include <stdio.h>    
#include <sys/timeb.h> 
using namespace std;

/*
 * 实习作业一
 * 链表相关
 * Abao
 *
 * */
void logCurrentTime()
{
	struct timeb tb;
	ftime(&tb);
	printf("时间log： %d\n", tb.time);
}
template<typename T>
void recursionA(ListNode<T>* t) {
	cout << t->date << "--->";
	if (t->link) {
		recursionA(t->link);
	}
}
template<typename T>
void recursionB(ListNode<T>* t) {
	if (t->link) {
		recursionB(t->link);
	}
	cout << t->date << "--->";
}

//递增序列归并为递减序列
void fun0() {
	SuperList<int> list1;
	SuperList<int> list2;
	list1 << 1 << 3 << 5 << 7 << 9;
	list2 << 2 << 4 << 6 << 8 << 10;
	list1.merge(list2);
	list1.output();
	std::cout << "------------------------------------------" << std::endl;
	list2.output();
}

//单链表的逆置测试代码
void fun1() {
	SuperList<int> list;
	list << 12 << 23 << 56 << 12 << 89;
	cout << "--------原链表------" << endl;
	list.output();
	list.reverse();
	cout << "--------原地逆置------" << endl;
	list.output();
}

//递归输出
void fun2() {
	SuperList<int> list;
	list << 12 << 56 << 34 << 90 << 45;
	cout << "---------------原链表------------" << endl;
	list.output();
	cout << "---递归正序输出--" << endl;
	recursionA(list.locate(0));
	cout << endl;
	cout << "---递归逆序输出---" << endl;
	recursionB(list.locate(0));
	cout << endl;
}

//
void fun3() {
	int num;
	FareyList list;
	cout << "请输入你想要求的最大法雷序列： ";
	cin >> num;
	bool choose;
	cout << "请选择广度优先(0)，或者深度优先（非0）:";
	cin >> choose;
	logCurrentTime();
	if (choose) {
		list.startDepth(num);
	}
	else
	{
		list.startBreadth(num);
	}
	logCurrentTime();
	return;
	list.output();
}

int main()
{
	fun3();
	fun3();
	system("pause");
    return 0;
}
