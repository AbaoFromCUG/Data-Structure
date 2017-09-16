#include "stdafx.h"
#include "LargeFactorial.h"


LargeFactorial::LargeFactorial(int l)
{
	list.append(1);
	storeLong = pow(10, l);
}


LargeFactorial::~LargeFactorial()
{
}

void LargeFactorial::start(int maxNum)
{
	for (int i = 2; i <= maxNum; i++)
	{
		multiplication(i);
	}
}

void LargeFactorial::multiplication(int num)
{
	ListNode<int>* item = list.getFirst();
	while (item)
	{
		int n = item->date * num;
		if (n >= storeLong) {
			if (!item->link) {
				list << 0;
			}
			item->link->date += (n / storeLong);
			item->date = n%storeLong;
		}
		else
		{
			item->date = n;
		}
		item = item->link;
	}
}

void LargeFactorial::output()
{
	cout << list.getSize() << endl;
	//return;
	ListNode<int> *item = list.getFirst();
	coutItem(item);
}

void LargeFactorial::coutItem(ListNode<int>* t)
{
	if (t) {
		printf("%04d", t->date);
		coutItem(t->link);
	}
	
}
