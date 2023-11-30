#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <string>
using namespace std;

template <typename T>
struct LinkNode
{
	T data;
	LinkNode *next;
	LinkNode() : next(NULL) {}
	LinkNode(T d) : data(d), next(NULL) {}
};

template <typename T>
class LinkQueue
{
public:
	LinkNode<T> *front;
	LinkNode<T> *rear;
	LinkQueue() : front(NULL), rear(NULL) {}
	~LinkQueue();
	// 检查队列是否为空
	bool empty();
	// 将元素e入队
	bool push(T e);
	// 将队列头部的元素赋值给e，并将其出队
	bool pop(T &e);
	// 将队列头部的元素赋值给e，不将其出队
	bool gethead(T &e);
};

class Hospital
{
public:
	// 将p入队
	bool enQueue(LinkQueue<string> *p);
	// 访问p中的病人
	bool visit(LinkQueue<string> *p);
	// 检查时间
	bool timer();
	// 计算队列中的病人总数
	int total(LinkQueue<string> *p);
};

#endif