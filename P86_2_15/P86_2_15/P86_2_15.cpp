// P86_2_15.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"LinkedList.h"
#include<iostream>
using namespace std;

//�ϲ��㷨
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
	std::cout << "<--------���Դ��뿪ʼ.....------>" << endl;
	std::cout << "<--------ԭ��------>" << endl;
	lit.output();
	std::cout << "<--------���������------>" << endl;
	lit.sortJ();
	lit.output();
	std::cout << "<--------���������------>"<<endl;
	lit.sortZ();
	lit.output();
	std::cout << "<--------��պ�------>"<<endl;
	lit.makeEmpty();
	lit.output();*/
	std::system("pause");
    return 0;
}


