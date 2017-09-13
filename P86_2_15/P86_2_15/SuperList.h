#pragma once

//µ•œÚ¡¥±Ì
template<typename T>
struct ListNode {
	T date;
	ListNode(T& t) {

	}
	ListNode* next;
};
template<typename T>
class SuperList
{
public:
	SuperList();
	virtual ~SuperList();
}; 

template<typename T>
inline SuperList<T>::SuperList()
{
}

template<typename T>
inline SuperList<T>::~SuperList()
{
}
