#pragma once
#include<iostream>
struct Item
{
	int data;
	Item* link;
};
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList& old);
	virtual ~LinkedList();
	
	bool  append(const int& num);
	bool insertBefore(int index,const int& data);  //�ڵ�indexǰ�����
	bool insertBehind(int index, const int& data);	//�ڵ�index�������
	int deleteItem(int index);
	int getData(int i) const;	//ȡ����iԪ��ֵ
	void setData(int i, int x);		//���µ�iԪ��ֵ

	bool sortJ();		//������,�����ӿռ临�Ӷ�
	bool sortZ();		//��������
	Item* indexAt(int index) const;          /*�������飬0 Ϊ��һ����1Ϊ�ڶ���*/
	bool makeEmpty();


	LinkedList& operator<<(int num);
	//�ϲ��㷨
	/*
		��ha��hb�ֱ�����������ͷ���ķǵݼ���������ı�ͷָ�룬�����һ���㷨��
		����������������ϲ���һ���ǵ�������ĵ�����
	*/
	bool Merge(LinkedList& list);

	//cout?
	void output();
	
protected:
	/*
	* ��һ��λ�õ��г��������ǿռ䲻delete��
	* index ��0��ʼ
	* ��Ϊ�ռ䲢����delete�����ǵ�ַ�������ˣ���������Ϊprotect
	*/
	Item * head;
	int size;
	Item* last;
	Item* getItemAt(int index);	
};

