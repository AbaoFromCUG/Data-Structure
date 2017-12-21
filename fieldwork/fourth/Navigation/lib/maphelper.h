#ifndef MAPHELPER_H
#define MAPHELPER_H
#include<vector>
#include<iostream>
using namespace std;
class MMap
{
    /*
    邻接矩阵法
    */
public:
    MMap(int cap) {
        m_iCap = cap;
        m_map = new int*[cap];  //声明二维数组并初始化
        m_pNodeArray = new int[cap];
        for (int i = 0; i < cap; i++)
        {
            m_map[i] = new int[cap];
            for (int j = 0; j < cap; j++)
            {
                m_map[i][j] = INT32_MAX;   //初始化为无限大，也就是int 可以表示最大的数
            }
        }

        m_iEdgeCount = 0;
        m_iNodeCount = 0;
    }
    bool isEmpty() {
        return this->m_iNodeCount >= m_iCap;  //当节点数大于等于容量时，就代表满了
    }
    int addNode(int val) {
        if (isEmpty()) {
            throw "error, map is full";
        }
        m_pNodeArray[m_iNodeCount] = val; //这个是传进一个编号，然后创建一个节点
        //this->m_iNodeCount++;
        return ++m_iNodeCount;  //返回创建的节点的下标
    }
    void insertEdge(int col, int row, int val) {
        //非法处理
        if (col < 0 || row < 0 || col >= m_iNodeCount || row >= m_iNodeCount) {
            throw "error ";
        }
        m_map[col][row] = val;  //传进两个点的下标，和边的权值
        m_map[row][col] = val;  //wuxiang
        this->m_iEdgeCount++;  //
    }
    ~MMap() {
        for (int i = 0; i < m_iCap; i++) {
            delete [] m_map[i];
        }
        //析构函数
        delete[]m_map;
        delete[]m_pNodeArray;
        //malloc
        //free
    }
    void printMap() {
        //打印点表
        for (int i = 0; i < m_iNodeCount; i++)
        {
            cout << m_pNodeArray[i] << "-";
        }
        cout << "打印边" << endl;
        //打印边表
        for (int i = 0; i < m_iNodeCount; i++)
        {
            for (int j = 0; j < m_iNodeCount; j++)
            {
                if ( m_map[i][j]!=INT32_MAX)
                {
                    cout << m_map[i][j];
                }
                else
                {
                    cout << " ";
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    int getMin(vector<int>& min) {
        int m = INT32_MAX;
        int index = -1;
        for (int i = 0; i < min.size(); i++)
        {
            if (!isHasFind(i)&&min[i] < m) {
                m = min[i];
                index = i;
            }
        }
        return index;
    }
    void coutMinWay(int from,int aim) {
        //初始化已经找到了最小路径的点
        hasFindMinWay.clear();
        hasFindMinWay.push_back(from);   //源点到源点本身，最短路径已经找到了

        //初始化最小的路径表
        vector<int> waitMin;  //直接下标
        //我们需要写一个保存每个节点当前最小路径的路径
        vector<vector<int>> waitWay;

        for (int i = 0; i < m_iNodeCount; i++) {
            waitMin.push_back(m_map[from][i]);		//把从源点能直接到的
            vector<int> way;
            if (m_map[from][i]!=INT32_MAX)
            {
                way.push_back(from);
                way.push_back(i);
            }
            waitWay.push_back(way);
        }
        waitMin[from] = 0;
        //源点To源点的最短路径
        waitWay[from].push_back(from);

        //开始算法
        while (hasFindMinWay.size()!=this->m_iNodeCount)
        {
            //第一步，在待选的路径里，选出最短的
            int index = getMin(waitMin);
            int nowWay = waitMin[index];  //选出的最短路径的长度
            for (int i = 0; i < m_iNodeCount; i++) {
                if (m_map[index][i]!=INT32_MAX)
                {
                    if (nowWay + m_map[index][i] < waitMin[i]) {
                        //如果通过当前的路径访问节点路径小于节点当前路径长度
                        waitMin[i] = nowWay + m_map[index][i];
                        waitWay[i] = waitWay[index];
                        waitWay[i].push_back(i);  //路径存储
                    }
                }
            }
            hasFindMinWay.push_back(getMin(waitMin));
        }

        //算法结束
        //

        cout << "从编号为：" << m_pNodeArray[from] << "到编号为" << m_pNodeArray[aim] << "的最短路径如下" << endl;
        for (int i = 0; i < waitWay[aim].size(); i++)
        {
            cout <<"编号为"<< m_pNodeArray[waitWay[aim][i]] << "---->";
        }
        cout << endl;
        cout << "最小路径" << waitMin[aim] << endl;






    }
    bool isHasFind(int index) {
        for (int i = 0; i < hasFindMinWay.size(); i++)
        {
            if (hasFindMinWay[i] == index) {
                return true;
            }
        }
        return false;
    }

private:
    int** m_map;  //二维数组
    int *m_pNodeArray;  //存储每个节点的编号
    int m_iNodeCount;	//当前顶点数
    int m_iEdgeCount;	//当前边数 //同一条无向边只算一条
    int m_iCap;	    //容量
    vector<int> hasFindMinWay;//保存已经找到最短路径的节点
};

#endif // MAPHELPER_H

