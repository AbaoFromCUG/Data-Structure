// LinkedList.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"SuperList.h"
#include<iostream>
using namespace std;
/*
 * 实习作业一
 * 链表相关
 * Abao
 *
 * */

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
	cout << "------------------------------------------" << endl;
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

int main()
{
	fun1();
	system("pause");
    return 0;
}
