#include <iostream>
#include <ctime>
#include <string>
#include "Queue.h"
using namespace std;

template <class T>
LinkQueue<T>::~LinkQueue()
{
	//~ 销毁队列时，将队列中的元素全部释放
	while (front != NULL)
	{
		rear = front->next;
		delete front;
		front = rear;
	}
}

template <class T>
bool LinkQueue<T>::empty()
{
	//~ 判断队列是否为空
	if (front == rear)
	{
		return true;
	}
	return false;
}

template <class T>
bool LinkQueue<T>::push(T e)
{
	//~ 向队列中添加元素
	if (empty())
	{
		rear = new LinkNode<T>();
		rear->data = e;
		front = rear;
		rear = new LinkNode<T>();
		front->next = rear;
		return true;
	}
	rear->data = e;
	LinkNode<T> *p = rear;
	rear = new LinkNode<T>();
	p->next = rear;
	return true;
}

template <class T>
bool LinkQueue<T>::pop(T &e)
{
	//~ 从队列中取出元素
	if (empty())
	{
		return false;
	}
	LinkNode<T> *p;
	p = front;
	e = front->data;
	front = front->next;
	delete p;
	return true;
}

template <class T>
bool LinkQueue<T>::gethead(T &e)
{
	//~ 获取队列中的第一个元素
	if (empty())
	{
		return false;
	}
	e = front->data;
	return true;
}

bool Hospital::timer()
{
	//~ 判断是否在就诊时间内
	time_t now = time(0);
	tm ntime;
	gmtime_s(&ntime, &now);
	if (ntime.tm_hour >= 20 || ntime.tm_hour <= 8)
	{
		cout << "医生也需要休息哦!" << endl;
		cout << "就诊时间:上午八点--十二点" << endl;
		cout << "         下午一点到下午八点" << endl;
		return false;
	}
	return true;
}

bool Hospital::enQueue(LinkQueue<string> *p)
{
	//~ 排队
	if (!timer())
	{
		cout << "请在就诊时间内排队" << endl;
		return false;
	}
	string name;
	cout << "请输入你的姓名:";
	cin >> name;
	if (p->push(name))
	{
		cout << "排队成功！请耐心等待" << endl;
		return true;
	}
	cout << "系统繁忙,请稍后再试(如果多次失败，请询问护士)" << endl;
	return false;
}

bool Hospital::visit(LinkQueue<string> *p)
{
	//~ 就诊
	string name;
	if (!timer())
	{
		cout << "请下午一点或明天再来" << endl;
		return false;
	}
	if (p->pop(name))
	{
		cout << name << "患者请进室就诊" << endl;
		if (p->gethead(name))
		{
			cout << name << "患者请准备" << endl;
		}
		return true;
	}
	cout << "空闲" << endl;
	return true;
}

int Hospital::total(LinkQueue<string> *p)
{
	//~ 计算队列中的元素个数
	int i = 0;
	LinkNode<string> *a = p->front;
	while (a != p->rear)
	{
		a = a->next;
		i++;
	}
	return i;
}