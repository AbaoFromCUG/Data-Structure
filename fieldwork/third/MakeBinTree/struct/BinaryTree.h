#pragma once
#include"myQueue.h"
template<typename T>
struct TreeNode{
	TreeNode<T>* rNode;
	TreeNode<T>* lNode;
	T data;
	TreeNode(T t, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr) {
		lNode = l;
		rNode = r;
		data = t;
	}

};
enum Direction
{
	Left,
	Right
};
template<typename T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	void addRootNode(T t);
	void swapTree();
	void swapSonTree(TreeNode<T>* node); //递归函数

	TreeNode<T> *find(T key);
	bool appendOneNode(TreeNode<T>* parent, T t, Direction dir);
	bool insertAfter(TreeNode<T>* parent, T t, Direction dir,Direction mvDir);
    //一个用来遍历的函数 1, 代表前序，2代表中序，3代表后序
    bool doSomeThing(int model,void(*visit)(TreeNode<T> *t));
    //一个用来遍历的函数代表层序
    bool doSomeThing(void(*visit)(TreeNode<T> *t,int nfl));
	void clear(); //清空一个二叉树

	void deleteSonTree(TreeNode<T>* node);
protected:
	TreeNode<T>* root;
	void(*tempVisit)(TreeNode<T>*t);  //doSomeThing 的临时函数指针

	//递归的几种顺序
	void recursiveDo1(TreeNode<T>* node);
	void recursiveDo2(TreeNode<T>* node);
	void recursiveDo3(TreeNode<T>* node);
};

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
	clear();
}

template<typename T>
inline void BinaryTree<T>::addRootNode(T t)
{
	if (root) {
		throw "Tree is not Empty";
	}
	else
	{
		root = new TreeNode<T>(t);
	}
}

template<typename T>
inline void BinaryTree<T>::swapTree()
{
	if (root)
	{
		swapSonTree(root);
	}
}

template<typename T>
inline void BinaryTree<T>::swapSonTree(TreeNode<T>* node)
{
	if (node->lNode)
	{
		swapSonTree(node->lNode);
	}
	if (node->rNode)
	{
		swapSonTree(node->rNode);
	}
	
	TreeNode<T>* mid = node->lNode;
	node->lNode = node->rNode;
	node->rNode = mid;
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T key)
{
    return nullptr;
}

template<typename T>
inline bool BinaryTree<T>::appendOneNode(TreeNode<T>* parent, T t, Direction dir)
{
	if (dir == Direction::Left) {
		if (parent->lNode) {
			throw "error: the append Node's lNode isn't nullptr";
		}
		else
		{
			parent->lNode = new TreeNode<T>(t);
		}
	}
	else if (dir == Direction::Right) {
		if (parent->rNode) {
			throw "error: the append Node's rNode isn't nullptr";
		}
		else
		{
			parent->rNode = new TreeNode<T>(t);
		}
	}
	return false;
}

template<typename T>
inline bool BinaryTree<T>::insertAfter(TreeNode<T>* parent, T t, Direction dir, Direction mvDir)
{
	if (dir == Direction::Left) {
		TreeNode<T>* mid = parent->lNode;
		parent->lNode = new TreeNode<T>(t);
		if (mvDir == Direction::Left) {
			parent->lNode->lNode = mid;
		}
		else
		{
			parent->lNode->rNode = mid;
		}
	}
	else
	{
		TreeNode<T>* mid = parent->rNode;
		parent->rNode = new TreeNode<T>(t);
		if (mvDir == Direction::Left) {
			parent->rNode->lNode = mid;
		}
		else
		{
			parent->rNode->rNode = mid;
		}

	}
	return true;
}

template<typename T>
inline bool BinaryTree<T>::doSomeThing(int model, void(*visit)(TreeNode<T>*t))
{
    if(!root)
        return false;
	tempVisit = visit;
	if (model == 1) {
		recursiveDo1(root);
	}
	else if (model == 2) {
		recursiveDo2(root);
	}else if (model==3)
	{
		recursiveDo3(root);
    }
    return true;
}

template<typename T>
bool BinaryTree<T>::doSomeThing(void (*visit)(TreeNode<T> *t, int num))
{
    //由于是层次遍历
    /*
     *
     * 但是正常的广度优先的搜索算法,
     * 又没有办法知道深度
     */
    if(root){
        return false;
    }
    MyQueue<TreeNode<T>*> *q=new MyQueue<TreeNode<char>*>;
    MyQueue<TreeNode<T>*> *p=new MyQueue<TreeNode<char>*>;
    p->inQueue(root);  //p是入队的队列,q是出队列的队列
    int floorNum=0; //第几层
    visit(root,floorNum);
    floorNum++;
    while (!p->empty()) {
        TreeNode<char>* mid=p;
        p=q;
        q=mid;
        while(!q->empty()) {
            TreeNode<char>* node=q->outQueue();
            if(node->lNode){
                p->inQueue(node->lNode);
                visit(node->lNode,floorNum);
            }
            if(node->rNode){
                p->inQueue(node->rNode);
                visit(node->rNode,floorNum);
            }
        }
        floorNum++;
    }
    delete p;
    delete q;
    return true;
}

template<typename T>
inline void BinaryTree<T>::clear()
{
	if(root)
		deleteSonTree(root);
	root = nullptr;
}

template<typename T>
inline void BinaryTree<T>::deleteSonTree(TreeNode<T>* node)
{
	/*
	 * 简单起见，递归
	 */
	if(node->lNode)deleteSonTree(node->lNode);
	if(node->rNode)deleteSonTree(node->rNode);
    delete node;
}

template<typename T>
inline void BinaryTree<T>::recursiveDo1(TreeNode<T>* node)
{
	//前序递归
	tempVisit(node);
	if(node->lNode)recursiveDo1(node->lNode);
	if(node->rNode)recursiveDo1(node->rNode);
}

template<typename T>
inline void BinaryTree<T>::recursiveDo2(TreeNode<T>* node)
{
	//中序递归
	if(node->lNode ) recursiveDo2(node->lNode)  ;
	tempVisit(node);
	if(node->rNode)recursiveDo2(node->rNode)  ;
}

template<typename T>
inline void BinaryTree<T>::recursiveDo3(TreeNode<T>* node)
{
	if(node->lNode)recursiveDo3(node->lNode) ;
	if(node->rNode)recursiveDo3(node->rNode)  ;
	tempVisit(node);
}
