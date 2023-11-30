#include <iostream>
#include <ctime>
#include <string>
#include "Queue.h"
using namespace std;

template <class T>
LinkQueue<T>::~LinkQueue()
{
	//~ ���ٶ���ʱ���������е�Ԫ��ȫ���ͷ�
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
	//~ �ж϶����Ƿ�Ϊ��
	if (front == rear)
	{
		return true;
	}
	return false;
}

template <class T>
bool LinkQueue<T>::push(T e)
{
	//~ ����������Ԫ��
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
	//~ �Ӷ�����ȡ��Ԫ��
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
	//~ ��ȡ�����еĵ�һ��Ԫ��
	if (empty())
	{
		return false;
	}
	e = front->data;
	return true;
}

bool Hospital::timer()
{
	//~ �ж��Ƿ��ھ���ʱ����
	time_t now = time(0);
	tm ntime;
	gmtime_s(&ntime, &now);
	if (ntime.tm_hour >= 20 || ntime.tm_hour <= 8)
	{
		cout << "ҽ��Ҳ��Ҫ��ϢŶ!" << endl;
		cout << "����ʱ��:����˵�--ʮ����" << endl;
		cout << "         ����һ�㵽����˵�" << endl;
		return false;
	}
	return true;
}

bool Hospital::enQueue(LinkQueue<string> *p)
{
	//~ �Ŷ�
	if (!timer())
	{
		cout << "���ھ���ʱ�����Ŷ�" << endl;
		return false;
	}
	string name;
	cout << "�������������:";
	cin >> name;
	if (p->push(name))
	{
		cout << "�Ŷӳɹ��������ĵȴ�" << endl;
		return true;
	}
	cout << "ϵͳ��æ,���Ժ�����(������ʧ�ܣ���ѯ�ʻ�ʿ)" << endl;
	return false;
}

bool Hospital::visit(LinkQueue<string> *p)
{
	//~ ����
	string name;
	if (!timer())
	{
		cout << "������һ�����������" << endl;
		return false;
	}
	if (p->pop(name))
	{
		cout << name << "��������Ҿ���" << endl;
		if (p->gethead(name))
		{
			cout << name << "������׼��" << endl;
		}
		return true;
	}
	cout << "����" << endl;
	return true;
}

int Hospital::total(LinkQueue<string> *p)
{
	//~ ��������е�Ԫ�ظ���
	int i = 0;
	LinkNode<string> *a = p->front;
	while (a != p->rear)
	{
		a = a->next;
		i++;
	}
	return i;
}