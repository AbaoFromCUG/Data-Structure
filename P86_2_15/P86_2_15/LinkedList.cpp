#include "stdafx.h"
#include "LinkedList.h"


LinkedList::LinkedList()
{
	head = new Item();
	head->data = 0;
	head->link = NULL;
	size = 0;
}

LinkedList::LinkedList(const LinkedList & old)
{
	this->size = old.size;
	head=new Item(*old.head);
	Item* last = head;
	Item* move=old.head->link;
	while (move != NULL)
	{
		last->link = new Item(*move);
		move = move->link;
		last = last->link;
	}
	last->link = NULL;
}

LinkedList::~LinkedList()
{
	/*
		删除链表时候
		从头到尾删除
	*/
	while (head != NULL)
	{
		Item* n = head;
		head = head->link;
		delete n;
		n = NULL;
	}
}

bool LinkedList::append(const int & num)
{
	try {
		Item* newitem = new Item;
		newitem->data = num;
		newitem->link = NULL;
		this->indexAt(size - 1)->link = newitem;
		size++;
		
	}
	catch (...) {
		return false;
	}
	
	/*last->link = new Item;
	last = last->link;
	last->link = NULL;
	last->data = num;*/
	return true;
	
	
}

bool LinkedList::insertBefore(int index, const int & data)
{
	if (index > size||index<1) {
		//非法越界
		return false;
	}
	else
	{
		Item* n = indexAt(index - 2); //前驱
		Item* m = n->link;				//后驱
		Item* newItem = new Item;
		newItem->data = data;
		n->link = newItem;		   //前驱保存的link指向new的Item
		newItem->link = m;			//newItem 的link指向后驱，如果没有后驱，就是NULL
		size++;
		return true;
	}
	
}

bool LinkedList::insertBehind(int index, const int & data)
{
	if (index > size || index < 1) {
		//非法
		return false;
	}
	else
	{
		Item* n = indexAt(index - 1); //前驱
		Item* m = n->link;				//后驱
		Item* newItem = new Item;
		newItem->data = data;
		n->link = newItem;		   //前驱保存的link指向new的Item
		newItem->link = m;			//newItem 的link指向后驱，如果没有后驱，就是NULL
		size++;
		return true;
	}
}

bool LinkedList::sortJ()
{
	/*
	 *此处需要额外3个空间
	 *起中指向新链表的最后一个指针本来可以可以省略，
	 *但是为了节省时间复杂度，所以牺牲空间
	 */
	/*
	插入排序、冒泡排序、二叉树排序、二路归并排序及其他线形排序是稳定的。
	选择排序、希尔排序、快速排序、堆排序是不稳定的。
	[编辑] 时间复杂性比较
	插入排序、冒泡排序最优为O(n),最坏为O(n^2),平均O(n^2）；
	快速排序最优为O(nlogn),最坏为O(n^2),平均O(nlogn);
	堆排序最优为O(nlogn),最坏为O(nlogn),平均O(nlogn);
	线形排序的时间复杂性为O(n)。
	[编辑] 辅助空间的比较
	线形排序、归并排序的辅助空间为O(n),快速排序的辅助空间为O(logn),其它排序的辅助空间为O(1)。
	
	*/
	Item* m = head->link;	//用来移动比较的指针
	Item* max = head;		//用来保存当前最大Item  的前一个Item的指针
	Item* last = head;	//用来指向新的链表的末尾
	
	for (int j = 0; j < size - 1; j++) {
		while (m->link!=NULL)
		{
			if (m->link->data >= max->link->data)
			{
				max = m;
			}
			m = m->link;
		}
		
		//开始交换
		/*
		步骤说明，last 后移一步，max后移一步，用中间值移动节点四步
		*/
		if (last != max) {
			Item* aa = last->link; //不要丢了last后面没排序
			last->link = max->link;	//把搜索到的最大的值加到last后面
			max->link = last->link->link;	//把最大值的后项连接到最大值前项上
			last->link->link = aa;
		}
		last = last->link;
		max = last;
		m = last->link;
		
	}
	//enenenenen
	last->link->link = NULL;
	return true;
}

bool LinkedList::sortZ()
{
	Item* m = head;	//用来移动比较的指针
	Item* min = head;		//用来保存当前小Item的前一个Item的指针
	Item* last = head;	//用来指向新的链表的末尾
						//冒泡排序
						//因为当只有一个没有比较时，不需要比较
	for (int j = 0; j < size - 1; j++) {
		while (m->link != NULL)
		{
			if (m->link->data <= min->link->data)
			{
				min = m;
			}
			m = m->link;
		}
		if (last != min) {
			Item* aa = last->link; //不要丢了last后面没排序
			last->link = min->link;	//把搜索到的最大的值加到last后面
			min->link = last->link->link;	//把最大值的后项连接到最大值前项上
			last->link->link = aa;
		}
		last = last->link;
		min = last;
		m = last->link;

	}
	//enenenenen
	last->link->link = NULL;
	return true;
}

int LinkedList::deleteItem(int index)
{
	// TODO: 在此处插入 return 语句
	if (index > size || index < 1) {
		//非法
		throw "妈呀，这犯法了";
	}
	else
	{
		int date;  //将要删除的Item还是保存数据返回吧
		Item* n = indexAt(index - 2); //前驱
		Item* old = n->link;				//当前
		n->link = old->link;			//前驱保存后驱的地址
		date = old->data;
		delete old;
		old = NULL;
		size--;
		return date;
	}
}

int LinkedList::getData(int i) const
{
	return indexAt(i - 1)->data;
}

void LinkedList::setData(int i, int x)
{
	indexAt(i - 1)->data = x;
}

Item * LinkedList::indexAt(int index) const
{
	if(index>=size||index<-1)
		return nullptr;
	else
	{
		//跳过头节点
		Item* p = head;
		for (int i = 0; i <= index&&p->link!=NULL; i++)
		{
			p = p->link;
		}
		return p;
	}
}

bool LinkedList::makeEmpty()
{
	/*
	清空链表时候
	从头+1到尾删除
	*/
	while (head->link != NULL)
	{
		Item* n = head->link;
		head->link = head->link->link;
		delete n;
		n = NULL;
	}
	return false;
}

LinkedList & LinkedList::operator<<(int num)
{
	// TODO: 在此处插入 return 语句
	append(num);
	return *this;
}

bool LinkedList::Merge(LinkedList & list)
{
	/*
		两条递增合并为递减
	
	*/
	Item* pa, *pb; 
	pa = head->link;   
	pb = list.head->link; 

	list.head->link = NULL; //截断list链表
	head->link = NULL;
	while (pa!=NULL&&pb!=NULL)
	{
		Item* p = head->link;	//p保存
		//比较头部的大小，较小的截下来
		if (pa->data > pb->data) {
			head->link = pb;	//将pb连接到头节点后面
			pb = pb->link;		//后移pb；
		}
		else{
			head->link = pa;	//将pa连接到头节点后面
			pa = pa->link;		//后移pa；
		}
		head->link->link = p;//再将原来头节点后面的接到新插入的pb上//
	}

	//此时，必定有一条不为空
	Item* noNull = pa ? pa : pb;
	while (noNull)
	{
		Item *mind = head->link;
		head->link = noNull;
		noNull = noNull->link;	//后移，准备切割
		head->link->link = mind;
	}
	//最后


	size = size + list.size;
	list.size = 0;
	return true;
}

void LinkedList::output()
{
	Item *item = head->link;
	//循环
	while (item)
	{
		std::cout << item->data << std::endl;
		item = item->link;
	}

}

Item * LinkedList::getItemAt(int index)
{

	return nullptr;
}
