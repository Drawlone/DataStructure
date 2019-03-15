#include<iostream>
#include<stdlib.h>
#include"LinkStack.h"
#include"LinkedQueue.h"
using namespace std;


template<class T>
struct BinTreeNode {
	T data;
	BinTreeNode<T> *leftChild, *rightChild;
	BinTreeNode() :leftChild(NULL), rightChild(NULL) {}
	BinTreeNode<T>(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL) : data(x), leftChild(l), rightChild(r) {}
};

template<class T>
class BinaryTree {
	//���ز���������
	template<class T> friend istream& operator>>(istream& in, BinaryTree<T>& Tree);
	//���ز��������
	template<class T> friend ostream& operator<<(ostream& out, BinaryTree<T>& Tree);
public:
	BinaryTree() :root(NULL) {}
	BinaryTree(const BinaryTree<T>& s);
	~BinaryTree() { destory(root); }

	//�ж϶������շ�
	bool IsEmpty() { return (root == NULL) ? true : false; }

	//���ظ��ڵ�
	BinTreeNode<T> * Parent(BinTreeNode<T> * current) {
		return (root == NULL || root == current) ? NULL : Parent(root, current);
	}
	//��������Ů
	BinTreeNode<T> * LeftChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->leftChild : NULL;
	}
	//��������Ů
	BinTreeNode<T> * RightChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->rightChild : NULL;
	}

	//�������߶�
	//int Height() { return Height(root); }
	//���ؽ����
	//int Size() { return Size(root); }

	//ȡ��
	BinTreeNode<T> * getRoot()const { return root; }

	//ǰ�����
	void preOrder(void(*visit)(BinTreeNode<T> *p)) {
		preOrder(root, visit);
	}
	//�������
	void inOrder(void(*visit)(BinTreeNode<T> *p)) {
		inOrder(root, visit);
	}
	//�������
	void postOrder(void(*visit)(BinTreeNode<T> *p)) {
		postOrder(root, visit);
	}
	//��������
	void levelOrder(void(*visit)(BinTreeNode<T> *p));

	//�ǵݹ�ǰ��������
	void PreOrder(void(*visit)(BinTreeNode<T> *p));
	//�ǵݹ�����������
	void InOrder(void(*visit)(BinTreeNode<T> *p));
	//�ǵݹ����������,���㷨�Ƚ���ͨ
	void PostOrder1(void(*visit)(BinTreeNode<T> *p));
	//�ǵݹ����������,���㷨�Ƚ�����
	void PostOrder2(void(*visit)(BinTreeNode<T> *p));

	//������Ԫ��
	//int Insert(const T& item);
	//BinTreeNode<T> *Find(T& item)const;
protected:
	BinTreeNode<T> * root;

	//����
	//bool Insert(BinTreeNode<T> * &subTree, const T& x);
	//ɾ��
	void destory(BinTreeNode<T> * subTree);
	//����
	BinTreeNode<T> * Copy(BinTreeNode<T> * orignode);

	//�������߶�
	//int Height(BinTreeNode<T> * subTree);
	//���ؽ����
	//int Size(BinTreeNode<T> * subTree);

	//���ظ��ڵ�
	BinTreeNode<T> * Parent(BinTreeNode<T> *subTree, BinTreeNode<T> * current);

	//��Ѱx
	//BinTreeNode<T> * Find(BinTreeNode<T> *subTree, const T& x)const;
	//�����������ΪsubTree�Ķ�����
	void Traverse(BinTreeNode<T> * subTree, ostream& out);

	//ǰ��������
	void preOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p));
	//����������
	void inOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p));
	//����������
	void postOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p));
};

template<class T>
inline void BinaryTree<T>::levelOrder(void(*visit)(BinTreeNode<T> * p)) {
	//���ö���ʵ�ֲ������������϶��£��������
	LinkedQueue<BinTreeNode<T>*>Q;
	BinTreeNode<T> * p = root;
	Q.EnQueue(p);
	while (!Q.IsEmpty()) {
		Q.DeQueue(p);
		visit(p);
		if (p->leftChild != NULL)Q.EnQueue(p->leftChild);
		if (p->rightChild != NULL)Q.EnQueue(p->rightChild);
	}
}

template<class T>
inline BinTreeNode<T> * BinaryTree<T>::Copy(BinTreeNode<T> * orignode) {
	if (orignode == NULL)return NULL;
	BinTreeNode<T> * temp = new BinTreeNode<T>;
	temp->data = orignode->data;
	temp->leftChild = Copy(orignode->leftChild);
	temp->rightChild = Copy(orignode->rightChild);
	return temp;
}

template<class T>
inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& s) {
	root = Copy(s.root);//ֻ���������������Copy�й������
}

template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p)) {
	if (subTree != NULL) {
		visit(subTree);
		preOrder(subTree->leftChild, visit);
		preOrder(subTree->rightChild, visit);
	}
}

template<class T>
inline void BinaryTree<T>::inOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p)) {
	if (subTree != NULL) {
		inOrder(subTree->leftChild, visit);
		vist(subTree);
		inOrder(subTree->rightChild, visit);
	}
}

template<class T>
inline void BinaryTree<T>::postOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p)) {
	if (subTree != NULL) {
		postOrder(subTree->leftChild, visit);
		postOrder(subTree->rightChild, visit);
		vist(subTree);
	}
}

template<class T>
inline void BinaryTree<T>::PreOrder(void(*visit)(BinTreeNode<T>*p))
{
	if (root == NULL) return;
	LinkedStack<BinTreeNode<T>*> s;

	s.Push(root);
	do {
		BinTreeNode<T> *temp = s.Pop();
		visit(temp);
		if (temp->rightChild != NULL) { s.Push(temp->rightChild); }
		if (temp->leftChild != NULL) { s.Push(temp->leftChild); }
	} while (!s.IsEmpty());

}

template<class T>
inline void BinaryTree<T>::InOrder(void(*visit)(BinTreeNode<T>*p))
{
	LinkedStack<BinTreeNode<T>*> s;
	BinTreeNode<T> *p = root;

	do {
		while (p != NULL) {
			s.Push(p);
			p = p->leftChild;
		}
		if (!s.IsEmpty()) {
			p = s.Pop();
			visit(p);
			p = p->rightChild;
		}
	} while (p != NULL || !s.IsEmpty());
}

template<class T>
inline void BinaryTree<T>::PostOrder1(void(*visit)(BinTreeNode<T>*p))
{
	BinTreeNode<T> *p = root, *last = root;
	LinkedStack<BinTreeNode<T>*> S;
	S.Push(p);

	while(!S.IsEmpty()) {
		S.getTop(p);
		if (p->leftChild == NULL && p->rightChild == NULL ||
			p->rightChild == NULL && last == p->leftChild ||
			last == p->rightChild) {
			p = S.Pop();
			last = p;
			visit(p);
		}
		else {
			if (p->rightChild) S.Push(p->rightChild);
			if (p->leftChild) S.Push(p->leftChild);
		}
	}
}

template<class T>
inline void BinaryTree<T>::PostOrder2(void(*visit)(BinTreeNode<T>*p))
{
	BinTreeNode<T> *p = root, *q;
	LinkedStack<BinTreeNode<T>*> S;
	S.Push(p);
	S.Push(p);
	while (!S.IsEmpty()) {
		p = S.Pop();
		if (!S.IsEmpty() && S.getTop(q) && p == q) {
			if (p->rightChild != NULL) S.Push(p->rightChild), S.Push(p->rightChild);
			if (p->leftChild != NULL) S.Push(p->leftChild), S.Push(p->leftChild);
		}
		else {
			visit(p);
		}
	}
}

template<class T>
inline void BinaryTree<T>::destory(BinTreeNode<T> * subTree) {
	if (subTree != NULL) {
		destory(subTree->leftChild);
		destory(subTree->rightChild);
		delete subTree;
	}
}

template<class T>
inline BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> * current) {
	/*
	subTreeΪ������ʼ��㣬currentΪ��ǰ���
	���������ʼ���ΪNULL������NULL
	���������ʼ�ڵ���Ů�е�ǰ��㣬���ؽ��
	���򣬴ӱ�����ʼ��㿪ʼ�ݹ���ң��ȱ�������Ů���ٱ�������Ů
	*/
	if (subTree == NULL)return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current)
		return subTree;
	BinTreeNode<T> *p;
	if ((p = Parent(subTree->leftChild, current)) != NULL)return p;
	else return Parent(subTree->rightChild, current);
}

template<class T>
inline void BinaryTree<T>::Traverse(BinTreeNode<T> * subTree, ostream& out) {
	//ǰ��ݹ����
	if (subTree != NULL) {
		out << subTree->data << ' ';
		Traverse(subTree->leftChild, out);
		Traverse(subTree->rightChild, out);
	}
}

template<class T>
istream& operator >>(istream& in, BinaryTree<T>& Tree) {
	CreateBinTree(in, Tree.root);
	return in;
}

template<class T>
ostream& operator <<(ostream& out, BinaryTree<T>& Tree) {
	out << "��������ǰ�����\n";
	Tree.Traverse(Tree.root, out);
	out << endl;
	return out;
}

void CreateBinTree(istream & in, BinTreeNode<char>*& BT)
{
	LinkedStack<BinTreeNode<char> *> s;
	BT = NULL;
	BinTreeNode<char> *p, *t;
	int k;
	char ch;
	in >> ch;
	while (ch != ';') {
		switch (ch) {
		case'(':s.Push(p); k = 1; break;//��������
		case')':t = s.Pop(); break;//�˳�����
		case',':k = 2; break;
		default:p = new BinTreeNode<char>(ch);
			if (BT == NULL)BT = p;
			else if (k == 1) {
				s.getTop(t);
				t->leftChild = p;
			}
			else {
				s.getTop(t);
				t->rightChild = p;
			}
		}
		in >> ch;
	}
}
