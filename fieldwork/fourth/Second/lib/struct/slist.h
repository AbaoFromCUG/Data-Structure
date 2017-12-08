#pragma once
#include<iostream>
using namespace std;
//单向链表
template<typename T>
struct SNode {
	T date;

    SNode(SNode<T> *ptr = NULL) { link = ptr; }
    SNode(T& t) {
		date = t;
		link = NULL;
	}
    SNode(const T &item, SNode<T> *ptr = NULL) {
		date = item;
		link = ptr;
	}
    SNode* link;
};


template<typename T>
class SList
{
public:
    SList();
    SList(SList<T>& list);
    virtual ~SList();
	bool prepend(T t);		//在头上插入
	bool append(T t);		//在尾部追加
	bool insertBefore(int index,T t);		//在第index节点前面插入
	bool insertAfter(int index,T t);			//在第index个节点后面插入
    SNode<T>* insertBetween(SNode<T>* a, SNode<T>* b, T t);
	void makeEmpty();						//清空链表，保存头节点
	T& remove(int index);			//删除第index个节点index>=0，返回值T
	void sort(int begin,int end , bool (*func)(T a,T b));
	void sort(bool(*func)(T a, T b));
    void sort(bool b);
    SList<T>& operator<<(T t);
	int getSize();
	//归并？，
    void merge(SList<T>& t);		//两条递增合并为递减
	void reverse();						//逆置

    SNode<T>* locate(int index);
    SNode<T>* getFirst();
    SNode<T>* getLast();
	//
	void output();
    bool isEmpty();
protected:
    SNode<T>* first;
    SNode<T>* last;
	int size;
};

template<typename T>
inline SList<T>::SList()
{
	//默认构造? 那么T就必须要又默认构造函数
    first = new SNode<T>;
	last = first;
	size = 0;
}

template<typename T>
inline SList<T>::SList(SList<T>& list)
{
    first = new SNode<T>();
	size = list.getSize();
    SNode<T>*workNode = list.getFirst();
	last=first;
	while (workNode)
	{
        last->link = new SNode<T>(workNode->date);
		last = last->link;
		workNode = workNode->link;
	}
}

template<typename T>
inline SList<T>::~SList()
{
	makeEmpty();
	delete first;
	first = NULL;
}

template<typename T>
inline bool SList<T>::prepend(T t)
{
    SNode<T> newNode = new SNode<T>(t);
	newNode.link = first->link;
	first->link = newNode;
	size++;
	return true ;
}

template<typename T>
inline bool SList<T>::append(T  t)
{
    last->link = new SNode<T>(T(t)); //调用在末尾追加专用构造 next赋值为NULL
	last = last->link;
	size++;
	return true;
}

template<typename T>
inline bool SList<T>::insertBefore(int index, T  t)
{
	if (index >= size || index<0) {
		//非法越界
		throw "越界了哦";
		return false;
	}
	else
	{
        SNode<T>* n = locate(index-1); //前驱
        SNode<T>* newItem = new SNode<T>(t, n->link);
		n->link = newItem;		   //前驱保存的link指向new的Item
		size++;
		return true;
	}
}

template<typename T>
inline bool SList<T>::insertAfter(int index, T t)
{
	if (index >= size || index<0) {
		//非法越界
		return false;
	}
	else
	{
        SNode<T>* n = locate(index ); //前驱
        SNode<T>* newItem = new SNode<T>(t, n->link);
		if (!n->link) {
			last = newItem;
		}
		n->link = newItem;
		size++;
		return true;
	}
}

template<typename T>
inline SNode<T>* SList<T>::insertBetween(SNode<T>* a, SNode<T>* b, T t)
{
	if (a&&b) {

        SNode<T>* newNode = new SNode<T>(t, b);
		a->link = newNode;
		size++;
		return newNode;
	}else{
		throw "exception";
	}
}

template<typename T>
inline void SList<T>::makeEmpty()
{
	while (first->link)
	{
        SNode<T>* n = first->link;
		first->link = first->link->link;
		delete n;
		n = NULL;
	}
	last = first;
	size = 0;
}

template<typename T>
inline T & SList<T>::remove(int index)
{
    // TODO: 在此处插入 return 语句
    if(index<0||index>=getSize()){
        throw "out of range";
    }
    size--;
    SNode<T>* node = locate(index - 1);
    SNode<T>* n = node->link;
    T t(n->date);
    node->link = node->link->link;
    last=node->link?node->link:node;
    delete n;
    return t;

}

template<typename T>
inline void SList<T>::sort(int begin, int end, bool(*func)(T a, T b))
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


    SNode<T>* beginNode=first;
    SNode<T>* endNode;
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

    SNode<T>* l = beginNode;
    SNode<T>* move = beginNode->link;	//
    SNode<T>* miax = beginNode;//极值

	for (int j = 0; j < end - begin - 1; j++) {
		while (move->link&&move->link!=endNode)
		{
			if (func(move->link->date, miax->link->date)) {
				miax = move;
			}
			move = move->link;
		}
		if (l != miax) {
            SNode<T>* aa = l->link; //不要丢了l后面没排序
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
inline void SList<T>::sort(bool(*func)(T a, T b))

{
    SNode<T>* m = first;	//用来移动比较的指针
    SNode<T>* min = first;		//用来保存当前小SNode<T>的前一个SNode<T>的指针
    SNode<T>* l = first;	//用来指向新的链表的末尾
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
            SNode<T>* aa = l->link; //不要丢了l后面没排序
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
void SList<T>::sort(bool b)
{
    SNode<T>* m = first;	//用来移动比较的指针
    SNode<T>* min = first;		//用来保存当前小SNode<T>的前一个SNode<T>的指针
    SNode<T>* l = first;	//用来指向新的链表的末尾
    for (int j = 0; j < size - 1; j++) {
        while (m->link != NULL)
        {
            if(b^(m->link->date)>(min->link->date))
            {
                min = m;
            }
            m = m->link;
        }
        if (l != min) {
            SNode<T>* aa = l->link; //不要丢了l后面没排序
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
inline SList<T>& SList<T>::operator<<(T t)
{
	// TODO: 在此处插入 return 语句
	append(t);
	return *this;
}



template<typename T>
inline int SList<T>::getSize()
{
	return size;
}

template<typename T>
inline void SList<T>::merge(SList<T>& t)  //两条递增合并为递减
{
	// TODO: 在此处插入 return 语句

    SNode<T>* pa = first->link;
    SNode<T>* pb = t.first->link;
	first->link = NULL;
	t.first->link = NULL;

	//先确定新的尾节点
	last = pa->date > pb->date ? pb : pa;
	while (pa&&pb)
	{
        SNode<T>* node;
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
    SNode<T>* noNull = pa ? pa : pb;
	while (noNull)
	{
        SNode<T>* node = noNull;
		noNull = noNull->link;
		node->link = first->link;
		first->link = node;
	}
	size += t.size;
	t.size = 0;
	t.last = first;
}

template<typename T>
inline void SList<T>::reverse()
{
	last = first->link;  //头变尾部
    SNode<T>* node = first->link;	//保存有效链表
    SNode<T>* lNode;			//作为中间变量
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
inline SNode<T>* SList<T>::locate(int index)
{
	if (index < -1) {
		return NULL;	   // i不合理?
	}

    SNode<T> * current = first;
	int k = -1;
	while ( k < index)
	{
		current = current->link;  k++;
	}
	return current;	    //返回第 i 号结点地址或NULL
}
template<typename T>
inline SNode<T>* SList<T>::getFirst()
{
	return first->link;
}
template<typename T>
inline SNode<T>* SList<T>::getLast()
{
	return last;
}
;


template<typename T>
inline void SList<T>::output()
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
    SNode<T> *item = first->link;
	//循环
	while (item)
	{
		std::cout << item->date << "--->";
		item = item->link;
	}
    cout << endl;
}

template<typename T>
bool SList<T>::isEmpty()
{
    return size<=0;
}
