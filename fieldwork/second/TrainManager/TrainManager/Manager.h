#pragma once
#include<string>
#include "MyQueue.h"
#include <iostream>
using namespace std;
class Manager
{
public:
	Manager(int track=3);
	~Manager();
	void startRun(int *n,int length);
	MyQueue<int>* getMinFTrack(int& i);//获得头部最小的队列
	MyQueue<int>* getMaxRTrack(int n,int&i);//获得尾部最小的队列
	bool isAllNULL();
	bool haveEmpty();	//是否有队列为空
	int getEmptyTrack();
	void outTrain();
	void initData();

protected:
	int n;
	int trackNum;
	MyQueue<int>* trackList;
	int waitNum = 1;
	
};

