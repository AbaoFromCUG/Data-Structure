#include "stdafx.h"
#include "Manager.h"




Manager::Manager(int track)
{
	this->trackNum = track;
	trackList = new MyQueue<int>[track];
}

Manager::~Manager()
{
}



void Manager::startRun(int *num, int length)
{
	this->initData();
	for (int i = 0; i < length; i++)
	{
		//如果
		if (num[i]==waitNum)
		{
			if (haveEmpty()){

				//如果有空轨道
				cout <<"                     -------->数字"<<waitNum<<"从"<< getEmptyTrack()<<"号轨道路过并出"  << endl;
				waitNum++;
			}
			else {

				//如果没有空轨道了，就是没有办法转运
				cout << "无法转运" << endl;
				return;
			}
		}
		else
		{
			//不是，那么就要等待,放到尾部最小的一个对列
			int tempNum = -1;
			MyQueue<int>* p = getMaxRTrack(num[i], tempNum);
			if (!p) {
				cout << "无法转运" << endl;
				return;
			}
			else
			{
				cout << "数字" << num[i] << "在" << tempNum << "号铁轨入轨" << endl;
				p->inQueue(num[i]);
			}
		}
		outTrain();
		
	}
}
MyQueue<int>* Manager::getMinFTrack(int& ii)
{
	int min = 100000000;
	ii = -1;
	MyQueue<int>* minPtr = NULL;
	for (int i = 0; i < trackNum; i++)
	{
		if ((!trackList[i].empty()) && trackList[i].getFrontData() < min) {
			min = trackList[i].getFrontData();
			minPtr = trackList + i;
			ii = i;
		}
	}
	return minPtr;
}
MyQueue<int>* Manager::getMaxRTrack(int n,int & ii)
{
	int max = -100;
	ii = -1;
	MyQueue<int>* maxPtr = NULL;
	MyQueue<int>* nPtr = NULL;
	for (int i = 0; i < trackNum; i++)
	{
		if (trackList[i].empty())
		{
			nPtr = trackList + i;
			ii = i;
		}
		else if (trackList[i].getRearData() < n&&trackList[i].getRearData() > max)
		{	
			max = trackList[i].getRearData();
			maxPtr = trackList + i;
			ii = i;
			continue;
		}
	}
	if (maxPtr) {
		//如果找到最小的存在数字的队列
		return maxPtr;
	}
	else if(nPtr)
	{
		//如果找到为空的，且没有找到最小的存在数字的队列
		return nPtr;
	}
	else
	{
		return NULL;
	}
}

bool Manager::isAllNULL()
{
	for (int i = 0; i < trackNum; i++)
	{
		if (!trackList[i].empty())
			return false;
	}
	return true;
}

bool Manager::haveEmpty()
{
	for (int i = 0; i < trackNum; i++)
	{
		if (trackList[i].empty())
			return true;
	}
	return false;
}

int Manager::getEmptyTrack()
{
	for (int i = 0; i < trackNum; i++)
	{
		if (trackList[i].empty())
			return i;
	}
	return -1;
}

void Manager::outTrain()
{
	//开始尝试清一波队列
	int temptNum = -1;
	while (true)
	{
		MyQueue<int> * p = getMinFTrack(temptNum);
		if (!p)
		{
			return;
		}
		if (p->getFrontData() != waitNum)
			//如果不能清理
			return;
		cout<<"                     -------->数字" << p->outQueue()<<"在"<<temptNum<<"号铁轨出轨道" << endl;
		waitNum++;
	}
}

void Manager::initData()
{
	for (int i = 0; i < trackNum; i++)
	{
		trackList[i].clear();
	}
	waitNum = 1;
	
}
