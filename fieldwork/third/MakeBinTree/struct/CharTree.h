﻿#pragma once
#include "BinaryTree.h"
#include "struct/stack.h"
#include "struct/myQueue.h"
#include"SuperList.h"
#include <tuple>
#include<string>
#include<iostream>
using namespace std;
class CharTree:public BinaryTree<char>
{
public:
	CharTree();
	~CharTree();
    TreeNode<char>* getRootNode();
	void getTree(string str,int model); //1 表示输入的是前序，输入2表示层序
	
	void printSelf(int model);  //1.表示前序输出，2 表示中序输出，3表示后序输出

    void reconstruction(string str1, string str2);  //str1 表示前序输出序列 ，str2 表示中序输出这个序列

    tuple<TreeNode<char>*,string> find(char key);		//先简单前序搜索，用栈代替递归


    SuperList<string> splitString(string str, char key);


protected:

    string tempStr;
    TreeNode<char>* reconSonTree(string str1);
};

