// P86_2_15.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"LinkedList.h"
#include<iostream>
using namespace std;

//合并算法
Item* Merge(LinkedList& list1, LinkedList& list2) {
	return NULL;
}

int main()
{
	LinkedList lit;
	lit.append(1);
	lit.append(12);
	lit.append(123);
	lit.append(1234);
	lit.append(12345);
	LinkedList lit2;
	lit2 << 12<<13<<22<<51;
	lit2.output();
	lit.Merge(lit2);
	
	lit.output();
	cout << "<----------->" << endl;;
	lit2.output();
	/*
	std::cout << "<--------测试代码开始.....------>" << endl;
	std::cout << "<--------原来------>" << endl;
	lit.output();
	std::cout << "<--------降序排序后------>" << endl;
	lit.sortJ();
	lit.output();
	std::cout << "<--------增序排序后------>"<<endl;
	lit.sortZ();
	lit.output();
	std::cout << "<--------清空后------>"<<endl;
	lit.makeEmpty();
	lit.output();*/
	std::system("pause");
    return 0;
}


