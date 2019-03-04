#pragma once
#include<assert.h>
#include<iostream>
using  namespace std;

const size_t stackIncreament = 20;  // 栈溢出时扩展空间的增量

template<class T>
class SeqStack
{
public:
	SeqStack(size_t sz = 50);
	~SeqStack();
	void Push(const T &x);
	bool Pop(T &x);
	size_t getSize();
	void output();
private:
	T *elements;
	size_t top;
	size_t maxSize;
	void overflowProcess();
};


template<class T>
SeqStack<T>::SeqStack(size_t sz)
{
	elements = new T[sz]();
	top = -1;
	maxSize = sz;
}

template<class T>
SeqStack<T>::~SeqStack()
{
	delete[] elements;
}

template<class T>
inline void SeqStack<T>::Push(const T & x)
{
	if (getSize() >= maxSize) {
		overflowProcess();
	}
	elements[++top] = x;
}

template<class T>
inline bool SeqStack<T>::Pop(T & x)
{
	if (top < 0) {
		return false;
	}
	x = elements[top--];
	return true;
}

template<class T>
inline size_t SeqStack<T>::getSize()
{
	return top + 1;
}

template<class T>
inline void SeqStack<T>::output()
{
	for (size_t i = 0;i<=top;i++) {
		cout << "#" << i + 1 << ":" << elements[i] << endl;
	}
}

template<class T>
inline void SeqStack<T>::overflowProcess()
{
	T *newArray = new T[maxSize + stackIncreament]();
	// 尝试用指针对数组迭代
	for (T *p = elements, *p_end = elements + maxSize, *q = newArray;
		p != p_end; p++) {
		*(q++) = *p;
	}
	maxSize = maxSize + stackIncreament;
	delete[] elements;
	elements = newArray;
}

void SeqStackTest() {
	SeqStack<int> s;
	int v;
	for (int i = 0; i < 50; i++) {
		s.Push(i);
	}
	s.Pop(v);
	cout << "出栈：" << v << endl;
	s.Push(100);
	s.output();
	for (int i = 60; i < 70; i++) {
		s.Push(i);
	}
	s.output();
}
