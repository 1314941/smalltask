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
	int vexnum;			 // ������Ŀ
	int arcnum;			 // ����Ŀ
	VNode vertices[MAX]; // �ڽӱ�
public:
	ALGraph();
	~ALGraph();
	VNode *getVertices();
	void CreateGraph(int vnum, int anum, VNode data[], ArcInfo arcList[]); // ����ͼ
	void addVex(VNode vex[], int prenum, int pre[], int postnum, int post[]);
	void deleteVex(VNode vex);
	void renewVex(VNode vex);
	void DisGraph();	 // չʾ
	VNode *Order_slow(); // ���ȷֲ�
	VNode *Order_fast(); // ���շֲ�
	void change_Limit(); // �޸Ĺ���
	void Arrange(VNode *vex, int choose);
	void IndegreeCal(); // ͳ��ÿ����������
						// void printToFile(queue<VNode> vs);

private:
	int LocateVex(VNode v); // ���ݶ�����Ϣ�����ض�������
};

#endif