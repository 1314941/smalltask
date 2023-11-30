#pragma once
#ifndef SQQUEUE_H
#define SQQUEUE_H
#include<string>
using namespace std;
const int MaxSize = 100;

template<typename T>
class SqQueue
{
public:
	T* data;
	int front, rear;
	SqQueue()
	{
		data = new T[MaxSize];
		front = rear = 1;
	}
	~SqQueue()
	{
		delete[] data;
	}
	bool empty();       //¶Ó¿Õ
	bool full();       //¶ÓÂú
	bool push(T e);
	bool pop(T& e);
	bool gethead(T& e);
};


class Hospital
{
public:
	Hospital(){}
	~Hospital(){}
	bool enqueue(SqQueue<string>* p);
	bool jiuzhen(SqQueue<string>* p);
	int total(SqQueue<string>* p);
	bool timer();
};


#endif