// InterviewScore.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include <iostream>

#include<fstream>

#include<string>

#include<time.h>

using namespace std;


void sort(int b[], int m);


int main()
{
	const int n = 2000, m = 1000;
	int a[n] = { 0 }, b[m] = { 0 };
	srand((int)time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = (int)(101.0*rand() / (RAND_MAX + 1.0));
	}
	ofstream out("成绩.txt");
	if (!out)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}
	for (int i = 0; i < n; i++)
	{
		out << a[i] << " ";
	}
	out.close();
	for (int i = 0; i < m; i++)
	{
		b[i] = a[i];
	}
	sort(b, m);
	for (int i = 0; i < n - m; i++)
	{
		if (b[0] < a[n - m + i])
		{
			b[0] = a[n - m + i];
			sort(b, m);
		}
	}
	ofstream outfile("最高成绩.txt");
	if (!outfile)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}
	for (int i = 0; i < m; i++)
	{
		outfile << b[i] << " ";
	}
	outfile.close();
	for (int i = 0; i < m; i++)
	{
		cout << b[i] << " ";
	}
	return 0;
}

void sort(int b[], int m)
{
	int temp;
	for (int j = 1; j < m; j++)
	{
		for (int k = 0; k < m - j; k++)
		{
			if (b[k] > b[k + 1])
			{
				temp = b[k];
				b[k] = b[k + 1];
				b[k + 1] = temp;
			}
		}
	}
}