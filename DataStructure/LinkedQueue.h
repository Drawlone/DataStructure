#pragma once
#include<iostream>
#include"LinkList.h"
using namespace std;

template < class T>
class LinkedQueue {
public:
	LinkedQueue() :rear(NULL), front(NULL) {}
	~LinkedQueue() { makeEmpty(); }
	bool EnQueue(const T& x);//将x加到队列
	bool DeQueue(T& x);//取出队头元素
	void makeEmpty();//置空队列
	bool IsEmpty()const { return (front == NULL) ? true : false; }//判空
	void output();
private:
	LinkNode<T> *front, *rear;
};

template<class T>
inline void LinkedQueue<T>::makeEmpty() {
	LinkNode<T> *p;
	//逐个删除队列中节点
	while (front != NULL) {
		p = front;
		front = front->link;
		delete p;
	}
}

template<class T>
inline void LinkedQueue<T>::output()
{
	LinkNode<T> *p = front;
	while (p != NULL) {
		cout << p->data << endl;
		p = p->link;
	}
}

template<class T>
inline bool LinkedQueue<T>::EnQueue(const T& x) {
	if (front == NULL) {
		front = rear = new LinkNode<T>(x);
		if (front == NULL)return false;
	}
	else {
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL)return false;
		rear = rear->link;
	}
	return true;
}

template<class T>
inline bool LinkedQueue<T>::DeQueue(T& x) {
	if (IsEmpty())return false;
	LinkNode<T> *p = front;
	x = front->data;
	front = front->link;
	delete p;
	return false;
}

void LinkedQueueTest() {
	LinkedQueue<int> s;
	int v;
	for (int i = 0; i < 50; i++) {
		s.EnQueue(i);
	}
	s.DeQueue(v);
	cout << "出栈：" << v << endl;
	s.EnQueue(100);
	s.output();
	for (int i = 0; i < 10; i++) {
		s.DeQueue(v);
		cout << "出栈：" << v << endl;
	}
	s.output();
}
