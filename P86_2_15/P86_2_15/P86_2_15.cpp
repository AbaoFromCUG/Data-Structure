// P86_2_15.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"LinkedList.h"
#include"SuperList.h"
#include<iostream>
using namespace std;

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

//LinkedList测试代码
void fun1() {
	LinkedList lit;
	lit.append(1);
	lit.append(12);
	lit.append(123);
	lit.append(4);
	lit.append(-1);
	lit.output();
	
	cout << "-------------delete 3" << endl;
	lit.deleteItem(3);
	lit.output();
	cout << "-------------append 4" << endl;
	lit.append(4);
	lit.output();
	cout << "-------------delete 1" << endl;
	lit.deleteItem(1);
	lit.output();
	cout << "-------------delete 2" << endl;
	lit.deleteItem(2);
	lit.output();
	cout << "-------------insertbefor 2" << endl;
	lit.insertBefore(2, 67);
	lit.output();

}

//SuperList 排序专用测试函数
void fun2() {
	SuperList<int> list;
	list.append(1);
	list.append(12);
	list.append(1);
	list.append(123);
	list.append(12);
	list.append(126);
	list.append(120);

	cout << "《-----原来的序列---->" << endl;
	list.output();

	list.sort([](int x, int y)->bool {
		return x < y;
	});
	cout << "《-----全部排序后的序列---->" << endl;
	list.output();

	list.sort(2, -1, [](int x, int y)->bool {
		return x > y;
	});
	cout << "《----2，5排序后----->" << endl;

	list.output();
	list.sort(2, 6, [](int x, int y)->bool {
		return x < y;
	});
	cout << "《----2，5反序后----->" << endl;
	list.output();

}

//流，增删改查专用的测试函数
void fun3() {
	SuperList<int> list;
	list << 12 << 223 << 23 << 34 << 45;
	cout << "-----------list原--------------" << endl;
	list.output();
	cout << "-------------list移除index=2的一个之后------------" << endl;
	list.remove(2);
	list.output();
	cout << "-------------list在index=2前插入------------" << endl;
	list.insertBefore(2,4);
	list.output();
	cout << "-------------list在index=4后插入------------" << endl;
	list.insertAfter(4, 4);
	list.output();
	


}

//递增序列归并为递减序列
void fun4() {
	SuperList<int> list1;
	SuperList<int> list2;
	list1 << 1 << 3 << 5 << 7 << 9;
	list2 << 2 << 4 << 6 << 8 <<10;
	list1.merge(list2);
	list1.output();
	cout << "------------------------------------------" << endl;
	list2.output();
}

//单链表的逆置测试代码
void fun5() {
	SuperList<int> list;
	list << 12 << 23 << 56 << 12 << 89;
	cout << "--------原链表------" << endl;
	list.output();
	list.reverse();
	cout << "--------原地逆置------" << endl;
	list.output();
}

//递归输出
void fun6() {
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
	std::system("pause");

	return 0;
}


