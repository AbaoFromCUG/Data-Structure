#include "stdafx.h"
#include "LargeFactorial.h"
#include<iostream>
using namespace std;

LargeFactorial::LargeFactorial(int l)
{
	list.append(1);
	storeLong = pow(10, l);
	length = l;
}


LargeFactorial::~LargeFactorial()
{
}

void LargeFactorial::start(int maxNum)
{
	list.makeEmpty();
	list.append(1);
	//高位在尾部
	for (int i = 2; i <= maxNum; i++)
	{
		DListNode<int>* node = list.getLast();       //用来计算的node
		DListNode<int>* mNode;      //用来进位的node
		while (node != list.getFirst()->LLink) {
			long long n = node->date*i;
			node->date = n%storeLong;
			n = n / storeLong;
			//如果需要进位的数非零的话
			mNode = node->RLink;
			//循环进位
			while (n!=0) {
				if (!mNode) {
					list.append(0);
					mNode = list.getLast();
					mNode->date = n%storeLong;
					n /= storeLong;
				}
				else {
					mNode->date += n%storeLong;
					n /= storeLong;
				}
				mNode = mNode->RLink;
			}

			node = node->LLink;
		}
	}

}

void LargeFactorial::output()
{
	cout << list.getLast()->date;
	coutItem(list.getLast()->LLink);
}

void LargeFactorial::coutItem(DListNode<int>* t)
{
	if (t!=list.getFirst()->LLink) {
		cout.fill('0');
		cout.width(length);
		cout << t->date;
		coutItem(t->LLink);
	}
	
}

int LargeFactorial::getSize()
{
	return list.getSize();
}


