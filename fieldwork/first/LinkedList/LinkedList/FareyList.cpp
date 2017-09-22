#include "stdafx.h"
#include "FareyList.h"


FareyList::FareyList()
{
	list << Fraction{ 0,1 }  << Fraction{ 1,1 };	
}


FareyList::~FareyList()
{
}

void FareyList::startDepth(long num)
{
	list.makeEmpty();
	list << Fraction{ 0,1 } << Fraction{ 1,1 };


	this->maxNum = num;
	recursion(list.getFirst(), list.getLast());
}

void FareyList::startBreadth(long num)
{
	list.makeEmpty();
	list << Fraction{ 0,1 } << Fraction{ 1,1 };

	this->maxNum = num;
	over = true;
	recursion();
}

void FareyList::startIterAtion(long num)
{
	maxNum = num;
	list.makeEmpty();
	list << Fraction{ 0,1 } << Fraction{ 1,maxNum };
	ListNode<Fraction>* a, *b;
	a = list.getFirst();
	b = a->link;

	while (b->date.d != 1) {
		int x = (a->date.d + num) / b->date.d;
		list.append(Fraction{ b->date.n*x - a->date.n,b->date.d*x - a->date.d });
		a = b;
		b = b->link;
	}
	return;
}

void FareyList::recursion(ListNode<Fraction>* a, ListNode<Fraction>* b)
{
	if ((a->date.d + b->date.d)> maxNum)
		return;
	ListNode<Fraction> *m = list.insertBetween(a, b, Fraction{ a->date.n + b->date.n,a->date.d + b->date.d });
	recursion(a, a->link);
	recursion(m, b);
}

void FareyList::recursion()
{
	ListNode<Fraction>* a = list.getFirst();
	ListNode<Fraction>* b = list.getFirst()->link;
	while (b)
	{
		if ((a->date.d + b->date.d) <= maxNum) {
			list.insertBetween(a, b, Fraction{ a->date.n + b->date.n,a->date.d + b->date.d });
			over = false;
		}
		a = b;
		b = b->link;
	}
	if (!over) {
		over = true;
		recursion();
	}
}

void FareyList::output()
{
	list.outMainMessage();
}

void FareyList::test()
{
	ListNode<Fraction>* node = list.getFirst();
	while (node)
	{
		
		
	}
}

ostream & operator<<(ostream & os, Fraction & f)
{
	// TODO: 在此处插入 return 语句
	os << f.n << "/" << f.d;
	return os;
}
