#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include "LinkList.h"
#include "ALGraph.h"
#include "GraphInfo.h"
using namespace std;
#define FAST 2
#define SLOW 1
Limit limit;

void ALGraph::change_Limit()
{
	cout << "current regulation:" << endl;
	// cout << "the biggest num of courses you can have for one semester:" << limit.max_class << endl;
	cout << "the most credit you can get for one semester:" << limit.max_credit << endl;
	cout << "the num of semesters you will have:" << limit.term << endl;
	// cout << "you can change the num of courses between 3-8 " << endl;
	cout << "you can change the num of credit between 4-8" << endl;
	// cout << "change course(input 1)" << endl
	cout << "change credit (input 2)" << endl
		 << "directly exit(0) " << endl;
	int choose = 0;
	int courses, credit;
	while (true)
	{
		cout << "choose:";
		cin >> choose;
		/*if (choose == 1)
		{
			cout << "input num(3-8):" << endl;
			cin >> courses;
			if (courses < 3 || courses > 8)
			{
				cout << "false!please input again:" << endl;
			}
			else
			{
				limit.max_class = courses;
			}
		}
		else */
		if (choose == 2)
		{
			cout << "input num(4-8):" << endl;
			cin >> credit;
			if (credit < 4 || credit > 8)
			{
				cout << "false!please enter again:" << endl;
			}
			{
				limit.max_credit = credit;
			}
		}
		else if (choose == 0)
		{
			return;
		}
	}
}

ALGraph::ALGraph()
{
	arcnum = 0;
	vexnum = 0;
	for (int i = 0; i < MAX; i++)
	{
		vertices[i].in = 0;
		vertices[i].firstarc = NULL;
	}
}

ALGraph::~ALGraph()
{
}

/*
void ALGraph::CreateGraph(int vnum, int anum, VNode vexList[], ArcInfo arcList[])
{
	arcnum = anum;
	vexnum = vnum;
	for (int i = 0; i < vnum; i++)
	{
		vertices[i] = vexList[i];
	}
	for (int i = 0; i < anum; i++)
	{
		ArcNode *a = new ArcNode();
		a->adjvex = arcList[i].To.data.index - 1;
		a->nextarc = NULL;
		a->weight = arcList[i].weight;
		if (!vertices[arcList[i].From.data.index - 1].firstarc)
		{
			vertices[arcList[i].From.data.index - 1].firstarc = a;
			break;
		}
		else
		{
			ArcNode *p = vertices[arcList[i].From.data.index - 1].firstarc;
			bool flag = true;
			while (p != NULL)
			{
				if (p->adjvex == a->adjvex)
				{
					flag = false;
				}
				p = p->nextarc;
			}

			if (!flag)
			{
				cout << "边重复" << endl;
			}
			else
			{
				a->nextarc = vertices[arcList[i].From.data.index - 1].firstarc; // 头插法
				vertices[arcList[i].From.data.index - 1].firstarc = a;
				vertices[arcList[i].From.data.index - 1].in++; // 入度+1
			}
		}
	}
}
*/

VNode *ALGraph::getVertices()
{
	VNode *v = new VNode[vexnum];
	for (int i = 0; i < vexnum; i++)
	{
		v[i] = vertices[i];
	}
	return &v[0];
}

void ALGraph::CreateGraph(int vnum, int anum, VNode vexList[], ArcInfo arcList[])
{
	arcnum = anum;
	vexnum = vnum;
	for (int i = 0; i < vnum; i++)
	{
		vertices[i] = vexList[i];
		vertices[i].firstarc = NULL;
		vertices[i].in = 0;
	}
	for (int i = 0; i < anum; i++)
	{
		ArcNode *a = new ArcNode();
		a->adjvex = arcList[i].To.data.index - 1;
		a->nextarc = NULL;
		a->weight = arcList[i].weight;
		if (!vertices[arcList[i].From.data.index - 1].firstarc)
		{
			vertices[arcList[i].From.data.index - 1].firstarc = a;
		}
		else
		{
			/*
			ArcNode *p = vertices[arcList[i].From.data.index - 1].firstarc;
			while (p->nextarc != NULL)
			{
				p = p->nextarc;
			}
			p->nextarc = a;								   // 尾插法 不行
			vertices[arcList[i].From.data.index - 1].in++; // 入度+1
			*/
			a->nextarc = vertices[arcList[i].From.data.index - 1].firstarc; // 头插法
			vertices[arcList[i].From.data.index - 1].firstarc = a;
		}
		vertices[arcList[i].To.data.index - 1].in++; // 入度+1
	}
	cout << "CreateGraph Successfully!" << endl;
}

void ALGraph::addVex(VNode vex[], int prenum, int pre[], int postnum, int post[])
{
	int i;
	bool flag = false;
	for (i = 0; i < vexnum; i++)
	{
		if (vertices[i].data.classname == vex->data.classname || vertices[i].data.index == vex->data.index)
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
		if (vertices[i].data.classname == vex->data.classname)
		{
			cout << "you already get it " << endl;
			if (vertices[i].data.index == -1)
			{
				cout << "but the index of the course is -1" << endl
					 << "if you want to add it ,please renew the index of the course" << endl;
			}
		}
		if (vertices[i].data.index == vex->data.index)
		{
			cout << "sorry,you already get it" << endl
				 << "some course have the same index" << endl
				 << "please change the index of the course" << endl;
		}
		return;
	}

	vertices[vexnum] = vex[0];
	int arcnum = prenum + postnum;
	vector<ArcInfo> arcList(arcnum);
	for (i = 0; i < prenum; i++)
	{
		arcList[i] = {vertices[pre[i] - 1], vertices[vexnum], 2};
	}
	for (int j = 0; j < postnum; j++, i++)
	{
		arcList[i] = {vertices[vexnum], vertices[post[j] - 1], 2};
	}
	// 引用CreatGraph的后半部分
	for (i = 0; i < arcnum; i++)
	{
		ArcNode *a = new ArcNode();
		a->adjvex = arcList[i].To.data.index - 1;
		a->nextarc = NULL;
		a->weight = arcList[i].weight;
		if (!vertices[arcList[i].From.data.index - 1].firstarc)
		{
			vertices[arcList[i].From.data.index - 1].firstarc = a;
		}
		else
		{
			a->nextarc = vertices[arcList[i].From.data.index - 1].firstarc; // 头插法
			vertices[arcList[i].From.data.index - 1].firstarc = a;
		}
		vertices[arcList[i].From.data.index - 1].in++; // 入度+1
	}
	vexnum++;
	cout << "add successfully!" << endl;
	return;
}

void ALGraph::deleteVex(VNode vex)
{
	for (int i = 0; i < vexnum; i++)
	{
		if (vertices[i].data.classname == vex.data.classname)
		{
			vertices[i].data.index = -1;
			cout << "delete successfully!" << endl;
			return;
		}
	}
	cout << "can not find it" << endl;
	return;
}

void ALGraph::renewVex(VNode vex)
{
	int i;
	bool flag = false;
	for (i = 0; i < vexnum; i++)
	{
		if (vertices[i].data.classname == vex.data.classname)
		{
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		cout << "can not find it" << endl;
		return;
	}
	vertices[i].data = vex.data;
	cout << "renew successfully!" << endl;
	return;
}

void ALGraph::DisGraph()
{
	VNode *vertices = getVertices();
	string sp = "->";
	for (int i = 0; i < vexnum; i++)
	{
		ArcNode *p = vertices[i].firstarc;
		if (vertices[i].data.index != -1)
		{
			cout << vertices[i].data.index << sp;
			while (p != NULL)
			{
				cout << p->adjvex + 1 << sp;
				p = p->nextarc;
			}
			cout << endl;
			// 输出入度
			// cout << endl
			//	 << vertices[i].in << endl;
		}
		else
		{
			cout << "deleted: " << vertices[i].data.classname << " credit:" << vertices[i].data.credit << endl;
		}
	}
}

VNode *ALGraph::Order_fast()
{
	// 副本，便于课程信息更新后重新排序
	VNode *vertices = getVertices();
	// 初始化变量
	int i = 0;
	bool flag = true;
	ArcNode *p;
	stack<VNode> vs;
	stack<ArcNode *> as;
	// 初始化标志位
	while (flag) // 一个循环一个学期，每次都取入度为零的
	{
		flag = false;
		// 遍历所有顶点，入度为0者入栈
		for (i = 0; i < vexnum; i++)
		{
			if (vertices[i].in == 0 && vertices[i].data.index != -1)
			{
				vs.push(vertices[i]);
				// cout << vertices[i].data.index << " " << vertices[i].data.classname << endl;
				vertices[i].in--;
				flag = true;
				p = vertices[i].firstarc;
				as.push(p);
			}
		} // 先取完入度为零的结点，再把邻接点减一
		while (!as.empty())
		{
			p = as.top();
			as.pop();
			while (p != NULL)
			{
				vertices[p->adjvex].in--;
				p = p->nextarc;
			}
		}
	}

	// 判断是否成环
	i = vs.size();
	// cout << "vs.size() = " << i << endl;
	// cout << "vexnum = " << vexnum << endl;
	if (i < vexnum)
	{
		cout << "there is cycle!" << endl;
		return NULL;
	}
	// 初始化结果数组
	VNode *result = new VNode[vexnum];
	// 弹栈，将结果存入数组
	for (i = 0; i < vexnum; i++)
	{
		if (!vs.empty())
		{
			result[i] = vs.top();
			vs.pop();
		}
		else
		{
			cout << "there is something wrong with the stack!" << endl;
		}
	}
	cout << "slow:success!" << endl;
	return result;
}

VNode *ALGraph::Order_slow()
{
	VNode *vertices = getVertices();
	// 定义一个计数变量i
	int i = 0;
	// 定义一个指针p
	ArcNode *p;
	// 定义一个栈vs
	stack<VNode> vs;
	// 定义一个栈as
	stack<ArcNode *> as;
	// 遍历每一个顶点
	for (i = 0; i < vexnum; i++)
	{
		// 如果该顶点的入度为0
		if (vertices[i].in == 0)
		{
			// 将该顶点压入栈vs
			vs.push(vertices[i]);
			// 将该顶点的入度减1
			vertices[i].in--; // in=-1
			// 将该顶点的指针p赋值给p
			p = vertices[i].firstarc;
			// 遍历该顶点的指针p
			// 取完就将邻接点入度减一，课程安排更紧凑
			// 比如，要学物理就要先学高等数学 A->B
			// 如果先将高等数学选了，就可以在同一学期内学物理了
			while (p)
			{
				// 将该顶点的入度减1
				vertices[p->adjvex].in--;
				// 将p的指针赋值给p
				p = p->nextarc;
			}
			// 将i赋值为-1
			i = -1; // 假如有新的课选上了，就重新遍历
		}
	}

	i = vs.size();
	if (i < vexnum)
	{
		cout << "there is cycle!" << endl;
		return NULL;
	}
	VNode *result = new VNode[vexnum];
	for (i = 0; i < vexnum; i++)
	{
		if (!vs.empty())
		{
			result[i] = vs.top();
			vs.pop();
		}
		else
		{
			cout << "there is something with the stack" << endl;
			return NULL;
		}
	}
	cout << "fast:success!" << endl;
	return result;
}

void ALGraph::IndegreeCal()
{
	for (int i = 0; i < vexnum; i++)
	{
		cout << vertices[i].data.index << "入度为" << vertices[i].in << endl;
	}
}

int ALGraph::LocateVex(VNode v)
{
	int flag = -1;
	for (int i = 0; i < vexnum; i++)
	{
		if (vertices[i].data.index == v.data.index &&
			vertices[i].data.classname == v.data.classname &&
			vertices[i].data.credit == v.data.credit)
		{
			flag = i;
			break;
		}
	}
	return flag;
}

void ALGraph::Arrange(VNode *vnode, int choose)
{
	// 声明一个变量vex，指向vnode
	VNode *vex = vnode;
	// 声明一个变量course，用于记录当前课程
	int course;
	// 声明一个变量s，用于记录当前课程的编号
	int s = 0;
	// 声明一个vector，用于记录每个课程的编号
	vector<int> course_list(vexnum, 0);
	// 声明一个vector，用于记录每个学期的课程数
	vector<int> semester_list(limit.term, 0);
	// 遍历vex，打印每个课程的编号和课程信息
	while (s < vexnum)
	{
		cout << s << " " << vex[s].data.classname << endl;
		s++;
	}
	// 声明一个变量arranged_num，用于记录已排列的课程数
	int arranged_num = 0;
	// 声明一个变量credit_sum，用于记录已排列课程的总学分
	int credit_sum = 0;
	// 声明一个变量course_num，用于记录本学期课程数
	int course_num = 0;
	// 声明一个变量per_maxcourse，用于记录每个学期最多可以上多少门课程
	// int per_maxcourse = 0;
	// 声明一个布尔变量flag，用于记录是否找到可以上当前课程的邻接课程
	bool flag = true;
	// 声明一个指针变量q，用于遍历当前学期课程列表
	ArcNode *q;
	// 声明一个队列变量vs，用于存储当前学期课程列表
	queue<VNode> vs;
	/*if (choose == FAST)
	{
		// 如果选择快速学习，则每个学期最多可以上vexnum门课程
		per_maxcourse = limit.max_class;
	}
	else
	{
		// 如果选择正常学习，则每个学期最多可以上vexnum/term门课程
		per_maxcourse = vexnum / limit.term + 1;
		// 如果每个学期可以上vexnum/term门课程，则每个学期最多可以上vexnum门课程
		/*if (vexnum / limit.term < limit.term / 2)
		{
			per_maxcourse = vexnum / limit.term;
		}
		else
		{
			per_maxcourse = vexnum / limit.term + 1;
		}
	}*/
	// 声明一个变量i，用于记录当前学期
	int i;
	// 遍历每个学期，尝试排列当前学期课程
	for (i = 0; i < limit.term; i++)
	{
		// 声明一个vector，用于存储当前学期课程列表
		vector<VNode> this_term_courses(vexnum);
		// 如果已排列的门数等于vexnum，则表示排列完成
		if (arranged_num == vexnum)
		{
			cout << "arranged_num == vexnum" << endl;
			break;
		}
		// 声明一个变量course_num，用于记录本学期课程数
		course_num = 0;
		// 声明一个变量credit_sum，用于记录本学期课程的总学分
		credit_sum = 0;
		// 声明一个布尔变量flag，用于记录本学期是否存在当前考察课程的先修课程
		flag = true;
		cout << endl
			 << "the " << i + 1 << " semester" << endl;
		/*while (flag /*&& course_num < per_maxcourse)
		{
			while (p != NULL && flag)
			{
				for (int j = 0; j < course_num; j++)
				{
					if (p->adjvex == LocateVex(this_term_courses[j]))
					{
						flag = false;
						break;
					}
				}
				p = p->nextarc;
			}*/
		// 遍历当前学期课程列表
		for (course = vexnum - 1; course >= 0; course--)
		{
			// 如果当前课程的编号为0，则表示该课程可以上
			if (course_list[course] == 0)
			{
				// 遍历当前学期课程列表
				for (int j = 0; j < course_num; j++)
				{
					q = this_term_courses[j].firstarc;
					while (q && flag)
					{
						// 如果找到当前课程的先修课程，则将该课程的编号置为1，表示该课程不能上
						if (q->adjvex == LocateVex(vex[course]))
						{
							flag = false;
							break;
						}
						q = q->nextarc;
					}
				}
				// 如果找到当前课程的先修课程，则将该课程的编号置为1，表示该课程不能上
				if (!flag)
				{
					break;
				}
				// 打印当前课程的编号和课程信息
				// cout << "vexnum:" << vexnum << endl
				//	 << "arranged_num: " << arranged_num << endl;
				cout << vex[course].data.classname << endl;
				// 计算本学期课程的总学分
				credit_sum += vex[course].data.credit;
				// 将当前课程添加到当前学期课程列表中
				this_term_courses[course_num] = vex[course];
				// 将当前课程的编号置为1，表示该课程已选上
				course_list[course] = 1;
				// 将当前课程添加到队列中
				vs.push(this_term_courses[course_num]);
				// 打印添加到队列中的课程的编号和课程信息
				// cout << "push into vs" << endl;
				course_num++;
				// 打印已排列的门数
				arranged_num++;
				// 打印本学期课程数
				// cout << "semester_list[" << i << "]"
				//	 << "++" << endl;
				semester_list[i]++;
				// 如果本学期课程的总学分加上准备考察课程的学分大于最大学分，则表示本学期课程已排列完毕
				if (credit_sum + vex[course].data.credit > limit.max_credit)
				{
					course--;
				}
			}
		}
		// 打印本学期课程列表
		// cout << endl
		//	 << "the " << i + 1 << " semester" << endl;
	}

	// 如果已排列的门数不等于vexnum，则表示排列未完成
	if (arranged_num != vexnum)
	{
		cout << "term:" << i << endl;
		cout << "arranged_num:" << arranged_num << endl;
		cout << "false!need more terms to finish the learning!" << endl;
		return;
	}
	cout << "victory!" << endl;

	// printToFile(vs);
	// 打印文件头
	// void printToFile(queue<VNode> vs)
	//{
	VNode n;
	// 打印文件头
	// cout << "vs.size()=" << vs.size() << endl;
	string filename = "course.txt";
	// 声明一个变量semester，用于记录当前学期
	int semester, year;
	semester = 1;
	year = 2023;
	// 打开文件
	ofstream out(filename, ios::out);
	// 打印文件头
	for (; semester <= limit.term; semester++)
	{
		out << endl
			<< "Courses for year " << year << " semester " << semester << ":" << endl
			<< endl;
		cout << endl
			 << "Courses for year " << year << " semester " << semester << ":" << endl;
		// 遍历课程，打印课程信息
		// cout << "semester_list[semester]:" << semester_list[semester-1] << endl;
		for (int k = 0; k < semester_list[semester - 1]; k++)
		{
			n = vs.front();
			vs.pop();
			// 打印当前课程的编号和课程信息
			// cout << "k:" << k << endl;
			cout << n.data.index << " " << n.data.classname << " " << n.data.credit << endl;
			out << n.data.index << " " << n.data.classname << " " << n.data.credit << endl;
		}
	}
	cout << endl
		 << "the plan has been in '" << filename << "'" << endl;
	cout << "you can look on  your own " << endl;
	out.close();
	return;
}