#pragma once
#include "BinaryTree.h"
#include "struct/stack.h"
#include "struct/myQueue.h"
#include<string>
#include<iostream>
#include<QString>
#include<QStringList>
using namespace std;
class CharTree:public BinaryTree<char>
{
public:
	CharTree();
	~CharTree();
	void getTree(string str,int model); //1 表示输入的是前序，输入2表示层序
	
	void printSelf(int model);  //1.表示前序输出，2 表示中序输出，3表示后序输出

	void reconstruction(string str1, string str2);  //str1 表示前序输出序列 ，str2 表示中序输出这个序列

	TreeNode<char>* find(char key);		//先简单前序搜索，用栈代替递归



protected:
    TreeNode<char>* reconSonTree(QString  str1, QString str2);
	
};

