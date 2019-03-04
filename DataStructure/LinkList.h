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
	void makeEmpty();//��������Ϊ�ձ�
	int Length()const;//����������
	LinkNode<T> *getHead()const { return first; }//����ͷ�ڵ��ַfirst
	LinkNode<T> *Search(T x);//Ѱ��ֵΪx�Ľڵ㣬�������ַ
	LinkNode<T> *Locate(int i);//��λ��i���ڵ㣬���ص�ַ
	bool getData(int i, T& x)const;//ȡ����i��Ԫ�ص�ֵ
	bool setData(int i, T& x);//��x�޸ĵ�i��Ԫ�ص�ֵ
	bool Insert(int i, T& x);//�ڵ�i��Ԫ�غ����x
	bool Remove(int i, T& x);//ɾ����i��Ԫ�أ�xΪ��Ԫ��
	bool IsEmpty()const { return first->link == NULL ? true : false; }//�п�	
	void output();//���
	void inputFront(T*, int length);//ǰ�巨����
	void inputRear(T*, int length);//���������ã�
	LinkList<T>& operator=(LinkList<T>& L);//���غ�������ֵ
protected:
	LinkNode<T> *first;
};

