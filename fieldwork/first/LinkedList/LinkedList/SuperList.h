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
	virtual ~SuperList();
	bool prepend(T t);		//��ͷ�ϲ���
	bool append(T t);		//��β��׷��
	bool insertBefore(int index,T 
		t);		//�ڵ�index�ڵ�ǰ�����
	bool insertAfter(int index,T t);			//�ڵ�index���ڵ�������
	void makeEmpty();						//�����������ͷ�ڵ�
	T& remove(int index);			//ɾ����index���ڵ�index>=0������ֵT
	void sort(int begin,int end , bool (*func)(T a,T b));
	void sort(bool(*func)(T a, T b));
	
	SuperList<T>& operator<<(T t);
	int getSize();
	//�鲢����
	void merge(SuperList<T>& t);		//���������ϲ�Ϊ�ݼ�	
	void reverse();						//����
	
	ListNode<T>* locate(int index);

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
	last->link = new ListNode<T>(T(t)); //������ĩβ׷��ר�ù��� next��ֵΪNULL
	last = last->link;
	size++;
	return true;
}

template<typename T>
inline bool SuperList<T>::insertBefore(int index, T  t)
{
	if (index >= size || index<0) {
		//�Ƿ�Խ��
		throw "Խ����Ŷ";
		return false;
	}
	else
	{
		ListNode<T>* n = locate(index-1); //ǰ��
		ListNode<T>* newItem = new ListNode<T>(t, n->link);
		n->link = newItem;		   //ǰ�������linkָ��new��Item
		size++;
		return true;
	}
}

template<typename T>
inline bool SuperList<T>::insertAfter(int index, T t)
{
	if (index >= size || index<0) {
		//�Ƿ�Խ��
		return false;
	}
	else
	{
		ListNode<T>* n = locate(index ); //ǰ��
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
inline void SuperList<T>::makeEmpty()
{
	while (first->link)
	{
		ListNode<T>* n = first->link;
		first->link = first->link->link;
		delete n;
		n = NULL;
	}
}

template<typename T>
inline T & SuperList<T>::remove(int index)
{
	// TODO: �ڴ˴����� return ���
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
		throw" Խ��Ƿ�";

	}
	else if (end == -1)
	{
		end = size;
	}
	else if (begin>end)
	{
		//����ǰ�����Դ��������
		throw" �Ƿ�";
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
	ListNode<T>* miax = beginNode;//��ֵ
	
	for (int j = 0; j < end - begin - 1; j++) {
		while (move->link&&move->link!=endNode)
		{
			if (func(move->link->date, miax->link->date)) {
				miax = move;
			}
			move = move->link;
		}
		if (l != miax) {
			ListNode<T>* aa = l->link; //��Ҫ����l����û����
			l->link = miax->link;	//��������������ֵ�ӵ�l����
			miax->link = l->link->link;	//�����ֵ�ĺ������ӵ����ֵǰ����
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
	last = l->link;
}

template<typename T>
inline SuperList<T>& SuperList<T>::operator<<(T t)
{
	// TODO: �ڴ˴����� return ���
	append(t);
	return *this;
}



template<typename T>
inline int SuperList<T>::getSize()
{
	return size;
}

template<typename T>
inline void SuperList<T>::merge(SuperList<T>& t)  //���������ϲ�Ϊ�ݼ�
{
	// TODO: �ڴ˴����� return ���

	ListNode<T>* pa = first->link;
	ListNode<T>* pb = t.first->link;
	first->link = NULL;
	t.first->link = NULL;

	//��ȷ���µ�β�ڵ�
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

	//��ʱ���ض���һ��û�����
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
	last = first->link;  //ͷ��β��
	ListNode<T>* node = first->link;	//������Ч����
	ListNode<T>* lNode;			//��Ϊ�м����
	first->link =NULL;	//��fist �ض�
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
		return NULL;	   // i������?
	}
		
	ListNode<T> * current = first;  
	int k = -1;
	while ( k < index)
	{
		current = current->link;  k++;
	}
	return current;	    //���ص� i �Ž���ַ��NULL
};


template<typename T>
inline void SuperList<T>::output()
{
	//����������Ҫ���ã�T����������

	if (size == 0) {
		cout << "�����������Ϊ��" << size << endl;
		cout << "������" << endl;
		return;
	}
	//���������������Ϣ��
	cout << "�����������Ϊ��" << size << endl;
	cout << "ͷ�ڵ������Ϊ�� " << first->link->date << endl;
	cout << "β�ڵ������Ϊ�� " << last->date << endl;
	cout << "�����ڵ���������α���Ϊ: " ;
	ListNode<T> *item = first->link;
	//ѭ��
	while (item)
	{
		std::cout << item->date << "--->";
		item = item->link;
	}
	cout << endl;
}
