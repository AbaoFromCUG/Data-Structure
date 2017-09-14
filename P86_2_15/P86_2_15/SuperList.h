#pragma once

//��������
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
	bool insertBefore(int index,T&t);		//�ڵ�index�ڵ�ǰ�����
	bool insertAfter(int index,T&t);			//�ڵ�index���ڵ�������
	void makeEmpty();						//�����������ͷ�ڵ�
	T& remove(int index);			//ɾ����index���ڵ�index>=0������ֵT
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
	//Ĭ�Ϲ���? ��ôT�ͱ���Ҫ��Ĭ�Ϲ��캯��
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
	last->link = new ListNode<T>(T(t)); //������ĩβ׷��ר�ù��� next��ֵΪNULL
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
	// TODO: �ڴ˴����� return ���
}

template<typename T>
inline void SuperList<T>::sort(int begin, int end, bool(*func)(T a, T b))
{
	if (begin<0&&end>size-1)
	{
		throw" Խ��Ƿ�";

	}
	else if (begin>end&&end!=-1)
	{
		//����ǰ�����Դ��������
		throw" �Ƿ�";
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
	
	ListNode<T>* m = beginNode->link;	//�����ƶ��Ƚϵ�ָ��
	ListNode<T>* min = beginNode->link->link;		//�������浱ǰСListNode<T>��ǰһ��ListNode<T>��ָ��
	ListNode<T>* l = beginNode;	//����ָ���µ������ĩβ
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
			ListNode<T>* aa = l->link; //��Ҫ����l����û����
			l->link = min->link;	//��������������ֵ�ӵ�l����
			min->link = l->link->link;	//�����ֵ�ĺ������ӵ����ֵǰ����
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
	ListNode<T>* m = first;	//�����ƶ��Ƚϵ�ָ��
	ListNode<T>* min = first;		//�������浱ǰСListNode<T>��ǰһ��ListNode<T>��ָ��
	ListNode<T>* l = first;	//����ָ���µ������ĩβ
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
			ListNode<T>* aa = l->link; //��Ҫ����l����û����
			l->link = min->link;	//��������������ֵ�ӵ�l����
			min->link = l->link->link;	//�����ֵ�ĺ������ӵ����ֵǰ����
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
	//����������Ҫ���ã�T����������
	ListNode<T> *item = first->link;
	//ѭ��
	while (item)
	{
		std::cout << item->date << std::endl;
		item = item->link;
	}
}
