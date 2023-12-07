#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H
#include <string>
using namespace std;

template <class T>
struct LinkNode
{
	T data;
	LinkNode *next;
	LinkNode() : next(NULL) {}
	LinkNode(T d) : data(d), next(NULL) {}
};

template <class T>
class LinkList
{
public:
	LinkList();
	LinkList(T a[], int n);
	~LinkList();
	int Locate(T x);
	void Insert(int i, T x);
	T Delete(int i);
	T Get(int i);
	void PrintList();
	bool empty();
	int Length();
	void Sort(); // ≈≈–Ú
	int Max();

private:
	LinkNode<T> *head;
};

#endif