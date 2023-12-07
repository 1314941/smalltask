#include <iostream>
#include "LinkList.h"
using namespace std;

template <class T>
bool LinkList<T>::empty()
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
LinkList<T>::LinkList()
{
	head = new LinkNode<T>;
}

template <class T>
LinkList<T>::LinkList(T a[], int n)
{
	LinkNode<T> *p, *q;
	head = new LinkNode<T>;
	p = head;
	for (int i = 0; i < n; i++)
	{
		q = new LinkNode<T>(a[i]);
		p->next = q;
		p = q;
	}
}

template <class T>
LinkList<T>::~LinkList()
{
	if (empty())
	{
	}
	else
	{
		LinkNode<T> *p, *q;
		p = head;
		q = p->next;
		if (q == NULL)
		{
		}
		else
		{
			p = q;
			q = q->next;
			head->next = NULL;
			while (q != NULL)
			{
				free(p);
				p = q;
				q = p->next;
			}
			free(p);
		}
	}
}

template <class T>
int LinkList<T>::Locate(T x)
{
	if (empty())
	{
		throw "�ձ�!";
	}
	int i = 0;
	LinkNode<T> *p = head;
	while (p != NULL)
	{
		if (p->data.number == x.number)
		{
			return i;
		}
		p = p->next;
		i++;
	}
	if (p == NULL)
	{
		cout << "�Ҳ������ҵ�ѧ����Ϣ!";
		return 0;
	}
}

template <class T>
void LinkList<T>::Insert(int i, T x) // ����
{
	if (empty())
	{
		cout << "�ձ�";
		return;
	}
	LinkNode<T> *p = head;
	LinkNode<T> *q = head->next;
	int j = 0;
	LinkNode<T> *n = new LinkNode<T>(x);
	while (j < (i - 1) && q != NULL)
	{
		p = q;
		q = q->next;
		j++;
	}
	if (j == (i - 1))
	{
		p->next = n;
		n->next = q;
		cout << "��ӳɹ���" << endl;
		return;
	}
	cout << "λ�ô���";
	return;
}

template <class T>
int LinkList<T>::Length()
{
	if (empty())
	{
		cout << "�ձ�!";
		return 0;
	}
	int i = 0;
	LinkNode<T> *p = head->next;
	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}

template <class T>
T LinkList<T>::Delete(int i) // ɾ��
{
	if (empty())
	{
		throw "�ձ�";
	}
	LinkNode<T> *p = head;
	LinkNode<T> *q = head->next;
	int j = 0;
	while (j < (i - 1) && q != NULL)
	{
		p = q;
		q = q->next;
		j++;
	}
	if (j == (i - 1))
	{
		if (q == NULL)
		{
		}
		else
		{
			p->next = q->next;
			cout << "ɾ���ɹ���" << endl;
			return q->data;
		}
	}
	throw "λ�ô���!";
}

template <class T>
void LinkList<T>::PrintList()
{
	if (empty())
	{
		cout << "�ձ�!" << endl;
		return;
	}
	LinkNode<T> *p = head->next;
	while (p != NULL)
	{
		cout << p->data.number << "\t" << p->data.name << "\t" << p->data.score << "\t" << endl;
		p = p->next;
	}
	return;
}

template <class T>
T LinkList<T>::Get(int i)
{
	if (empty())
	{
		throw "�ձ�!";
	}
	int j = 1;
	LinkNode<T> *p = head->next;
	while (p != NULL)
	{
		if (j == i)
		{
			return p->data;
		}
		p = p->next;
		j++;
	}
	throw "λ�ô���";
}

template <class T>
int LinkList<T>::Max()
{
	if (empty())
	{
		cout << "�ձ�!";
		return -1;
	}
	LinkNode<T> *p = head->next;
	if (p)
	{
		int max = p->data.score;
		int temp = 1, i = 1;
		while (p != NULL)
		{
			if (p->data.score > max)
			{
				max = p->data.score;
				temp = i;
			}
			p = p->next;
			i++;
		}
		return temp;
	}
	else
	{
		cout << "ֻ��ͷ��㣡";
		return -1;
	}
}

template <class T>
void LinkList<T>::Sort()
{
	int max = Max();
	if (max == -1)
	{
		cout << "�޷�����";
		return;
	}
	int le = Length();
	LinkNode<T> *p = new LinkNode<T>[le];
	LinkNode<T> *h = p;
	for (int i = 1; i <= le; i++)
	{
		max = Max();
		p->data = Delete(max);
		p++;
	}
	p = h;
	for (int i = 1; i <= le; i++)
	{
		Insert(i, p->data);
		p++;
	}
}