#include<iostream>
#include<stdlib.h>
#include"LinkStack.h"
#include"LinkedQueue.h"
using namespace std;

template<class T>
struct BinTreeNode {
	T data;
	BinTreeNode<T> *leftChild, *rightChild;
	BinTreeNode() :leftChild(NULL), rightChildL(NULL) {}
	BinTreeNode<T>(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL) : data(x), leftChild(l), rightChild(r) {}
};

template<class T>
class BinaryTree {
public:
	BinaryTree() :root(NULL) {}
	BinaryTree(const BinaryTree<T>& s);
	~BinaryTree() { destroy(root); }

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
	BinTreeNode<T> * LeftChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->rightChild : NULL;
	}

	//返回树高度
	int Height() { return Height(root); }
	//返回结点数
	int Size() { return Size(root); }

	//取根
	BinTreeNode<T> * getRoot()const { return root; }

	//前序遍历
	void preOrder(void(*visit))(BinTreeNode<T> *p) {
		preOrder(root, visit);
	}
	//中序遍历
	void inOrder(void(*visit))(BinTreeNode<T> *p) {
		inOrder(root, visit);
	}
	//后序遍历
	void postOrder(void(*visit))(BinTreeNode<T> *p) {
		postOrder(root, visit);
	}
	//层次序遍历
	void levelOrder(void(*visit)(BinTreeNode<T> *p));

	//插入新元素
	int Insert(const T& item);
	BinTreeNode<T> *Find(T& item)const;
protected:
	BinTreeNode<T> * root;

	//从文件读入建树
	void CreateBinTree(istream& in, BinTreeNode<T> * &subTree);

	//插入
	bool Insert(BinTreeNode<T> * &subTree, const T& x);
	//删除
	void destory(BinTreeNode<T> * subTree);
	//查找
	bool Find(BinTreeNode<T> * subTree, const T& x)const;
	//复制
	BinTreeNode<T> * Copy(BinTreeNode<T> * orignode);

	//返回树高度
	int Height(BinTreeNode<T> * subTree);
	//返回结点数
	int Size(BinTreeNode<T> * subTree);

	//返回父节点
	BinTreeNode<T> * Parent(BinTreeNode<T> *subTree, BinTreeNode<T> * current);

	//搜寻x
	BinTreeNode<T> * Find(BinTreeNode<T> *subTree.const T& x)const;
	//搜索并输出根为subTree的二叉树
	void Traverse(BinTreeNode<T> * subTree, ostream& out);

	//前序遍历输出
	void preOrder(BinTreeNode<T>& subTree, void(*vist)(BinTreeNode<T> *p));
	//中序遍历输出
	void inOrder(BinTreeNode<T>& subTree, void(*vist)(BinTreeNode<T> *p));
	//后序遍历输出
	void postOrder(BinTreeNode<T>& subTree, void(*vist)(BinTreeNode<T> *p));

	//重载操作：输入
	friend istream& operator>>(istream& in, BinaryTree<T>& Tree);
	//重载操作：输出
	friend ostream& operator<<(ostream& out, BinaryTree<T>& Tree);
};

template<class T>
void BinaryTree<T>::levelOrder(void(*visit)(BinTreeNode<T> * p)) {
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
BinTreeNode<T> * BinaryTree<T>::Copy(BinTreeNode<T> * orignode) {
	if (orignode == NULL)return NULL;
	BinTreeNode<T> * temp = new BinTreeNode<T>;
	temp->data = orignode->data;
	temp->leftChild = Copy(orignode->leftChild);
	temp->rightChild = Copy(orignode->rightChild);
	return temp;
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s) {
	root = Copy(s.root);//只传根，其它结点在Copy中构造好了
}

template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>& subTree, void(*vist)(BinTreeNode<T> *p)) {
	if (subTree != NULL) {
		vist(subTree);
		preOrder(subTree->leftChild, visit);
		preOrder(subTree->rightChild, visit);
	}
}

template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>& subTree, void(*vist)(BinTreeNode<T> *p)) {
	if (subTree != NULL) {
		inOrder(subTree->leftChild, visit);
		vist(subTree);
		inOrder(subTree->rightChild, visit);
	}
}

template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>& subTree, void(*vist)(BinTreeNode<T> *p)) {
	if (subTree != NULL) {
		postOrder(subTree->leftChild, visit);
		postOrder(subTree->rightChild, visit);
		vist(subTree);
	}
}

template<class T>
void CreateBinTree(istream& in, BinTreeNode<T>* &BT) {
	LinkedStack<BinTreeNode<char> *> s;
	BT = NULL;
	BinTreeNode<char> *p.*t;
	int k;
	in >> ch;
	while (ch != ';') {
		switch (ch) {
		case'(':s.Push(p); k = 1; break;//进入子树
		case')':s.Pop(t); break;//退出子树
		case',':k = 2; break;
		default:p = new BinTreeNode(ch);
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

template<class T>
void BinaryTree<T>::destory(BinTreeNode<T> * subTree) {
	if (subTree != NULL) {
		destory(subTree->leftChild);
		destory(subTree->rightChild);
		delete subTree;
	}
}

template<class T>
BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> * current) {
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
void BinaryTree<T>::Traverse(BinTreeNode<T> * subTree, ostream& out) {
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
ostream& operator<<(ostream& out, BinaryTree<T>& Tree) {
	out << "二叉树的前序遍历\n";
	Tree.Traverse(Tree.root, out);
	out << endl;
	return out;
}
