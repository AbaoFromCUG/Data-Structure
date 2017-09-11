// P84_2_6.cpp : 定义控制台应用程序的入口点。
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
	cout << "转换前"<<endl;
	for (int i = 0; i < 8; i++)
	{
		
		cout << myVector[i] << endl;
	}
	int length;
	cout << "请输入需要转换的长度：" ;
	cin >> length;
	
	myVector.change(length);
	cout << "转换后"<<endl;
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
	// TODO: 在此处插入 return 语句
	return myArray[index];
}

template<class T>
MyVector<T>& MyVector<T>::change(int length)
{
	// TODO: 在此处插入 return 语句
	for (int i = 0; i < (length / 2); i++) {
		T mindle = (*this)[i];
		(*this)[i] = (*this)[length- i-1];
		(*this)[length - i - 1] = mindle;
		
	}
	return *this;
}
