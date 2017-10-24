#include "CharTree.h"


CharTree::CharTree()
{
}

CharTree::~CharTree()
{
}

TreeNode<char> *CharTree::getRootNode()
{
    return root;
}

void CharTree::getTree(string str, int model)
{
	this->clear();
	if (model == 1) {
		Stack<TreeNode<char>*> s;
		char nowC;
		//用栈，代替递归
		Direction nowDir=Direction::Left;  //指向当前延伸方向
		this->addRootNode(str[0]);
		TreeNode<char>* nowP = root;
		for (int i = 1; i <str.length(); i++)
		{
			nowC = str[i];			//
			if (nowC == '#') {
				if (nowDir == Direction::Left) {
					//如果当前是个终止符号，就终止当前的延伸，把延伸方向变为向右边延伸
					nowP->lNode = nullptr;
					nowDir = Direction::Right; 
				}else{
					//如果当前是往右延伸，但是碰到终止符号了，就不能往右边延伸，弹栈，但是方向不变
					nowP->rNode = nullptr;
					
					if (s.empty()) {
						//如果栈为空，而且当前不能向右延伸，也就是说，根节点的右节点为空，那么就结束了
						return;
					}
					nowP = s.pop();		
				}
			}
			else
			{
				//就是说就，没有碰到终止符号
				if (nowDir == Direction::Left) {
					//如果当前延伸方向是向左延伸;,且方向不变
					s.push(nowP);
					nowP->lNode = new TreeNode<char>(nowC);
					nowP = nowP->lNode;
				}else{
					//如果当前是往右延伸，方向要变
					nowP->rNode = new TreeNode<char>(nowC);
					nowP = nowP->rNode;
					nowDir = Direction::Left;
				}
			}
		}
	}
	else
	{
		//如果是层次
		//那么用队列
		MyQueue<TreeNode<char>*> s;
		addRootNode(str[0]); //先添加根节点
		Direction nowDir = Direction::Left;
		s.inQueue(root);
		for (int i = 1; i < str.length(); i++)
		{
			if (str[i] == '#') {
				if (nowDir==Direction::Left)
				{
					s.getFrontData()->lNode = nullptr;  //如果是向左边
					nowDir = Direction::Right;
				}
				else
				{
					s.outQueue()->rNode = nullptr; 
					nowDir = Direction::Left;
				}
			}
			else
			{
				//就是说就，没有碰到终止符号
				if (nowDir == Direction::Left) {
					TreeNode<char>* l= new TreeNode<char>(str[i]);
					s.getFrontData()->lNode = l;
					s.inQueue(l); //把新加的有效的左节点加入入队
					nowDir = Direction::Right;
				}
				else {
					//如果当前是往右延伸，方向要变
					TreeNode<char>* r = new TreeNode<char>(str[i]);
					s.outQueue()->rNode = r;	//当增加右边节点是，就是要出队列的时候
					s.inQueue(r); //把新加的有效的左节点加入入队
					nowDir = Direction::Left;
				}
			}
		}
		
	}
	
}

void CharTree::printSelf(int model)
{
	doSomeThing(model, [](TreeNode<char> * t)->void {
        std::cout << t->data;
	});
	cout<<  endl;
}

void CharTree::reconstruction(string str1, string str2)  //
{
	clear();
    root=reconSonTree(str1.c_str(),str2.c_str());
    printSelf(1);
}

tuple<TreeNode<char>*,string> CharTree::find(char key)
{
	if (!root) {
        return make_tuple(nullptr,string());
	}
    if(root->data==key){
        return make_tuple(root,string());
    }
	////下面的搜索算法是一种比较便利的前序搜索算法，但是缺点就是不能输出他的祖先节点
	////是前序搜索
	//Stack<TreeNode<char>*> s,parent;	
	//TreeNode<char>* nowP = root;
	//s.push(NULL);
	//while (nowP)
	//{
	//	if (nowP->data==key)
	//	{
	//		while (!parent.empty())
	//		{
	//			cout << parent.pop()->data;
	//		}
	//		cout << endl;
	//		return nowP;
	//	}
	//	if (nowP->rNode)
	//	{
	//		s.push(nowP->rNode);//将右边节点入栈，等左边子树查完
	//	}		
	//	if (nowP->lNode)
	//	{
	//		parent.push(nowP);
	//		nowP = nowP->lNode;
	//	}
	//	else
	//	{
	//		nowP = s.pop();
	//		parent.pop();
	//	}
	//}
	//return nullptr;


	//搜索算法，
	//由于想不到更好的算法，姑且这样
	Stack<TreeNode<char>*> s;
	s.push(nullptr);
	s.push(root);
	TreeNode<char>* nowL;
	TreeNode<char>* nowR;
	while (true)
	{
		nowL = s.top()->lNode;
		nowR = s.top()->rNode;

        if ((nowL&&nowL->data == key)||(nowR&&nowR->data == key)) {  //左节点或者右节点是
            string parentStr;   //返回的所有的父亲节点字符串
			while (s.top())
			{
                parentStr+=s.pop()->data;
            }
            return make_tuple(nowL&&nowL->data==key?nowL:nowR,parentStr);
        }

		if (nowL)
		{
			s.push(nowL);
		}
		else
		{
			if (nowR)
			{
				s.push(nowR);
			}
			else
			{
				//如果左右节点都为空，那么就开始弹栈
				//一直弹到某个节点存在右边节点
				//这里一定要理清楚关系，不然是坑
				TreeNode<char>* n = s.pop();
                while (s.top()&&s.top()->rNode == n||((s.top())&&!s.top()->rNode))
				{
                    //TreeNode<char>* n = s.pop();
                    n = s.pop();
				}
                if (!s.top())
				{
                    return make_tuple(nullptr,string());
				}
				s.push(s.top()->rNode);
			}
		}


		


	}
    return make_tuple(nullptr,string());
	

}

string CharTree::getFloorOut()
{
    return string();

}


TreeNode<char> *CharTree::reconSonTree(QString str1, QString str2)
{
    if(str1.isEmpty())
        return nullptr;
    QStringList list=str2.split(str1[0]);
    TreeNode<char>* node=new TreeNode<char>(str1[0].toLatin1());
    if(!list.at(0).isEmpty()){
        node->lNode=reconSonTree(str1.mid(1),list.at(0));
    }
    if(list.length()==2&&!list.at(1).isEmpty()){
        node->rNode=reconSonTree(str1.mid(1),list.at(1));
    }
    return node;
}
