# 数据结构的各种实习

#<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [数据结构的各种实习](#数据结构的各种实习)
	- [作业](#)
		- [作业p84 2.6](#作业p84-26)
		- [作业p86 2.15](#作业p86-215)
	- [实习一](#实习一)
		- [关于法雷序列](#关于法雷序列)
			- [方案一：递归](#方案一递归)
				- [深度优先](#深度优先)
				- [广度优先](#广度优先)
			- [方案二： 循环](#方案二-循环)

<!-- /TOC -->



### 作业p84 2.6
实现了一个顺序表，一些基本功能，模板的

### 作业p86 2.15

* 类LinkedList
```cpp
struct Item{
    int date;
    Item* linked;
}
```
节点的单向链表
功能简单，归并，全部排序，增删该查


* 类SuperList，实现了实习一的关于链表的一些要求

```cpp
template<typename T>
struct ListNode {
	T date;
	ListNode* link;
    ....
};
```
各全模板，可自定义排序，通过传递函数指针
重载了排序函数 begin ,end, sortFun*;

##  实习一

### 关于法雷序列

#### 方案一：递归

##### 深度优先
在我的电脑上，大概3950-4000 之间的时候就开始栈溢出
```cpp
void FareyList::recursion(ListNode<Fraction>* a, ListNode<Fraction>* b)
{
	if ((a->date.d + b->date.d)> maxNum)
		return;
	ListNode<Fraction> *m = list.insertBetween(a, b, Fraction{ a->date.n + b->date.n,a->date.d + b->date.d });
	recursion(a, a->link);
	recursion(m, b);
}
```
<img src="assets/markdown-img-paste-20170916120930883.png" width=500 alt="正常的运行" >
-----
<img src="assets/markdown-img-paste-2017091612064045.png" width=500 alt="Stack overflow">

##### 广度优先
```cpp
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
```

<img src="assets/markdown-img-paste-20170916134915584.png" width=500 alt="深度优先vs广度优先">

但是仍然崩溃，此时size=10938995

<img src="assets/markdown-img-paste-2017091614375667.png" width=500 alt="广度优先">

> 总结： 法雷序列如果通过递归来进行搜索（？），那么无论是深度优先还是广度优先，选好终结条件是关键，另外，感觉深度优先递归（2的n次方？）的话更容易溢出，而广度优先由于递归的层数更少（递归层数？），更不容易溢出?但是，最终仍然会因为new的空间太大而不可以继续new


#### 方案二： 循环
--------
>17.9.22更新

迭代计算法：参考了acm相关论文的一种方法

> 法雷序列有个比较明显，基本上也是众所周知的性质，对于法雷序列中的任意三个连续的分数，设为p1/q1, p2/q2, p3/q3, 应该有性质:p2/q2 = (p1+p3)/(q1+q2)，其中p2,q2可能是经过约分得到的。如此我们希望通过已知的前两个数，直接能得到第三个数，然后依次类推，推出所有的数。  实际上也是可以的，虽然从表面上看，知道p1,q1,p2,q2之后,p3,q3有多种情况，如(p2-p1)/(q2-q1), (p2*2-p1)/(q2*2-q1)…但是我们只需选择最小的一个，容易证明最小的p3/q3应该为(p2*x-p1)/(q2*x-q1)，其中x=max{k∣q2*k-q1≤n}，这点容易证明。

如上所描述，本种方法直接利用了这个的结论*最小的p3/q3应该为(p2*x-p1)/(q2*x-q1)，其中x=max{k∣q2*k-q1≤n}*
于是我们主要的计算就是来算x，即k的最大值，通过演算，k≤(n+q1)/q2，利用计算机除法整除的性质，可以快速算出k
```cpp
list.makeEmpty();
list << Fraction{ 0,1 } << Fraction{ 1,maxNum };
ListNode<Fraction>* a, *b;
a = list.getFirst();
b = a->link;
try{
		while (b->date.d != 1) {
				int x = (a->date.d + num) / b->date.d;	//整除的特性
				list.append(Fraction{ b->date.n*x - a->date.n,b->date.d*x - a->date.d });
				a = b;
				b = b->link;
		}
}catch(...){
		emit error(0);
}
```


### 关于大数阶乘

高位计算到低位
低位循环进位到高位
3个循环，2个移动节点
```cpp
for (int i = 2; i <= maxNum; i++)
{
		DListNode<int>* node=list.getLast();       //用来计算的node
		DListNode<int>* mNode;      //用来进位的node
		while (node!=list.getFirst()->LLink) {
				 long long n= node->date*i;
				 node->date=n%storeLong;
				 n=n/storeLong;
				 //如果需要进位的数非零的话
				 mNode=node->RLink;
				 //循环进位
				 while (n) {
						 if(!mNode){
								 list.append(0);
								 mNode = list.getLast();
								 mNode->date = n%storeLong;
								 n /= storeLong;
						 }else {
								n=mNode->date+n;
								mNode->date=n%storeLong;
								n=n/storeLong;
						 }
						 mNode=mNode->RLink;
				 }
				 node = node->LLink;
		}
}
```


最后再上两个效果图片

![](assets/markdown-img-paste-20170922141136399.png)

![](assets/markdown-img-paste-20170922141241239.png)
