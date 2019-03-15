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
	//重载操作：输入
	template<class T> friend istream& operator>>(istream& in, BinaryTree<T>& Tree);
	//重载操作：输出
	template<class T> friend ostream& operator<<(ostream& out, BinaryTree<T>& Tree);
public:
	BinaryTree() :root(NULL) {}
	BinaryTree(const BinaryTree<T>& s);
	~BinaryTree() { destory(root); }

	//判断二叉树空否
	bool IsEmpty() { return (root == NULL) ? true : false; }

	//返回父节点
	BinTreeNode<T> * Parent(BinTreeNode<T> * current) {
		return (root == NULL || root == current) ? NULL : Parent(root, current);
	}
	//返回左子女
	BinTreeNode<T> * LeftChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->leftChild : NULL;
	}
	//返回右子女
	BinTreeNode<T> * RightChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->rightChild : NULL;
	}

	//返回树高度
	//int Height() { return Height(root); }
	//返回结点数
	//int Size() { return Size(root); }

	//取根
	BinTreeNode<T> * getRoot()const { return root; }

	//前序遍历
	void preOrder(void(*visit)(BinTreeNode<T> *p)) {
		preOrder(root, visit);
	}
	//中序遍历
	void inOrder(void(*visit)(BinTreeNode<T> *p)) {
		inOrder(root, visit);
	}
	//后序遍历
	void postOrder(void(*visit)(BinTreeNode<T> *p)) {
		postOrder(root, visit);
	}
	//层次序遍历
	void levelOrder(void(*visit)(BinTreeNode<T> *p));

	//非递归前序遍历输出
	void PreOrder(void(*visit)(BinTreeNode<T> *p));
	//非递归中序遍历输出
	void InOrder(void(*visit)(BinTreeNode<T> *p));
	//非递归后序遍历输出,此算法比较普通
	void PostOrder1(void(*visit)(BinTreeNode<T> *p));
	//非递归后序遍历输出,此算法比较巧妙
	void PostOrder2(void(*visit)(BinTreeNode<T> *p));

	//插入新元素
	//int Insert(const T& item);
	//BinTreeNode<T> *Find(T& item)const;
protected:
	BinTreeNode<T> * root;

	//插入
	//bool Insert(BinTreeNode<T> * &subTree, const T& x);
	//删除
	void destory(BinTreeNode<T> * subTree);
	//复制
	BinTreeNode<T> * Copy(BinTreeNode<T> * orignode);

	//返回树高度
	//int Height(BinTreeNode<T> * subTree);
	//返回结点数
	//int Size(BinTreeNode<T> * subTree);

	//返回父节点
	BinTreeNode<T> * Parent(BinTreeNode<T> *subTree, BinTreeNode<T> * current);

	//搜寻x
	//BinTreeNode<T> * Find(BinTreeNode<T> *subTree, const T& x)const;
	//搜索并输出根为subTree的二叉树
	void Traverse(BinTreeNode<T> * subTree, ostream& out);

	//前序遍历输出
	void preOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p));
	//中序遍历输出
	void inOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p));
	//后序遍历输出
	void postOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T> *p));
};

template<class T>
inline void BinaryTree<T>::levelOrder(void(*visit)(BinTreeNode<T> * p)) {
	//采用队列实现层次序遍历，自上而下，自左而右
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
	root = Copy(s.root);//只传根，其它结点在Copy中构造好了
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
	subTree为遍历开始结点，current为当前结点
	如果遍历开始结点为NULL，返回NULL
	如果遍历开始节点子女有当前结点，返回结点
	否则，从遍历开始结点开始递归查找，先遍历左子女，再遍历右子女
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
	//前序递归输出
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
	out << "二叉树的前序遍历\n";
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
		case'(':s.Push(p); k = 1; break;//进入子树
		case')':t = s.Pop(); break;//退出子树
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
