// P86_2_15.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"LinkedList.h"
#include"SuperList.h"
#include<iostream>
using namespace std;

void fun() {
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

	list.sort(2,-1,[](int x, int y)->bool {
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


void fun3() {
	SuperList<int> list;
	list.append(1234342356);
	list.append(5);
	list.append(343);
	list.append(1);
	list.append(12);
	list.append(1);
	list.output();
	cout << "《--------->" << endl;

}

void fun2() {
	LinkedList lit;
	lit.append(1);
	lit.append(12);
	lit.append(123);
	lit.append(4);
	lit.append(-1);


}

int main()
{
	fun();
	std::system("pause");

	return 0;
}


