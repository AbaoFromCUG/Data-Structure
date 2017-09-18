#pragma once
#include"SuperList.h"
#include"stable.h"
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
class FareyList:public QObject
{
    Q_OBJECT
public:
	FareyList();
	~FareyList();

    void recursion(ListNode<Fraction>* a,ListNode<Fraction>*b);
    void recursion();
    void output();
public slots:
    void startDepth(long num);      //深度优先
    void startBreadth(long num);    //广度优先
    void startIteration(long num);  //迭代

    void saveDate();

    void saveFileName(QString file);

signals:
    void ok(int);           //步骤ok的信号
    void error(int num);    //错误的信号
protected:
	SuperList<Fraction> list;
	int maxNum;
    bool over;
    QString fileName;
};

