#pragma once
#include<iostream>
using namespace std;

template<class T>
class SeqQueue
{
public:
	SeqQueue(int sz = 10);
	~SeqQueue();
	bool EnQueue(const T & x);
	bool DeQueue(T & x);
	bool getFront(T & x);
	int getSize();
	void Clear();
	bool IsEmpty();
	bool IsFull();
	void output();
protected:
	int rear, front;  // 队尾总是空的等待数据装入，队头总是等待数据取出
	T *elements;
	int maxSize;
};


template<class T>
SeqQueue<T>::SeqQueue(int sz)
{
	elements = new T[sz]();
	maxSize = sz;
	rear = front = 0;
}

template<class T>
SeqQueue<T>::~SeqQueue()
{
	delete[] elements;
}

template<class T>
inline bool SeqQueue<T>::EnQueue(const T & x)
{
	if (IsFull())
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}

template<class T>
inline bool SeqQueue<T>::DeQueue(T & x)
{
	if (IsEmpty())
		return false;
	x = elements[front];
	front = (front + 1) % maxSize;
	return true;
}

template<class T>
inline bool SeqQueue<T>::getFront(T & x)
{
	if(IsEmpty())
		return false;
	x = elements[front];
	return true;
}

template<class T>
inline int SeqQueue<T>::getSize()
{
	return (rear - front + maxSize) % maxSize;  // awesome!
}

template<class T>
inline void SeqQueue<T>::Clear()
{
	front = rear = 0;
}

template<class T>
inline bool SeqQueue<T>::IsEmpty()
{
	return (rear == front) ? true : false;
}

template<class T>
inline bool SeqQueue<T>::IsFull()
{
	// 队列满意味着存了maxSzie-1个元素，少了的一个用来判断队列是否满
	return (rear + 1) % maxSize == front ? true : false;
}

template<class T>
inline void SeqQueue<T>::output()
{
	for (int i = front; i != rear; ++i) {
		cout << elements[i] << endl;
	}
}

void SeqQueueTest() {
	SeqQueue<int> s(100);
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