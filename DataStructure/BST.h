#pragma once
#include<iostream>
#include"LinkedQueue.h"
using namespace std;

template<class E>
struct BSTNode {
	E data;
	BSTNode<E> *left, *right;
	BSTNode(const E &x) :data(x), left(NULL), right(NULL) {};
};


template<class E>
class BST
{
public:
	BST():root(NULL) {};
	~BST();
	bool Search(const E &x)const;
	void PrintTree()const { PrintTree(root); };
	E Min();
	E Max();
	bool Insert(const E &x);
	bool Remove(const E x);
private:
	BSTNode<E> *root;

	void PrintTree(BSTNode<E>* ptr)const;
	BSTNode<E>* Search(const E &x, BSTNode<E> *p)const;
	BSTNode<E>* Min(BSTNode<E> *p)const;
	BSTNode<E>* Max(BSTNode<E> *p)const;
	// �����ã��ʿ��Զ����븸�ڵ�
	bool Insert(const E &x, BSTNode<E> * &ptr);
	bool Remove(const E x, BSTNode<E> * &ptr);

	// c�����е�ʵ�֣������ã�
	BSTNode<E>* Insert_c(const E &x, BSTNode<E> * ptr);
	BSTNode<E>* Remove_c(const E &x, BSTNode<E> * ptr);
};

template<class E>
BST<E>::~BST()
{
}

template<class E>
inline bool BST<E>::Search(const E &x)const
{
	return Search(x, root);
}

template<class E>
inline E BST<E>::Min()
{	
	return Min(root)->data;
}

template<class E>
inline E BST<E>::Max()
{
	return Max(root)->data;
}

template<class E>
inline bool BST<E>::Insert(const E & x)
{
	return Insert(x, root);
	/*
	// c��
	root = Insert_c(x, root);
	return true;
	*/
}

template<class E>
inline bool BST<E>::Remove(const E x)
{
	return Remove_c(x, root);
	/*
	// c��
	root = Remove_c(x, root);
	return true;
	*/
}

template<class E>
inline void BST<E>::PrintTree(BSTNode<E>* ptr) const
{
	//���ö���ʵ�ֲ������������϶��£��������
	LinkedQueue<BSTNode<E>*>Q;
	BSTNode<E> * p = ptr;
	Q.EnQueue(p);
	while (!Q.IsEmpty()) {
		Q.DeQueue(p);
		cout << p->data<<" ";
		if (p->left != NULL)Q.EnQueue(p->left);
		if (p->right != NULL)Q.EnQueue(p->right);
	}
}

template<class E>
inline BSTNode<E>* BST<E>::Search(const E & x, BSTNode<E>* p) const
{
	if (p == NULL) return NULL;
	if (x < p->data) {
		Search(x, p->left);
	}
	else if (x > p->data) {
		Search(x, p->right);
	}
	else {
		return p;
	}
	return NULL;
}

template<class E>
inline BSTNode<E>* BST<E>::Min(BSTNode<E>* p)const
{
	if (p->left == NULL) 
	{
		return p;
	}
	else return Min(p->left);

}

template<class E>
inline BSTNode<E>* BST<E>::Max(BSTNode<E>* p) const
{
	if (p->right == NULL)
	{
		return p;
	}
	else return Min(p->right);
}

template<class E>
inline bool BST<E>::Insert(const E & x, BSTNode<E>* &ptr)
{
	if (ptr == NULL) {
		// ע�⣺֮���������ptr�����ӵ�����ڵ㣬����Ϊptrָ����ʹ�����ô��ݵģ���ptr���ϸ����̵�ptr->left(��right)
		// �ɶϵ�鿴��һ����
		ptr = new BSTNode<E>(x);
		return true;
	}
	else if (x < ptr->data) {
		Insert(x, ptr->left);
	}
	else if (x > ptr->data) { 
		Insert(x, ptr->right);
	}
	return false; // �����򲻲���
}

template<class E>
inline bool BST<E>::Remove(const E x, BSTNode<E>* &ptr)
{
	BSTNode<E> *temp;

	if (ptr != NULL) {
		if (x < ptr->data) {
			Remove(x, ptr->left); // ���ô��ݣ����ӽ���޸��Զ�����ptr
		}
		else if (x > ptr->data) {
			Remove(x, ptr->right);  // ���ô��ݣ����ӽ���޸��Զ�����ptr
		}
		else {
			if (ptr->left != NULL && ptr->right != NULL) {
				temp = Min(ptr->right);
				ptr->data = temp->data;
				Remove(ptr->data, ptr->right);  // // ���ô��ݣ����ӽ���޸��Զ�����ptr
			}
			else {
				temp = ptr;
				if (ptr->left == NULL) {
					ptr = ptr->right;
				}
				else {
					ptr = ptr->left;
				}
				delete temp;
			}

		}
		return true;
	}
	return false;
}

template<class E>
inline BSTNode<E>* BST<E>::Insert_c(const E & x, BSTNode<E>* ptr)
{
	if (ptr == NULL) {
		// ע�⣺֮���������ptr�����ӵ�����ڵ㣬����Ϊptrָ����ʹ�����ô��ݵģ���ptr���ϸ����̵�ptr->left(��right)
		// �ɶϵ�鿴��һ����
		ptr = new BSTNode<E>(x);
		return ptr;
	}
	else if (x < ptr->data) {
		ptr->left = Insert_c(x, ptr->left);  // ����
	}
	else if (x > ptr->data) {
		ptr->right = Insert_c(x, ptr->right);  //����
	}
	return ptr;  // ������ʲô������
}

template<class E>
inline BSTNode<E>* BST<E>::Remove_c(const E & x, BSTNode<E>* ptr)
{
	// Ҫ��֤������������������
	BSTNode<E> * temp;
	if(ptr==NULL) return NULL;
	if (x < ptr->data) { 
		ptr->left = Remove_c(x, ptr->left); 
	}
	else if (x > ptr->data) { 
		ptr->right = Remove_c(x, ptr->right); 
	}
	else {
		// �ҵ�ɾ�����
		/*
		 ɾ����ʵ�����滻�����滻�����ͷ�û�õĽ��
		*/
		if (ptr->left && ptr->right) {
			// ���Һ��Ӿ�����,���ַ���:
			// �����������������(���ҽ��)�滻
			// ��������������С���(�����㣩�滻
			// ����ѡ�â�
			temp = Min(ptr->right);
			ptr->data = temp->data;  // �滻
			ptr->right = Remove_c(ptr->data, ptr->right); // �����������Ǹ�tempɾ��
		}
		else 
		{
			// ��ɾ���ֻ��һ��������Ů
			temp = ptr;
			if (ptr->left == NULL)
				ptr = ptr->right;
			else if (ptr->right == NULL)
				ptr = ptr->left;
			delete temp;
		}
	}
	return ptr;
}

void BSTTest() {
	BST<int> Bst;
	int test[] = { 53, 78, 94, 65, 17, 9, 81, 45, 23, 88 };
	for (auto i = begin(test); i != end(test); i++) {
		Bst.Insert(*i);
		Bst.PrintTree();
		cout << endl;
	}
	Bst.Remove(78);
	Bst.PrintTree();
	cout << endl;
}
