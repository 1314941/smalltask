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
				cout << "���ظ�" << endl;
			}
			else
			{
				a->nextarc = vertices[arcList[i].From.data.index - 1].firstarc; // ͷ�巨
				vertices[arcList[i].From.data.index - 1].firstarc = a;
				vertices[arcList[i].From.data.index - 1].in++; // ���+1
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
			p->nextarc = a;								   // β�巨 ����
			vertices[arcList[i].From.data.index - 1].in++; // ���+1
			*/
			a->nextarc = vertices[arcList[i].From.data.index - 1].firstarc; // ͷ�巨
			vertices[arcList[i].From.data.index - 1].firstarc = a;
		}
		vertices[arcList[i].To.data.index - 1].in++; // ���+1
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
	// ����CreatGraph�ĺ�벿��
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
			a->nextarc = vertices[arcList[i].From.data.index - 1].firstarc; // ͷ�巨
			vertices[arcList[i].From.data.index - 1].firstarc = a;
		}
		vertices[arcList[i].From.data.index - 1].in++; // ���+1
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
			// ������
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
	// ���������ڿγ���Ϣ���º���������
	VNode *vertices = getVertices();
	// ��ʼ������
	int i = 0;
	bool flag = true;
	ArcNode *p;
	stack<VNode> vs;
	stack<ArcNode *> as;
	// ��ʼ����־λ
	while (flag) // һ��ѭ��һ��ѧ�ڣ�ÿ�ζ�ȡ���Ϊ���
	{
		flag = false;
		// �������ж��㣬���Ϊ0����ջ
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
		} // ��ȡ�����Ϊ��Ľ�㣬�ٰ��ڽӵ��һ
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

	// �ж��Ƿ�ɻ�
	i = vs.size();
	// cout << "vs.size() = " << i << endl;
	// cout << "vexnum = " << vexnum << endl;
	if (i < vexnum)
	{
		cout << "there is cycle!" << endl;
		return NULL;
	}
	// ��ʼ���������
	VNode *result = new VNode[vexnum];
	// ��ջ���������������
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
	// ����һ����������i
	int i = 0;
	// ����һ��ָ��p
	ArcNode *p;
	// ����һ��ջvs
	stack<VNode> vs;
	// ����һ��ջas
	stack<ArcNode *> as;
	// ����ÿһ������
	for (i = 0; i < vexnum; i++)
	{
		// ����ö�������Ϊ0
		if (vertices[i].in == 0)
		{
			// ���ö���ѹ��ջvs
			vs.push(vertices[i]);
			// ���ö������ȼ�1
			vertices[i].in--; // in=-1
			// ���ö����ָ��p��ֵ��p
			p = vertices[i].firstarc;
			// �����ö����ָ��p
			// ȡ��ͽ��ڽӵ���ȼ�һ���γ̰��Ÿ�����
			// ���磬Ҫѧ�����Ҫ��ѧ�ߵ���ѧ A->B
			// ����Ƚ��ߵ���ѧѡ�ˣ��Ϳ�����ͬһѧ����ѧ������
			while (p)
			{
				// ���ö������ȼ�1
				vertices[p->adjvex].in--;
				// ��p��ָ�븳ֵ��p
				p = p->nextarc;
			}
			// ��i��ֵΪ-1
			i = -1; // �������µĿ�ѡ���ˣ������±���
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
		cout << vertices[i].data.index << "���Ϊ" << vertices[i].in << endl;
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
	// ����һ������vex��ָ��vnode
	VNode *vex = vnode;
	// ����һ������course�����ڼ�¼��ǰ�γ�
	int course;
	// ����һ������s�����ڼ�¼��ǰ�γ̵ı��
	int s = 0;
	// ����һ��vector�����ڼ�¼ÿ���γ̵ı��
	vector<int> course_list(vexnum, 0);
	// ����һ��vector�����ڼ�¼ÿ��ѧ�ڵĿγ���
	vector<int> semester_list(limit.term, 0);
	// ����vex����ӡÿ���γ̵ı�źͿγ���Ϣ
	while (s < vexnum)
	{
		cout << s << " " << vex[s].data.classname << endl;
		s++;
	}
	// ����һ������arranged_num�����ڼ�¼�����еĿγ���
	int arranged_num = 0;
	// ����һ������credit_sum�����ڼ�¼�����пγ̵���ѧ��
	int credit_sum = 0;
	// ����һ������course_num�����ڼ�¼��ѧ�ڿγ���
	int course_num = 0;
	// ����һ������per_maxcourse�����ڼ�¼ÿ��ѧ���������϶����ſγ�
	// int per_maxcourse = 0;
	// ����һ����������flag�����ڼ�¼�Ƿ��ҵ������ϵ�ǰ�γ̵��ڽӿγ�
	bool flag = true;
	// ����һ��ָ�����q�����ڱ�����ǰѧ�ڿγ��б�
	ArcNode *q;
	// ����һ�����б���vs�����ڴ洢��ǰѧ�ڿγ��б�
	queue<VNode> vs;
	/*if (choose == FAST)
	{
		// ���ѡ�����ѧϰ����ÿ��ѧ����������vexnum�ſγ�
		per_maxcourse = limit.max_class;
	}
	else
	{
		// ���ѡ������ѧϰ����ÿ��ѧ����������vexnum/term�ſγ�
		per_maxcourse = vexnum / limit.term + 1;
		// ���ÿ��ѧ�ڿ�����vexnum/term�ſγ̣���ÿ��ѧ����������vexnum�ſγ�
		/*if (vexnum / limit.term < limit.term / 2)
		{
			per_maxcourse = vexnum / limit.term;
		}
		else
		{
			per_maxcourse = vexnum / limit.term + 1;
		}
	}*/
	// ����һ������i�����ڼ�¼��ǰѧ��
	int i;
	// ����ÿ��ѧ�ڣ��������е�ǰѧ�ڿγ�
	for (i = 0; i < limit.term; i++)
	{
		// ����һ��vector�����ڴ洢��ǰѧ�ڿγ��б�
		vector<VNode> this_term_courses(vexnum);
		// ��������е���������vexnum�����ʾ�������
		if (arranged_num == vexnum)
		{
			cout << "arranged_num == vexnum" << endl;
			break;
		}
		// ����һ������course_num�����ڼ�¼��ѧ�ڿγ���
		course_num = 0;
		// ����һ������credit_sum�����ڼ�¼��ѧ�ڿγ̵���ѧ��
		credit_sum = 0;
		// ����һ����������flag�����ڼ�¼��ѧ���Ƿ���ڵ�ǰ����γ̵����޿γ�
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
		// ������ǰѧ�ڿγ��б�
		for (course = vexnum - 1; course >= 0; course--)
		{
			// �����ǰ�γ̵ı��Ϊ0�����ʾ�ÿγ̿�����
			if (course_list[course] == 0)
			{
				// ������ǰѧ�ڿγ��б�
				for (int j = 0; j < course_num; j++)
				{
					q = this_term_courses[j].firstarc;
					while (q && flag)
					{
						// ����ҵ���ǰ�γ̵����޿γ̣��򽫸ÿγ̵ı����Ϊ1����ʾ�ÿγ̲�����
						if (q->adjvex == LocateVex(vex[course]))
						{
							flag = false;
							break;
						}
						q = q->nextarc;
					}
				}
				// ����ҵ���ǰ�γ̵����޿γ̣��򽫸ÿγ̵ı����Ϊ1����ʾ�ÿγ̲�����
				if (!flag)
				{
					break;
				}
				// ��ӡ��ǰ�γ̵ı�źͿγ���Ϣ
				// cout << "vexnum:" << vexnum << endl
				//	 << "arranged_num: " << arranged_num << endl;
				cout << vex[course].data.classname << endl;
				// ���㱾ѧ�ڿγ̵���ѧ��
				credit_sum += vex[course].data.credit;
				// ����ǰ�γ���ӵ���ǰѧ�ڿγ��б���
				this_term_courses[course_num] = vex[course];
				// ����ǰ�γ̵ı����Ϊ1����ʾ�ÿγ���ѡ��
				course_list[course] = 1;
				// ����ǰ�γ���ӵ�������
				vs.push(this_term_courses[course_num]);
				// ��ӡ��ӵ������еĿγ̵ı�źͿγ���Ϣ
				// cout << "push into vs" << endl;
				course_num++;
				// ��ӡ�����е�����
				arranged_num++;
				// ��ӡ��ѧ�ڿγ���
				// cout << "semester_list[" << i << "]"
				//	 << "++" << endl;
				semester_list[i]++;
				// �����ѧ�ڿγ̵���ѧ�ּ���׼������γ̵�ѧ�ִ������ѧ�֣����ʾ��ѧ�ڿγ����������
				if (credit_sum + vex[course].data.credit > limit.max_credit)
				{
					course--;
				}
			}
		}
		// ��ӡ��ѧ�ڿγ��б�
		// cout << endl
		//	 << "the " << i + 1 << " semester" << endl;
	}

	// ��������е�����������vexnum�����ʾ����δ���
	if (arranged_num != vexnum)
	{
		cout << "term:" << i << endl;
		cout << "arranged_num:" << arranged_num << endl;
		cout << "false!need more terms to finish the learning!" << endl;
		return;
	}
	cout << "victory!" << endl;

	// printToFile(vs);
	// ��ӡ�ļ�ͷ
	// void printToFile(queue<VNode> vs)
	//{
	VNode n;
	// ��ӡ�ļ�ͷ
	// cout << "vs.size()=" << vs.size() << endl;
	string filename = "course.txt";
	// ����һ������semester�����ڼ�¼��ǰѧ��
	int semester, year;
	semester = 1;
	year = 2023;
	// ���ļ�
	ofstream out(filename, ios::out);
	// ��ӡ�ļ�ͷ
	for (; semester <= limit.term; semester++)
	{
		out << endl
			<< "Courses for year " << year << " semester " << semester << ":" << endl
			<< endl;
		cout << endl
			 << "Courses for year " << year << " semester " << semester << ":" << endl;
		// �����γ̣���ӡ�γ���Ϣ
		// cout << "semester_list[semester]:" << semester_list[semester-1] << endl;
		for (int k = 0; k < semester_list[semester - 1]; k++)
		{
			n = vs.front();
			vs.pop();
			// ��ӡ��ǰ�γ̵ı�źͿγ���Ϣ
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