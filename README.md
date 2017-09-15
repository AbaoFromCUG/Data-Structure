# 数据结构的各种实习

### 作业p84 2.6
实现了一个顺序表，一些基本功能，模板的

### 作业p86 2.15

#### 第一个类LinkedList
```cpp
struct Item{
    int date;
    Item* linked;
}
```
节点的单向链表
功能简单，归并，全部排序，增删该查


#### 第二个类，实现了实习一的关于链表的一些要求

```cpp
template<typename T>
struct ListNode {
	T date;
	ListNode* link;
    ....
};
```
各全模板，可自定义排序，通过传递函数指针
重载了排序函数 begin ,end, sortFun*;

###  实习一
start


