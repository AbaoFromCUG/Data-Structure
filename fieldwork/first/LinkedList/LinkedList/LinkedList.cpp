// LinkedList.cpp : 定义控制台应用程序的入口点。
//
// 


#include "stdafx.h"
#include"SuperList.h"
#include"FareyList.h"
#include"LargeFactorial.h"
#include"DoublyList.h"
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
 

//打印时间戳
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
void fun0();

//单链表的逆置测试代码
void fun1();

//递归输出
void fun2();

//法雷序列的测试函数
void fun3();

//大数阶乘的测试函数
void fun4();

//双向链表；
void fun5();


int main()
{
	fun4();
	system("pause");
	return 2;
	cout << "这只是个用以测试各种链表的项目" << endl;
	cout << "请输入你想要测试的函数序号0-5：";
	int num;
	cin >> num;
	switch (num)
	{
	case 0:
		fun0();
		break;
	case 1:
		fun1();
		break;
	case 2:
		fun2();
		break;
	case 3:
		fun3();
		break;
	case 4:
		fun4();
		break;
	case 5:
		fun5();
		break;
	default:
		cout << "error,退出，请自行看代码" << endl;
		break;
	}
	cout << "更多内容，请看代码" << endl;
	
    return 0;
}

void fun0()
{
	SuperList<int> list1;
	SuperList<int> list2;
	list1 << 1 << 3 << 5 << 7 << 9;
	list2 << 2 << 4 << 6 << 8 << 10;
	list1.output();
	list2.output();
	list1.merge(list2);
	std::cout << "-----------------合并后-------------------------" << std::endl;
	list1.output();
	list2.output();
}

void fun1()
{
	SuperList<int> list;
	list << 12 << 23 << 56 << 12 << 89;
	cout << "--------原链表------" << endl;
	list.output();
	list.reverse();
	cout << "--------原地逆置------" << endl;
	list.output();
}

void fun2()
{
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

void fun3()
{
	int num;
	FareyList list;
	cout << "请输入你想要求的最大法雷序列： ";
	cin >> num;
	int choose;
	cout << "请选择广度优先(0)，或者深度优先（1）,或者迭代（2）:";
	cin >> choose;
	logCurrentTime();
	switch (choose)
	{
	case 0:
		list.startBreadth(num);
		break;
	case 1:
		list.startDepth(num);
		break;
	case 2:
		list.startIterAtion(num);
		break;
	default:
		cout << "输出有误，正在退出……";
		return;
		break;
	}
	logCurrentTime();
	
	list.output();
	return;

}

void fun4()
{
	cout << "请输入你要求的大数: ";
	int num;
	cin >> num;
	for (int i = 3; i <8; i++)
	{
		LargeFactorial list(i);
		cout << "当每个节点存" << i << "位时" << endl;
		logCurrentTime();

		list.start(num);
		logCurrentTime();
		list.output();
		cout << endl;
		//cout << "长度"<<list.getSize() << endl;
		cout << "-----------------" << endl;
	}
	
	
}

void fun5()
{
	DoublyList<int> list;
	list << 12 << 23 << 54 << 87;
	list.output();
}
