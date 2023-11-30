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
	cout << "请输入你的名字:";
	cin >> name;
	if (p->push(name)) {
		cout << "排队成功,请稍等片刻"<<endl;
		return true;
	}
	return false;
}



bool Hospital::jiuzhen(SqQueue<string>* p)
{
	string name;
	if (p->pop(name)) {
		cout <<name<< "患者请进室就诊" << endl;
		if (p->gethead(name)) {
			cout << name << "患者请准备" << endl;
		}
		return true;
	}
	cout << "系统繁忙,请稍后再试" << endl;
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
		cout << "医生也需要休息哦!" << endl;
		cout << "就诊时间:上午八点--十二点" << endl;
		cout << "         下午一点到下午八点" << endl;
		return false;
	}
	return true;
}

