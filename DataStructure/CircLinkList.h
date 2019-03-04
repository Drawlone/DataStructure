#pragma once
#include<iostream>

template<class T>
struct CircLinkNode {
	T data;
	CircLinkNode<T> *link;
	CircLinkNode(CircLinkNode<T> * next = NULL) :link(next) {}
	CircLinkNode(T d, CircLinkNode<T> *next = NULL) :data(d), link(next) {}
};

template<class T>
class CircLinkList
{
public:
	CircLinkList();
	~CircLinkList();
	int Length()const;
	bool IsEmpty();
	CircLinkNode<T> * getHead()const { return first; }
	CircLinkNode<T> * Locate(int i);
	T * getData(int i);
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	void insert(T& x);
	void output();
private:
	CircLinkNode<T> *first, *last;
};

void Josephus(int n, int m);

void Josephus2(int n, int s, int m);

