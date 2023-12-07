#include <iostream>
#include "ALGraph.h"
#include "GraphInfo.h"
#include "LinkList.h"
#include <vector>
using namespace std;
string sp = "******";

void setClass(ALGraph *graph);
void addVex(ALGraph *);
void deleteVex(ALGraph *);
void renewVex(ALGraph *);

void showMenu()
{
	cout << "1.预定课程导入" << endl;
	cout << "2.添加课程" << endl;
	cout << "3.删除课程" << endl;
	cout << "4.更新课程" << endl;
	cout << "5.拓扑排序" << endl;
	cout << "6.排序结果" << endl;
	cout << "7.方案选择" << endl;
	cout << "8.修改限制" << endl;
	cout << "9.展示图" << endl;
	cout << "10.退出" << endl;
	cout << "请选择你的英雄:";
}

int main(void)
{
	// 创建一个ALGraph类型的指针变量graph
	ALGraph *graph = new ALGraph();
	// 创建一个VNode类型的指针变量slow，初始值为NULL
	VNode *slow = NULL;
	// 创建一个VNode类型的指针变量fast，初始值为NULL
	VNode *fast = NULL;
	// 创建一个VNode类型的指针变量p，初始值为NULL
	VNode *p = NULL;
	// 创建一个int类型的变量choose，初始值为0
	int choose = 0;
	// 打印出欢迎信息
	cout << sp << "欢迎来到课程管理系统" << sp << endl;
	// 创建一个无限循环
	while (true)
	{
		// 调用showMenu函数，显示菜单
		showMenu();
		// 创建一个int类型的变量choose，初始值为0
		int choose;
		// 调用cin函数，输入choose的值
		cin >> choose;
		// 根据choose的值，进行不同的操作
		switch (choose)
		{
		// 如果choose的值为1，调用setClass函数，设置课程
		case 1:
			setClass(graph);
			cout << endl;
			break;
		// 如果choose的值为2，调用addVex函数，添加顶点
		case 2:
			addVex(graph);
			cout << endl;
			break;
		// 如果choose的值为3，调用deleteVex函数，删除顶点
		case 3:
			deleteVex(graph);
			cout << endl;
			break;
		// 如果choose的值为4，调用renewVex函数，更新顶点
		case 4:
			renewVex(graph);
			cout << endl;
			break;
		// 如果choose的值为5，调用graph的Order_slow函数，获取slow
		case 5:
			slow = graph->Order_slow();
			cout << endl;
			// 调用graph的Order_fast函数，获取fast
			fast = graph->Order_fast();
			cout << endl;
			break;
		// 如果choose的值为6，判断fast和slow是否为空，不为空则调用graph的Arrange函数，进行拓扑排序
		case 6:
			if (fast != NULL || slow != NULL)
			{
				p = fast;
				cout << "拓扑排序结果为：" << endl;
				cout << "fast:" << endl;
				if (p != NULL)
				{
					for (int i = 0; i < graph->vexnum; i++)
					{
						cout << p->data.index << " ";
						p++;
					}
				}
				else
				{
					cout << "none" << endl;
				}
				cout << endl
					 << "slow:" << endl;
				p = slow;
				if (p != NULL)
				{
					for (int i = 0; i < graph->vexnum; i++)
					{
						cout << p->data.index << " ";
						p++;
					}
				}
				else
				{
					cout << "none" << endl;
				}
			}
			else
			{
				cout << "没有拓扑排序结果" << endl;
			}
			cout << endl;
			break;
		// 如果choose的值为7，调用graph的Arrange函数，进行拓扑排序
		case 7:
			cout << "请输入你的选择(slow:1  fast:2):";
			cin >> choose;
			if (choose == 1 && slow != NULL)
			{
				graph->Arrange(slow, 1);
			}
			else if (choose == 2 && fast != NULL)
			{
				graph->Arrange(fast, 2);
			}
			break;
		// 如果choose的值为8，调用graph的change_Limit函数，修改课程限制
		case 8:
			graph->change_Limit();
			break;
		// 如果choose的值为9，调用graph的DisGraph函数，显示课程图
		case 9:
			graph->DisGraph();
			break;
		// 如果choose的值为10，结束程序
		case 10:
			return 0;
		}
	}

	return 0;
}

void setClass(ALGraph *graph)
{
	vector<VNode> data(14);
	vector<ArcInfo> arcList(19);

	data[0] = {1, "程序设计基础", 2};
	data[1] = {2, "离散数学", 3};
	data[2] = {3, "数据结构", 4};
	data[3] = {4, "汇编语言", 3};
	data[4] = {5, "程序设计与分析", 2};
	data[5] = {6, "计算机原理", 3};
	data[6] = {7, "编译原理", 4};
	data[7] = {8, "操作系统", 4};
	data[8] = {9, "高等数学", 7};
	data[9] = {10, "线性代数", 5};
	data[10] = {11, "普通物理", 2};
	data[11] = {12, "数值分析", 3};
	data[12] = {13, "软件工程", 3};
	data[13] = {14, "数据库原理", 3};

	arcList[0] = {data[0], data[1], 2};
	arcList[1] = {data[0], data[3], 2};
	arcList[2] = {data[0], data[2], 2};
	arcList[3] = {data[0], data[11], 2};
	arcList[4] = {data[1], data[2], 2};
	arcList[5] = {data[3], data[4], 2};
	arcList[6] = {data[4], data[12], 2};
	arcList[7] = {data[2], data[4], 2};
	arcList[8] = {data[2], data[6], 2};
	arcList[9] = {data[6], data[13], 2};
	arcList[10] = {data[4], data[6], 2};
	arcList[11] = {data[8], data[11], 2};
	arcList[12] = {data[8], data[9], 2};
	arcList[13] = {data[8], data[10], 2};
	arcList[14] = {data[9], data[11], 2};
	arcList[15] = {data[10], data[5], 2};
	arcList[16] = {data[5], data[7], 2};
	arcList[17] = {data[7], data[13], 2};
	arcList[18] = {data[2], data[7], 2};

	graph->CreateGraph(data.size(), arcList.size(), data.data(), arcList.data());
}

void addVex(ALGraph *g)
{
	int pre = 0, post = 0;
	int index, credit;
	string name;
	cout << sp << "课程增加" << sp << endl;
	cout << "温馨提示:请不要输入已经存在的课程编号或名字" << endl
		 << "可使用 9.展示图 查看所有课程信息(包含已删除的)" << endl;
	cout << "请输入课程编号:";
	cin >> index;
	cout << "请输入课程名称:";
	cin >> name;
	cout << "请输入课程学分:";
	cin >> credit;
	vector<VNode> data(1);
	data[0] = {index, name, credit};
	cout << "请输入课程先修课数量:";
	cin >> pre;
	vector<int> preList(pre);
	for (int i = 0; i < pre; i++)
	{
		cout << "请输入课程先修课编号:";
		cin >> preList[i];
	}
	cout << "请输入课程后修课数量:";
	cin >> post;
	vector<int> postList(post);
	for (int i = 0; i < post; i++)
	{
		cout << "请输入课程后修课编号:";
		cin >> postList[i];
	}
	g->addVex(data.data(), preList.size(), preList.data(), postList.size(), postList.data());
}

void deleteVex(ALGraph *g)
{
	VNode n;
	cout << sp << "课程删除" << sp << endl;
	cout << "请输入课程编号:";
	cin >> n.data.index;
	cout << "请输入课程名称:";
	cin >> n.data.classname;
	cout << "请输入课程学分:";
	cin >> n.data.credit;
	g->deleteVex(n);
}

void renewVex(ALGraph *g)
{
	VNode n;
	cout << "此功能只能用于重新恢复曾经删除的课程" << endl
		 << "如果想要增加新课程,请使用 2.添加课程 功能" << endl;
	cout << "this function is only used to have the course again that you have deleted" << endl;
	cout << sp << "课程更改" << sp << endl;
	cout << "请输入课程编号:";
	cin >> n.data.index;
	cout << "请输入课程名称:";
	cin >> n.data.classname;
	cout << "请输入课程学分:";
	cin >> n.data.credit;
	g->renewVex(n);
}
