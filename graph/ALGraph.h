#pragma once
#include <queue>
#include <vector>
// #include "LinkList.h"
#include "GraphInfo.h"
#ifndef ALGRAPH_H
#define ALGRAPH_H
#define MAX 1000
#define TERMNUMBER 6
#define CREDITMAX 10

class ALGraph
{
public:
	int vexnum;			 // 顶点数目
	int arcnum;			 // 弧数目
	VNode vertices[MAX]; // 邻接表
public:
	ALGraph();
	~ALGraph();
	VNode *getVertices();
	void CreateGraph(int vnum, int anum, VNode data[], ArcInfo arcList[]); // 创建图
	void addVex(VNode vex[], int prenum, int pre[], int postnum, int post[]);
	void deleteVex(VNode vex);
	void renewVex(VNode vex);
	void DisGraph();	 // 展示
	VNode *Order_slow(); // 均匀分布
	VNode *Order_fast(); // 紧凑分布
	void change_Limit(); // 修改规则
	void Arrange(VNode *vex, int choose);
	void IndegreeCal(); // 统计每个顶点的入度
						// void printToFile(queue<VNode> vs);

private:
	int LocateVex(VNode v); // 根据顶点信息，返回顶点坐标
};

#endif