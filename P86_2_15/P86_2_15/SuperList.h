#pragma once

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

	}
	ListNode* link;
	
};


template<typename T>
class SuperList
{
public:
	SuperList();
	virtual ~SuperList();
	bool append(T t);
	bool insertBefore(int index,T&t);		//在第index节点前面插入
	bool insertAfter(int index,T&t);			//在第index个节点后面插入
	void makeEmpty();						//清空链表，保存头节点
	T& remove(int index);			//删除第index个节点index>=0，返回值T
	void sort(int begin,int end , bool (*func)(T a,T b));
	void sort(bool(*func)(T a, T b));
	

	int getSize();
	
	
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
inline SuperList<T>::~SuperList()
{
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
inline bool SuperList<T>::insertBefore(int index, T & t)
{
	return false;
}

template<typename T>
inline bool SuperList<T>::insertAfter(int index, T & t)
{
	return bool();
}

template<typename T>
inline void SuperList<T>::makeEmpty()
{
}

template<typename T>
inline T & SuperList<T>::remove(int index)
{
	// TODO: 在此处插入 return 语句
}

template<typename T>
inline void SuperList<T>::sort(int begin, int end, bool(*func)(T a, T b))
{
	if (begin<0&&end>size-1)
	{
		throw" 越界非法";

	}
	else if (begin>end&&end!=-1)
	{
		//排序前不可以大于排序后
		throw" 非法";
	}
	else if (end==-1)
	{
		end = size;
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
	std::cout << beginNode->date << "-----" << endNode->date << endl;
	

	//start;endNode = endNode->link;
	
	ListNode<T>* m = beginNode->link;	//用来移动比较的指针
	ListNode<T>* min = beginNode->link->link;		//用来保存当前小ListNode<T>的前一个ListNode<T>的指针
	ListNode<T>* l = beginNode;	//用来指向新的链表的末尾
	for (int j = 0; j <end-begin-1; j++) {
		while (m->link != NULL)
		{
			if (func(m->link->date, min->link->date))
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
	l->link->link = endNode;
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
}

template<typename T>
inline int SuperList<T>::getSize()
{
	return size;
}


template<typename T>
inline void SuperList<T>::output()
{
	//这个函数如果要调用，T必须重载流
	ListNode<T> *item = first->link;
	//循环
	while (item)
	{
		std::cout << item->date << std::endl;
		item = item->link;
	}
}
