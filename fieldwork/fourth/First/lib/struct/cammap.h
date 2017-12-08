#pragma once
#include "ammap.h"
#include "sstack.h"



/*
 * 字符图
 * 邻接矩阵
 * 非模板类非虚类,
 */
class CAMMap :
	public AMMap<char>
{
public:
    CAMMap(int capacity, MapType type=MapType::dirMap);
    CAMMap(const CAMMap& old);
    ~CAMMap();
    void printMap();
};

