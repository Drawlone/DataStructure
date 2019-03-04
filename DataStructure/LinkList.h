#pragma once

template<class T>
struct LinkNode {
	T data;
	LinkNode<T> * link;
	LinkNode(LinkNode<T> *ptr = NULL) {
		link = ptr;
	}
	LinkNode(const T& item, LinkNode *ptr = NULL) {
		data = item;
		link = ptr;
	}
};

template<class T>
class LinkList
{
public:
	LinkList();
	LinkList(LinkList<T>& L);
	~LinkList();
	void makeEmpty();//将链表置为空表
	int Length()const;//计算链表长度
	LinkNode<T> *getHead()const { return first; }//返回头节点地址first
	LinkNode<T> *Search(T x);//寻找值为x的节点，返回其地址
	LinkNode<T> *Locate(int i);//定位第i个节点，返回地址
	bool getData(int i, T& x)const;//取出第i个元素的值
	bool setData(int i, T& x);//用x修改第i个元素的值
	bool Insert(int i, T& x);//在第i个元素后插入x
	bool Remove(int i, T& x);//删除第i个元素，x为改元素
	bool IsEmpty()const { return first->link == NULL ? true : false; }//判空	
	void output();//输出
	void inputFront(T*, int length);//前插法建表
	void inputRear(T*, int length);//后差法建表（常用）
	LinkList<T>& operator=(LinkList<T>& L);//重载函数：赋值
protected:
	LinkNode<T> *first;
};

