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
	list.append(123);
	list.append(1234);
	list.append(12345);
	list.append(123456);
	list.output();
	list.sort([](int x, int y)->bool {
		return x < y;
	});
	list.output();

	return;
	cout << "《--------->" << endl;
	list.sort(2,4,[](int x, int y)->bool {
		return x < y;
	});
	list.output();
	cout << "《--------->" << endl;
	list.sort(2, 4, [](int x, int y)->bool {
		return x > y;
	});
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
	//fun();
	//cout <<"<----------------------------------------------------->"<< endl;

	fun3();

	/*
	*/
	std::system("pause");

	return 0;
}


