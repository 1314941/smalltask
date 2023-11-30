#include<iostream>
#include"SqQueue.h"
#include<string>
using namespace std;

template<typename T>
bool SqQueue<T>::empty()
{
	if (front == rear) {
		return true;
	}
	return false;
}

template<typename T>
bool SqQueue<T>::full()
{
	if ((rear + 1) % MaxSize == front) {
		return true;
	}
	return false;
}


template<typename T>
bool SqQueue<T>::push(T e)
{
	if (full()) {
		return false;
	}
	if (empty()) {
		front=rear=(rear+1)%MaxSize;
		data[rear] = e;
		rear = (rear + 1) % MaxSize;
		return true;
	}
	data[rear] = e;
	rear = (rear + 1) % MaxSize;
	return true;
}  


template<typename T>
bool SqQueue<T>::pop(T& e)
{
	if (empty()) {
		return false;
	}
	e = data[front];
	front = (front + 1) % MaxSize;
	return true;
}

template<typename T>
bool SqQueue<T>::gethead(T& e)
{
	if (empty()) {
		return false;
	}
	e = data[front];
	return true;

}
 

bool Hospital::enqueue(SqQueue<string>* p)
{
	string name;
	cout << "�������������:";
	cin >> name;
	if (p->push(name)) {
		cout << "�Ŷӳɹ�,���Ե�Ƭ��"<<endl;
		return true;
	}
	return false;
}



bool Hospital::jiuzhen(SqQueue<string>* p)
{
	string name;
	if (p->pop(name)) {
		cout <<name<< "��������Ҿ���" << endl;
		if (p->gethead(name)) {
			cout << name << "������׼��" << endl;
		}
		return true;
	}
	cout << "ϵͳ��æ,���Ժ�����" << endl;
	return false;
}


int Hospital::total(SqQueue<string>* p)
{
	int f, r,count=0;
	if (p->empty()) {
		return 0;
	}
	f = p->front;
	r = p->rear;
	count = (r - f + MaxSize) % MaxSize;
	return count;
}


bool Hospital::timer()
{
	time_t now = time(0);
	tm ntime;
	gmtime_s(&ntime, &now);
	if (ntime.tm_hour >= 20 || ntime.tm_hour <= 8) {
		cout << "ҽ��Ҳ��Ҫ��ϢŶ!" << endl;
		cout << "����ʱ��:����˵�--ʮ����" << endl;
		cout << "         ����һ�㵽����˵�" << endl;
		return false;
	}
	return true;
}

