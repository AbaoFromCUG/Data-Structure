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
		ɾ������ʱ��
		��ͷ��βɾ��
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
		//�Ƿ�Խ��
		return false;
	}
	else
	{
		Item* n = indexAt(index - 2); //ǰ��
		Item* m = n->link;				//����
		Item* newItem = new Item;
		newItem->data = data;
		n->link = newItem;		   //ǰ�������linkָ��new��Item
		newItem->link = m;			//newItem ��linkָ����������û�к���������NULL
		size++;
		return true;
	}
	
}

bool LinkedList::insertBehind(int index, const int & data)
{
	if (index > size || index < 1) {
		//�Ƿ�
		return false;
	}
	else
	{
		Item* n = indexAt(index - 1); //ǰ��
		Item* m = n->link;				//����
		Item* newItem = new Item;
		newItem->data = data;
		n->link = newItem;		   //ǰ�������linkָ��new��Item
		newItem->link = m;			//newItem ��linkָ����������û�к���������NULL
		size++;
		return true;
	}
}

bool LinkedList::sortJ()
{
	/*
	 *�˴���Ҫ����3���ռ�
	 *����ָ������������һ��ָ�뱾�����Կ���ʡ�ԣ�
	 *����Ϊ�˽�ʡʱ�临�Ӷȣ����������ռ�
	 */
	/*
	��������ð�����򡢶��������򡢶�·�鲢�������������������ȶ��ġ�
	ѡ������ϣ�����򡢿������򡢶������ǲ��ȶ��ġ�
	[�༭] ʱ�临���ԱȽ�
	��������ð����������ΪO(n),�ΪO(n^2),ƽ��O(n^2����
	������������ΪO(nlogn),�ΪO(n^2),ƽ��O(nlogn);
	����������ΪO(nlogn),�ΪO(nlogn),ƽ��O(nlogn);
	���������ʱ�临����ΪO(n)��
	[�༭] �����ռ�ıȽ�
	�������򡢹鲢����ĸ����ռ�ΪO(n),��������ĸ����ռ�ΪO(logn),��������ĸ����ռ�ΪO(1)��
	
	*/
	Item* m = head->link;	//�����ƶ��Ƚϵ�ָ��
	Item* max = head;		//�������浱ǰ���Item  ��ǰһ��Item��ָ��
	Item* last = head;	//����ָ���µ������ĩβ
	
	for (int j = 0; j < size - 1; j++) {
		while (m->link!=NULL)
		{
			if (m->link->data >= max->link->data)
			{
				max = m;
			}
			m = m->link;
		}
		
		//��ʼ����
		/*
		����˵����last ����һ����max����һ�������м�ֵ�ƶ��ڵ��Ĳ�
		*/
		if (last != max) {
			Item* aa = last->link; //��Ҫ����last����û����
			last->link = max->link;	//��������������ֵ�ӵ�last����
			max->link = last->link->link;	//�����ֵ�ĺ������ӵ����ֵǰ����
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
	Item* m = head;	//�����ƶ��Ƚϵ�ָ��
	Item* min = head;		//�������浱ǰСItem��ǰһ��Item��ָ��
	Item* last = head;	//����ָ���µ������ĩβ
						//ð������
						//��Ϊ��ֻ��һ��û�бȽ�ʱ������Ҫ�Ƚ�
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
			Item* aa = last->link; //��Ҫ����last����û����
			last->link = min->link;	//��������������ֵ�ӵ�last����
			min->link = last->link->link;	//�����ֵ�ĺ������ӵ����ֵǰ����
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
	// TODO: �ڴ˴����� return ���
	if (index > size || index < 1) {
		//�Ƿ�
		throw "��ѽ���ⷸ����";
	}
	else
	{
		int date;  //��Ҫɾ����Item���Ǳ������ݷ��ذ�
		Item* n = indexAt(index - 2); //ǰ��
		Item* old = n->link;				//��ǰ
		n->link = old->link;			//ǰ����������ĵ�ַ
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
		//����ͷ�ڵ�
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
	�������ʱ��
	��ͷ+1��βɾ��
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
	// TODO: �ڴ˴����� return ���
	append(num);
	return *this;
}

bool LinkedList::Merge(LinkedList & list)
{
	/*
		���������ϲ�Ϊ�ݼ�
	
	*/
	Item* pa, *pb; 
	pa = head->link;   
	pb = list.head->link; 

	list.head->link = NULL; //�ض�list����
	head->link = NULL;
	while (pa!=NULL&&pb!=NULL)
	{
		Item* p = head->link;	//p����
		//�Ƚ�ͷ���Ĵ�С����С�Ľ�����
		if (pa->data > pb->data) {
			head->link = pb;	//��pb���ӵ�ͷ�ڵ����
			pb = pb->link;		//����pb��
		}
		else{
			head->link = pa;	//��pa���ӵ�ͷ�ڵ����
			pa = pa->link;		//����pa��
		}
		head->link->link = p;//�ٽ�ԭ��ͷ�ڵ����Ľӵ��²����pb��//
	}

	//��ʱ���ض���һ����Ϊ��
	Item* noNull = pa ? pa : pb;
	while (noNull)
	{
		Item *mind = head->link;
		head->link = noNull;
		noNull = noNull->link;	//���ƣ�׼���и�
		head->link->link = mind;
	}
	//���


	size = size + list.size;
	list.size = 0;
	return true;
}

void LinkedList::output()
{
	Item *item = head->link;
	//ѭ��
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
