#include "pch.h"
#include "LinkList.h"
using namespace std;

template<class T>
LinkList<T>::LinkList()
{
	first = new LinkNode<T>;
}

template<class T>
LinkList<T>::LinkList(LinkList<T>& L) {
	T value;
	LinkNode<T> *srcptr, *desptr;
	srcptr = L.getHead();
	desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;
		desptr->link = new LinkNode<T>(value);
		desptr = desptr->link;
		srcptr = srcptr->link;
	}
	desptr->link = NULL;
}

template<class T>
LinkList<T>::~LinkList()
{
	makeEmpty();
}

template<class T>
void LinkList<T>::makeEmpty() {
	LinkNode<T> *ptr = first->link, *p;
	while (ptr != NULL) {
		p = ptr->link;
		delete ptr;
		ptr = p;
	}
}

template<class T>
int LinkList<T>::Length()const {
	int count = 0;
	LinkNode<T> *p = first;
	while (p->link != NULL) {
		count++;
		p = p->link;
	}
	return count;
}

template<class T>
LinkNode<T> * LinkList<T>::Search(T x) {
	LinkNode *p = first->link;
	while (p != NULL && x != p->data)
		p = p->link;
	if (p != NULL)
		return p;
	else return NULL;
}

template<class T>
LinkNode<T> * LinkList<T>::Locate(int i) {
	if (i < 0)
		return false;
	int count = 0;
	LinkNode<T> *p = first;
	while (p != NULL && (count++) < i)
		p = p->link;
	if (p != NULL)
		return p;
	else return NULL;
}

template<class T>
bool LinkList<T>::getData(int i, T& x)const {
	if (i <= 0)
		return NULL;
	LinkNode<T> *p = Locate<T>(i);
	if (p != NULL) {
		x = p->data;
		return true;
	}
	else return false;
}

template<class T>
bool LinkList<T>::setData(int i, T& x) {
	if (i <= 0)
		return false;
	LinkNode<T> *p = Locate(i);
	if (p != NULL) {
		p->data = x;
		return true;
	}
	else return false;
}

template<class T>
bool LinkList<T>::Insert(int i, T& x) {
	LinkNode<T> *p = Locate(i);
	LinkNode<T> *desptr = new LinkNode<T>(x);
	if (Locate(i) == NULL || desptr == NULL)
		return false;
	desptr->link = p->link;
	p->link = desptr;
	return true;
}

template<class T>
bool LinkList<T>::Remove(int i, T& x) {
	LinkNode<T> *p = Locate(i - 1), *s;
	if (p == NULL || p->link == NULL)
		return false;
	s = p->link;
	x = s->data;
	p->link = s->link;
	delete s;
	return true;
}

template<class T>
void LinkList<T>::output() {
	LinkNode<T> *p = first->link;
	while (p != NULL) {
		cout << p->data << endl;
		p = p->link;
	}
}

template<class T>
LinkList<T>& LinkList<T>::operator=(LinkList<T>& L) {
	T value;
	LinkNode<T> *srcptr, *desptr;
	srcptr = L.getHead();
	desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;
		desptr->link = new LinkNode<T>(value);
		desptr = desptr->link;
		srcptr = srcptr->link;
	}
	desptr->link = NULL;
	return *this;
}

template<class T>
void LinkList<T>::inputFront(T*a, int length) {
	makeEmpty();
	LinkNode<T> *s;
	for (int i = 0; i < length; i++) {
		s = new LinkNode<T>(a[i]);
		if (s == NULL) {
			cerr << "ÄÚ´æ·ÖÅä´íÎó£¡" << endl;
			exit(1);
		}
		s->link = first->link;
		first->link = s;
	}
}

template<class T>
void LinkList<T>::inputRear(T*a, int length) {
	makeEmpty();
	LinkNode<T> *p = first, *s;
	for (int i = 0; i < length; i++) {
		s = new LinkNode<T>(a[i]);
		if (s == NULL) {
			cerr << "ÄÚ´æ·ÖÅä´íÎó£¡" << endl;
			exit(1);
		}
		p->link = s;
		p = s;
	}
	p->link = NULL;
}
