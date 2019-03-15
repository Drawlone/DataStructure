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
	// 含引用，故可自动链入父节点
	bool Insert(const E &x, BSTNode<E> * &ptr);
	bool Remove(const E x, BSTNode<E> * &ptr);

	// c语言中的实现（无引用）
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
	// c版
	root = Insert_c(x, root);
	return true;
	*/
}

template<class E>
inline bool BST<E>::Remove(const E x)
{
	return Remove_c(x, root);
	/*
	// c版
	root = Remove_c(x, root);
	return true;
	*/
}

template<class E>
inline void BST<E>::PrintTree(BSTNode<E>* ptr) const
{
	//采用队列实现层次序遍历，自上而下，自左而右
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
		// 注意：之所以这里的ptr能链接到其根节点，是因为ptr指针是使用引用传递的，即ptr是上个过程的ptr->left(或right)
		// 可断点查看这一过程
		ptr = new BSTNode<E>(x);
		return true;
	}
	else if (x < ptr->data) {
		Insert(x, ptr->left);
	}
	else if (x > ptr->data) { 
		Insert(x, ptr->right);
	}
	return false; // 等于则不插入
}

template<class E>
inline bool BST<E>::Remove(const E x, BSTNode<E>* &ptr)
{
	BSTNode<E> *temp;

	if (ptr != NULL) {
		if (x < ptr->data) {
			Remove(x, ptr->left); // 引用传递，故子结点修改自动链入ptr
		}
		else if (x > ptr->data) {
			Remove(x, ptr->right);  // 引用传递，故子结点修改自动链入ptr
		}
		else {
			if (ptr->left != NULL && ptr->right != NULL) {
				temp = Min(ptr->right);
				ptr->data = temp->data;
				Remove(ptr->data, ptr->right);  // // 引用传递，故子结点修改自动链入ptr
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
		// 注意：之所以这里的ptr能链接到其根节点，是因为ptr指针是使用引用传递的，即ptr是上个过程的ptr->left(或right)
		// 可断点查看这一过程
		ptr = new BSTNode<E>(x);
		return ptr;
	}
	else if (x < ptr->data) {
		ptr->left = Insert_c(x, ptr->left);  // 链入
	}
	else if (x > ptr->data) {
		ptr->right = Insert_c(x, ptr->right);  //链入
	}
	return ptr;  // 等于则什么都不做
}

template<class E>
inline BSTNode<E>* BST<E>::Remove_c(const E & x, BSTNode<E>* ptr)
{
	// 要保证二叉搜索树的完整性
	BSTNode<E> * temp;
	if(ptr==NULL) return NULL;
	if (x < ptr->data) { 
		ptr->left = Remove_c(x, ptr->left); 
	}
	else if (x > ptr->data) { 
		ptr->right = Remove_c(x, ptr->right); 
	}
	else {
		// 找到删除结点
		/*
		 删除的实质是替换：先替换，再释放没用的结点
		*/
		if (ptr->left && ptr->right) {
			// 左右孩子均存在,两种方案:
			// ①用左子树的最大结点(无右结点)替换
			// ②用右子树的最小结点(无左结点）替换
			// 这里选用②
			temp = Min(ptr->right);
			ptr->data = temp->data;  // 替换
			ptr->right = Remove_c(ptr->data, ptr->right); // 从右子树把那个temp删掉
		}
		else 
		{
			// 被删结点只有一个或无子女
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
