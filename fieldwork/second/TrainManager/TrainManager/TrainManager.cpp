// TrainManager.cpp: 定义控制台应用程序的入口点。
//

/*

【要求】使用队列完成，n>20，入轨序列随机产生，输出每个车厢是经过哪个缓存铁轨而来。

*/

#include "stdafx.h"
#include "Manager.h"
#include <iostream>
#include <time.h>
#define random(x) (rand()%x)



int * a;
int length;
void deleteA();
void initA(int num);
void printA();

using namespace std;
int main()
{
	srand((int)time(0));
	while (true)
	{
		int cmd = 0;
		cout << "请输入你要进行的操作:\n\t0）退出\n\t1）自动生成随机数字运算\n\t2)您输入一串数字进行运算\n>";
		cin >> cmd;
		if (cmd == 0) {
			cout << "正在退出程序" << endl;
			return 0;
		}
		else if (cmd==1)
		{
			int trackNum = 3;
			int maxNum = 10;
			cout << "请输入你想要设定的转运轨道数字（大于3）\n>";
			cin >> trackNum;
			while (trackNum<=3)
			{
				cout << "请重新输入你想要设定的转运轨道数字（大于3）\n>";
				cin >> trackNum;

			}
			cout << "请输入你想要随机生成的车厢长度（大于5）\n>";
			cin >> maxNum;
			while (maxNum <= 5)
			{
				cout << "请重新输入你想要随机生成的车厢长度（大于5）\n>";
				cin >> maxNum;
			}
			Manager m(trackNum);
			for (int i = 0; i < 10; i++)
			{
				initA(maxNum);
				printA();
				m.startRun(a, maxNum);
				deleteA();
				cout << endl;
			}

			cout << "运行完毕" << endl;
		}
		else if (cmd == 2)
		{
			int trackNum = 3;
			int maxNum = 10;
			cout << "请输入你想要设定的转运轨道数字（大于3）\n>";
			cin >> trackNum;
			while (trackNum <= 3)
			{
				cout << "请重新输入你想要设定的转运轨道数字（大于3）\n>";
				cin >> trackNum;

			}
			cout << "请输入你想输入的的车厢长度（大于5）\n>";
			cin >> maxNum;
			while (maxNum <= 5)
			{
				cout << "请重新输入你想输入的的车厢长度（大于5）\n>";
				cin >> maxNum;
			}
			cout <<"我将不会对你输入的数字进行检查，请慎重" << endl;
			int* t = new int[maxNum];
			for (int i = 0; i < maxNum; i++)
			{
				int j;
				cin >> j;
				t[i] = j;
			}
			Manager m(trackNum);
			m.startRun(t, maxNum);
			delete[]t;
			
		}

	}


	
	
	system("pause");
    return 0;
}

void deleteA()
{
	delete[]a;
	a = NULL;
	length = 0;
}

void initA(int num)
{
	length = num;
	a = new int[num];
	for (int i = 0; i < num; i++)
	{
		a[i] = 1+i;
	}
	//交换很多次，提高混乱度，充当随机
	for (int i=0;i<length * 23;i++)
	{
		int index = random(length);
		int mid = a[index];
		a[index] = a[length % (length / 3 + 1)];
		a[length % (length / 3 + 1)] = mid;
	}
}

void printA()
{
	for (int i = 0; i < length; i++)
	{
		cout << a[i]<<"  ";
	}
	cout << endl;
}
