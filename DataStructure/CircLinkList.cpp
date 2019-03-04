#include "pch.h"
#include "CircLinkList.h"
using namespace std;


template<class T>
CircLinkList<T>::CircLinkList()
{
	first = new CircLinkNode<T>;
	first->link = first;
	last = first;
}

template<class T>
CircLinkList<T>::~CircLinkList()
{

}

template<class T>
CircLinkNode<T>* CircLinkList<T>::Locate(int i)
{
	/* i可以超过元素个数 */
	CircLinkNode<T> * current = first;
	int j = 0;
	while (j < i) {
		current = current->link;
		j++;
	}
	return current;
}

template<class T>
bool CircLinkList<T>::Insert(int i, T & x)
{
	CircLinkNode<T> * newNode = new CircLinkNode(x);
	CircLinkNode<T> * current = Locate(i);
	if (current == last) {
		current->link = newNode;
		newNode->link = first;
		last = newNode;
	}
	else {
		newNode->link = current->link;
		current->link = newNode;
	}
	return true;
}

template<class T>
bool CircLinkList<T>::Remove(int i, T & x)
{
	CircLinkNode<T> * p = Locate(i - 1);
	CircLinkNode<T> * del = p->link;
	p->link = del->link;
	x = del->data;
	delete del;
	return true;
}

template<class T>
void CircLinkList<T>::insert(T & x)
{
	CircLinkNode<T> * newNode = new CircLinkNode<T>(x);
	last->link = newNode;
	newNode->link = first;
	last = newNode;
}

template<class T>
void CircLinkList<T>::output()
{
	CircLinkNode<T> * current = first->link;
	while (current != first) {
		cout << current->data << " ";
		current = current->link;
	}
}

void Josephus(int n, int m)
{
	CircLinkList<int> Js;
	for (int i = 1; i <= n; i++) Js.insert(i);
	CircLinkNode<int> * p = Js.Locate(1), *pre = Js.getHead();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 1; j < m; j++) {
			pre = p;
			p = p->link;
			if (p == Js.getHead()) {
				pre = p;
				p = p->link;
			}
		}
		cout << "出列的人是" << p->data << endl;
		pre->link = p->link;
		delete p;
		p = pre->link;
		if (p == Js.getHead()) {
			pre = p;
			p = p->link;
		}
	}
	cout << "获胜者是" << p->data << endl;
}

void Josephus2(int n, int s, int m)
{
	CircLinkList<int> Js;
	for (int i = 1; i <= n; i++) Js.insert(i);
	CircLinkNode<int> * p = Js.Locate(s), *pre = Js.Locate(s - 1);
	for (int i = 0; i < n - 1; i++) {
		for (int j = 1; j < m; j++) {
			pre = p;
			p = p->link;
			if (p == Js.getHead()) {
				pre = p;
				p = p->link;
			}
		}
		cout << "出列的人是" << p->data << endl;
		pre->link = p->link;
		delete p;
		p = pre->link;
		if (p == Js.getHead()) {
			pre = p;
			p = p->link;
		}
	}
	cout << "获胜者是" << p->data << endl;
}
