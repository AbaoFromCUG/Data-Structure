// P84_2_6.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class T>

 class MyVector
{
	
public:
	MyVector(int m_size);
	~MyVector();
	T&operator[](int index);
	MyVector<T>& change(int length);


private:
	T* myArray;
	int arraySize;
};

int main()
{
	MyVector<int>  myVector(8);
	for (int i = 0; i < 8; i++)
	{
		myVector[i] = 10 - i;
	}
	cout << "ת��ǰ"<<endl;
	for (int i = 0; i < 8; i++)
	{
		
		cout << myVector[i] << endl;
	}
	int length;
	cout << "��������Ҫת���ĳ��ȣ�" ;
	cin >> length;
	
	myVector.change(length);
	cout << "ת����"<<endl;
	for (int i = 0; i < 8; i++)
	{

		cout << myVector[i] << endl;
	}

	system("pause");
    return 0;
}
template<class T>
MyVector<T>::MyVector(int m_size)
{
	myArray = new T[m_size];
	arraySize = m_size;
}
template<class T>
MyVector<T>::~MyVector()
{
}

template<class T>
T & MyVector<T>::operator[](int index)
{
	// TODO: �ڴ˴����� return ���
	return myArray[index];
}

template<class T>
MyVector<T>& MyVector<T>::change(int length)
{
	// TODO: �ڴ˴����� return ���
	for (int i = 0; i < (length / 2); i++) {
		T mindle = (*this)[i];
		(*this)[i] = (*this)[length- i-1];
		(*this)[length - i - 1] = mindle;
		
	}
	return *this;
}
