#include "FareyList.h"


FareyList::FareyList()
{
    list << Fraction{ 0,1 }  << Fraction{ 1,1 };
    connect(this,&FareyList::ok,[=](int num){
        if(num==1){
            QTimer::singleShot(0,this,SLOT(saveDate()));
        }
    });
}


FareyList::~FareyList()
{
}

void FareyList::startDepth(long num)
{
	list.makeEmpty();
	list << Fraction{ 0,1 } << Fraction{ 1,1 };


	this->maxNum = num;
    try{
        recursion(list.getFirst(), list.getLast());
    }catch(...){
        emit error(0);
    }

    emit ok(1);
}

void FareyList::startBreadth(long num)
{
	list.makeEmpty();
	list << Fraction{ 0,1 } << Fraction{ 1,1 };

	this->maxNum = num;
	over = true;
    try{
        recursion();
    }catch(...){
        emit error(0);
    }

    emit ok(1);
}

void FareyList::startIteration(long num)
{
    maxNum = num;
    list.makeEmpty();
    list << Fraction{ 0,1 } << Fraction{ 1,maxNum };
    ListNode<Fraction>* a, *b;
    a = list.getFirst();
    b = a->link;
    try{
        while (b->date.d != 1) {
            int x = (a->date.d + num) / b->date.d;
            list.append(Fraction{ b->date.n*x - a->date.n,b->date.d*x - a->date.d });
            a = b;
            b = b->link;
        }
    }catch(...){
        emit error(0);
    }

    emit ok(1);
}



void FareyList::saveDate()
{
    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        QString cache;      //写入的速度决定于调取<<的次数，所以尽量先读取一定的缓存，分几次存入
        ListNode<Fraction>* item=list.getFirst();
        while (item ) {

            for(int i=0;i<1000&&item;i++){
                cache.append(QString("%1/%2,").arg(item->date.n).arg(item->date.d));
                item=item->link;
            }
            out<<cache;
            cache.clear();
        }


        out<<QString("size：");
        out<<QString::number(list.getSize());
    }else {
        emit this->error(1);
    }


    file.close();
    emit ok(2);     //第二步骤ok

}

void FareyList::saveFileName(QString file)
{
    this->fileName=file;

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
	list.output();
}



ostream & operator<<(ostream & os, Fraction & f)
{
	// TODO: 在此处插入 return 语句
	os << f.n << "/" << f.d;
	return os;
}
