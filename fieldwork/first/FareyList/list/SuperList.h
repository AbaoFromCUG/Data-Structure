#pragma once
#include<iostream>
using namespace std;
//单向链表
template<typename T>
struct ListNode {
	T date;

	ListNode(ListNode<T> *ptr = NULL) { link = ptr; }
	ListNode(T& t) {
		date = t;
		link = NULL;
	}
	ListNode(const T &item, ListNode<T> *ptr = NULL) {
		date = item;
		link = ptr;
	}
	ListNode* link;

};


template<typename T>
class SuperList
{
public:
	SuperList();
	SuperList(SuperList<T>& list);
	virtual ~SuperList();
	bool prepend(T t);		//在头上插入
	bool append(T t);		//在尾部追加
	bool insertBefore(int index,T t);		//在第index节点前面插入
	bool insertAfter(int index,T t);			//在第index个节点后面插入
	ListNode<T>* insertBetween(ListNode<T>* a, ListNode<T>* b, T t);
	void makeEmpty();						//清空链表，保存头节点
	T& remove(int index);			//删除第index个节点index>=0，返回值T
	void sort(int begin,int end , bool (*func)(T a,T b));
	void sort(bool(*func)(T a, T b));

	SuperList<T>& operator<<(T t);
	int getSize();
	//归并？，
	void merge(SuperList<T>& t);		//两条递增合并为递减
	void reverse();						//逆置

	ListNode<T>* locate(int index);
	ListNode<T>* getFirst();
	ListNode<T>* getLast();
	//
	void output();
protected:
	ListNode<T>* first;
	ListNode<T>* last;
	int size;
};

template<typename T>
inline SuperList<T>::SuperList()
{
	//默认构造? 那么T就必须要又默认构造函数
	first = new ListNode<T>;
	last = first;
	size = 0;
}

template<typename T>
inline SuperList<T>::SuperList(SuperList<T>& list)
{
	first = new ListNode<T>();
	size = list.getSize();
	ListNode<T>*workNode = list.getFirst();
	last=first;
	while (workNode)
	{
		last->link = new ListNode<T>(workNode->date);
		last = last->link;
		workNode = workNode->link;
	}
}

template<typename T>
inline SuperList<T>::~SuperList()
{
	makeEmpty();
	delete first;
	first = NULL;
}

template<typename T>
inline bool SuperList<T>::prepend(T t)
{
	ListNode<T> newNode = new ListNode<T>(t);
	newNode.link = first->link;
	first->link = newNode;
	size++;
	return true ;
}

template<typename T>
inline bool SuperList<T>::append(T  t)
{
	last->link = new ListNode<T>(T(t)); //调用在末尾追加专用构造 next赋值为NULL
	last = last->link;
	size++;
	return true;
}

template<typename T>
inline bool SuperList<T>::insertBefore(int index, T  t)
{
	if (index >= size || index<0) {
		//非法越界
		throw "越界了哦";
		return false;
	}
	else
	{
		ListNode<T>* n = locate(index-1); //前驱
		ListNode<T>* newItem = new ListNode<T>(t, n->link);
		n->link = newItem;		   //前驱保存的link指向new的Item
		size++;
		return true;
	}
}

template<typename T>
inline bool SuperList<T>::insertAfter(int index, T t)
{
	if (index >= size || index<0) {
		//非法越界
		return false;
	}
	else
	{
		ListNode<T>* n = locate(index ); //前驱
		ListNode<T>* newItem = new ListNode<T>(t, n->link);
		if (!n->link) {
			last = newItem;
		}
		n->link = newItem;
		size++;
		return true;
	}
}

template<typename T>
inline ListNode<T>* SuperList<T>::insertBetween(ListNode<T>* a, ListNode<T>* b, T t)
{
	if (a&&b) {

		ListNode<T>* newNode = new ListNode<T>(t, b);
		a->link = newNode;
		size++;
		return newNode;
	}else{
		throw "exception";
	}
}

template<typename T>
inline void SuperList<T>::makeEmpty()
{
	while (first->link)
	{
		ListNode<T>* n = first->link;
		first->link = first->link->link;
		delete n;
		n = NULL;
	}
	last = first;
	size = 0;
}

template<typename T>
inline T & SuperList<T>::remove(int index)
{
	// TODO: 在此处插入 return 语句
	size--;
	ListNode<T>* node = locate(index - 1);
	ListNode<T>* n = node->link;
	T t(n->date);
	node->link = node->link->link;
	delete n;
	return t;

}

template<typename T>
inline void SuperList<T>::sort(int begin, int end, bool(*func)(T a, T b))
{
	if (begin<0&&end>size-1)
	{
		throw" 越界非法";

	}
	else if (end == -1)
	{
		end = size;
	}
	else if (begin>end)
	{
		//排序前不可以大于排序后
		throw" 非法";
	}

	else if ((end-begin)<=1&&(end - begin) >= 0)
	{
		return;
	}


	ListNode<T>* beginNode=first;
	ListNode<T>* endNode;
	int i = 0;
	while (i<begin)
	{
		i++;
		beginNode = beginNode->link;
	}
	endNode = beginNode;
	while (i<end)
	{
		i++;
		endNode = endNode->link;
	}


	//start;
	cout << beginNode->date << "-------" << endNode->date << endl;
	endNode = endNode->link;

	ListNode<T>* l = beginNode;
	ListNode<T>* move = beginNode->link;	//
	ListNode<T>* miax = beginNode;//极值

	for (int j = 0; j < end - begin - 1; j++) {
		while (move->link&&move->link!=endNode)
		{
			if (func(move->link->date, miax->link->date)) {
				miax = move;
			}
			move = move->link;
		}
		if (l != miax) {
			ListNode<T>* aa = l->link; //不要丢了l后面没排序
			l->link = miax->link;	//把搜索到的最大的值加到l后面
			miax->link = l->link->link;	//把最大值的后项连接到最大值前项上
			l->link->link = aa;
		}
		l = l->link;
		miax = l;
		move = l->link;
	}
	l->link->link = endNode;
	if (endNode == NULL) {
		last = l->link;
	}


}

template<typename T>
inline void SuperList<T>::sort(bool(*func)(T a, T b))

{
	ListNode<T>* m = first;	//用来移动比较的指针
	ListNode<T>* min = first;		//用来保存当前小ListNode<T>的前一个ListNode<T>的指针
	ListNode<T>* l = first;	//用来指向新的链表的末尾
	for (int j = 0; j < size - 1; j++) {
		while (m->link != NULL)
		{
			if(func (m->link->date , min->link->date))
			{
				min = m;
			}
			m = m->link;
		}
		if (l != min) {
			ListNode<T>* aa = l->link; //不要丢了l后面没排序
			l->link = min->link;	//把搜索到的最大的值加到l后面
			min->link = l->link->link;	//把最大值的后项连接到最大值前项上
			l->link->link = aa;
		}
		l = l->link;
		min = l;
		m = l->link;
	}
	//enenenenen
	l->link->link = NULL;
	last = l->link;
}

template<typename T>
inline SuperList<T>& SuperList<T>::operator<<(T t)
{
	// TODO: 在此处插入 return 语句
	append(t);
	return *this;
}



template<typename T>
inline int SuperList<T>::getSize()
{
	return size;
}

template<typename T>
inline void SuperList<T>::merge(SuperList<T>& t)  //两条递增合并为递减
{
	// TODO: 在此处插入 return 语句

	ListNode<T>* pa = first->link;
	ListNode<T>* pb = t.first->link;
	first->link = NULL;
	t.first->link = NULL;

	//先确定新的尾节点
	last = pa->date > pb->date ? pb : pa;
	while (pa&&pb)
	{
		ListNode<T>* node;
		if (pa->date > pb->date) {
			node = pb;
			pb = pb->link;
		}
		else
		{
			node = pa;
			pa = pa->link;
		}
		node->link = first->link;
		first->link = node;
	}

	//此时，必定有一条没有清空
	ListNode<T>* noNull = pa ? pa : pb;
	while (noNull)
	{
		ListNode<T>* node = noNull;
		noNull = noNull->link;
		node->link = first->link;
		first->link = node;
	}
	size += t.size;
	t.size = 0;
	t.last = first;
}

template<typename T>
inline void SuperList<T>::reverse()
{
	last = first->link;  //头变尾部
	ListNode<T>* node = first->link;	//保存有效链表
	ListNode<T>* lNode;			//作为中间变量
	first->link =NULL;	//把fist 截断
	while (node)
	{
		lNode = first->link;
		first->link = node;
		node = node->link;
		first->link->link = lNode;
	}

}

template<typename T>
inline ListNode<T>* SuperList<T>::locate(int index)
{
	if (index < -1) {
		return NULL;	   // i不合理?
	}

	ListNode<T> * current = first;
	int k = -1;
	while ( k < index)
	{
		current = current->link;  k++;
	}
	return current;	    //返回第 i 号结点地址或NULL
}
template<typename T>
inline ListNode<T>* SuperList<T>::getFirst()
{
	return first->link;
}
template<typename T>
inline ListNode<T>* SuperList<T>::getLast()
{
	return last;
}
;


template<typename T>
inline void SuperList<T>::output()
{
	//这个函数如果要调用，T必须重载流

	if (size == 0) {
		cout << "这个链表，长度为：" << size << endl;
		cout << "输出完毕" << endl;
		return;
	}
	//在这里输入各种信息吧
	cout << "这个链表，长度为：" << size << endl;
	cout << "头节点的数据为： " << first->link->date << endl;
	cout << "尾节点的数据为： " << last->date << endl;
	cout << "各个节点的数据依次遍历为: " ;
	ListNode<T> *item = first->link;
	//循环
	while (item)
	{
		std::cout << item->date << "--->";
		item = item->link;
	}
	cout << endl;
}
