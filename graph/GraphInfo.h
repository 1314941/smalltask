#pragma once
#ifndef GRAPHINFO_H
#define GRAPHINFOI_H
#include <string.h>
using namespace std;

// 课程信息
struct Course
{
	int index;
	string classname;
	int credit; // 学分
};

// 弧结点
struct ArcNode // 存放顶点的邻接点的链表->邻接表
{
	int adjvex; // 邻接点位置
	int weight; // 比重
	struct ArcNode *nextarc;
};

// 顶点结点
struct VNode
{
	Course data;
	int in; // 入度
	ArcNode *firstarc;
};

// 弧信息
struct ArcInfo
{
	VNode From; // 起点
	VNode To;	// 终点
	int weight; // 比重
};

struct Limit
{
	int term = 6;
	int max_credit = 10;
	int max_class = 8;
};

#endif
