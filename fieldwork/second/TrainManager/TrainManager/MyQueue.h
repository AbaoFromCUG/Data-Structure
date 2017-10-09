#pragma once

template<typename T>
struct QueueNode
{
	QueueNode(T t, QueueNode<T>* l = NULL, QueueNode<T>* r = NULL) {
		data = t;
		lNode = l;
		rNode = r;
		//勾连好
		if (l) {
			lNode->rNode = this;
		}
		if (r) {
			rNode->lNode = this;
		}
	}
	QueueNode<T>* lNode;
	QueueNode<T>* rNode;
	T data;
};

template<typename T> 
class MyQueue
{
public:
	MyQueue();
	~MyQueue();
	void inQueue(T t);	//入队列
	T outQueue();			//出队列
	bool empty();		//判断是否为空
	T getFrontData();	//获得队头数据
	T getRearData();
	void clear();		//清空队列
protected:
	QueueNode<T>* fromt;
	QueueNode<T>* rear;
	int length;
};

template<typename T>
MyQueue<T>::MyQueue()
{
	fromt = rear = NULL;
	length = 0;
}

template<typename T>
MyQueue<T>::~MyQueue()
{
	while (fromt)
	{
		rear = fromt;
		fromt = fromt->rNode;
		delete rear;
	}

}

template<typename T>
void MyQueue<T>::inQueue(T t)
{
	length++;
	if (!rear) {
		rear = fromt = new QueueNode<T>(t);
	}
	else
	{
		new QueueNode<T>(t, rear);
		rear = rear->rNode;
	}
}

template<typename T>
T MyQueue<T>::outQueue()
{
	if (length <= 0) {
		throw "Queue is empty";
	}else if (length==1)
	{
		T t = fromt->data;
		delete fromt;
		fromt = rear = NULL;
		length = 0;
		return t;
	}
	else
	{
		QueueNode<T> *l;
		T t;
		l = fromt;
		fromt = fromt->rNode;
		fromt->lNode = NULL;
		t = l->data;
		delete l;
		length--;
		return t;
	}
}

template<typename T>
bool MyQueue<T>::empty()
{
	return length < 1;
}

template<typename T>
T MyQueue<T>::getFrontData()
{
	if (empty())
		throw "Queue is empty";
	return fromt->data;
}

template<typename T>
inline T MyQueue<T>::getRearData()
{
	if (empty())
		throw "Queue is empty";
		return rear->data;
}

template<typename T>
inline void MyQueue<T>::clear()
{
	while (!this->empty())
	{
		this->outQueue();
	}
}

