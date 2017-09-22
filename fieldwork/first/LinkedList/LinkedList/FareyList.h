#pragma once
#include"SuperList.h"
//法雷序列
struct Fraction
{
	int n;	//分子 Numerator
	int d;  //分母 Denominator
	friend ostream & operator<<(ostream& os, Fraction& f);
	Fraction(int nn=0, int dd=0) {
		n = nn;
		d = dd;
	}
};
class FareyList
{
public:
	FareyList();
	~FareyList();
	void startDepth(long num);
	void startBreadth(long num);
	void recursion(ListNode<Fraction>* a,ListNode<Fraction>*b);		//深度优先
	void recursion();						//广度优先
	void output();
protected:
	SuperList<Fraction> list;
	int maxNum;
	bool over;
};

