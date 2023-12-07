#pragma once
#ifndef GRAPHINFO_H
#define GRAPHINFOI_H
#include <string.h>
using namespace std;

// �γ���Ϣ
struct Course
{
	int index;
	string classname;
	int credit; // ѧ��
};

// �����
struct ArcNode // ��Ŷ�����ڽӵ������->�ڽӱ�
{
	int adjvex; // �ڽӵ�λ��
	int weight; // ����
	struct ArcNode *nextarc;
};

// ������
struct VNode
{
	Course data;
	int in; // ���
	ArcNode *firstarc;
};

// ����Ϣ
struct ArcInfo
{
	VNode From; // ���
	VNode To;	// �յ�
	int weight; // ����
};

struct Limit
{
	int term = 6;
	int max_credit = 10;
	int max_class = 8;
};

#endif
