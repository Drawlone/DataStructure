#pragma once
#include"LinkList.h"
#include<assert.h>
#include<iostream>
using namespace std;

template<class T>
class LinkedStack {
public:
	LinkedStack() : top(NULL) {}
	~LinkedStack() { makeEmpty(); }
	void Push(const T &x);//进栈
	T Pop();//退栈
	bool getTop(T &x);//读取栈顶元素
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;//求栈内元素个数
	void makeEmpty();
	friend ostream& operator<<(ostream& os, LinkedStack<T>& S);
	void output();
private:
	LinkNode<T> * top;
};

template<class T>
inline ostream& operator<<(ostream& os, LinkedStack<T>& S) {
	os << "栈中元素个数" << S.getSize() << endl;
	LinkNode<T> *p = S.top;
	int i = 0;
	while (p != NULL) {
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}

template<class T>
inline int LinkedStack<T>::getSize()const {
	LinkNode<T> *p = top; int k = 0;
	while (top != NULL) {
		top = top->link;
		k++;
	}
	return k;
}

template<class T>
inline bool LinkedStack<T>::getTop(T& x) {
	if (IsEmpty() == true) {
		return false;
	}
	x = top->data;
	return true;
}

template<class T>
inline T LinkedStack<T>::Pop() {
	T x;
	if (IsEmpty() == true) {
		cerr << "空栈无法退栈";
		exit(1);
	}
	LinkNode<T> *p = top;
	top = top->link;
	x = p->data;
	delete p;
	return x;
}

template<class T>
inline void LinkedStack<T>::Push(const T& x) {
	top = new LinkNode<T>(x, top);
	assert(top != NULL);
}

template<class T>
inline void LinkedStack<T>::makeEmpty() {
	LinkNode<T> *p;
	while (top != NULL) {
		p = top;
		top = top->link;
		delete p;
	}
}

template<class T>
inline void LinkedStack<T>::output()
{
	LinkNode<T> *p = top;
	int i = 0;
	while (p->link != NULL) {
		cout << "#" << i + 1 << ":" << p->data << endl;
		p = p->link;
	}
}

void LinkStackTest() {
	LinkedStack<int> s;
	int v;
	for (int i = 0; i < 50; i++) {
		s.Push(i);
	}
	v = s.Pop();
	cout << "出栈：" << v << endl;
	s.Push(100);
	s.output();
	for (int i = 60; i < 70; i++) {
		s.Push(i);
	}
	s.output();
}

bool pairCheck(string & str) {
	// 这里扩展性不是很好，可以改进的，，，
	LinkedStack<char> s;
	for (auto &c : str) {

		if (c == '{' || c == '(' || c == '[') {
			s.Push(c);
		}
		else if (c == '}' || c == ')' || c == ']') {
			char temp;
			if (s.getTop(temp)) {
				if (temp == '{'&&c != '}' || temp == '('&&c != ')' || temp == '['&&c != ']') return false;
				else s.Pop();
			}
			else {
				return false;
			}
		}
	}
	if(s.IsEmpty())
		return true;
	else return false;
}

int Fibnacci(int n) {
	LinkedStack<int> s;
	int sum = 0;
	                                  /* 
									   * 栈中始终只有分解后未执行（或待分解）的任务，
									   * 已经分解的任务不会在栈中保存
									   */
	s.Push(n);								// 拿到任务（进栈）
	do {
		int temp = s.Pop();                 // 拿出任务准备执行或分解
		if (temp == 0 || temp == 1) {       // 无法分解，执行计算
			sum += 1;
		}
		else {                              // 可以分解，分解任务压栈
			s.Push(temp - 1);               /* 分解后任务所需参数只由父任务(temp)提供 */
			s.Push(temp - 2);
		}
	} while (!s.IsEmpty());               
	return sum;
}

void Hanoi(size_t n) {
	/*
	 * 用栈实现递归需要考虑递归实现的结构（树状）
	 * 若两个递归语句之间插了其它输出，如何用栈来实现？（汉罗塔问题）
		* 让输出内容具备特殊标志（可以区别于其它内容），将输出内容想办法push进栈（可用结构体），写在两递归语句之间，
		* 然后在判断任务时加以甄别，挑出特殊标志，进行输出；
		* 汉罗塔的特殊标志就是1，其和递归停止标志一样，其输出格式相同，故可公用。
		* 对于此类问题是否还有更好的解决方案？
	 */

	struct Han {
		size_t n;
		char a;
		char b;
		char c;
	};
	LinkedStack<Han> s;
	Han initial{ n, 'A', 'B', 'C' };
	unsigned int step = 0;

	s.Push(initial);
	do {
		Han temp = s.Pop();
		if (temp.n == 1) {
			cout << "Move " << temp.a << " to " << temp.c << "." << endl;
			step++;
		}
		else {
			Han subtask1{ temp.n - 1, temp.a, temp.c, temp.b };
			Han subtask2{ temp.n - 1, temp.b, temp.a, temp.c };
			Han midtask{ 1, temp.a, temp.b, temp.c };
			s.Push(subtask2);
			s.Push(midtask);  // 中间输出
			s.Push(subtask1);
		}

	} while (!s.IsEmpty());
	cout << "总共移动" << step << "次" << endl;
}

void AkmQ(int m, int n) {
	/* 双递归函数的非递归实现，由于一层递归的值需要二层递归值，因此分解任务时就不能把需要二层递归值的任务取出来了 */
	/* 
	 * 初始版本，待优化部分：
		* 读取栈顶时使用Pop，因为它不会遇到未得到值的Akm
		* 这样在拿出任务后（pop）栈中只会保存未完全赋值的Akm
		
	 */

	struct Akm {
		int m;
		int n;
		bool deeper;  // true代表需要二层递归值（会在栈中停留），false代表不需要，不用留在栈中
	};

	LinkedStack<Akm> s;
	Akm initial{ m, n, false };
	int result = 0;

	s.Push(initial);
	do {
		Akm temp;
		s.getTop(temp);
		if (temp.m == 0) {
			result = temp.n + 1;
			Akm t = s.Pop();
			while (!t.deeper && !s.IsEmpty()) {  // 寻找deeper为true的项
				t = s.Pop();
			}
			if (!s.IsEmpty()) {
				t = { t.m, result, false };
				s.Push(t);
			}
		}
		else if (temp.m != 0 && temp.n == 0) {
			Akm subtask1{ temp.m - 1, 1, false };
			s.Push(subtask1);
		}
		else if (temp.m != 0 && temp.n != 0) {
			Akm subtask2{ temp.m - 1, -1, true };
			Akm subtask3{ temp.m, temp.n - 1, false };
			s.Push(subtask2);
			s.Push(subtask3);
		}
	} while (!s.IsEmpty());
	cout << result << endl;
}

void Ackerman(int m, int n) {

	/* 最终版 */
	/* 非递归的终极版 */

	struct Akm {
		int m;
		int n;  // -1代表需要二层递归值（会在栈中停留），否则不需要，不用留在栈中
	};
	LinkedStack<Akm> s;
	Akm initial{ m, n};
	int result = 0;

	s.Push(initial);
	do {
		Akm temp = s.Pop();
		if (temp.m == 0) {
			result = temp.n + 1;
			if (!s.IsEmpty()) {  // 栈未空说明有任务未完成，且需要当前结果二次递归
				Akm t = s.Pop();
				t = {t.m, result};  // 在此完成了二层递归给一层递归的传值，这是最低端向上传值
				s.Push(t);
			}
		}
		else if (temp.m != 0 && temp.n == 0) {
			Akm subtask1{ temp.m - 1, 1};
			s.Push(subtask1);
		}
		else if (temp.m != 0 && temp.n != 0) {
			Akm subtask2{ temp.m - 1, -1};  // 第二个参数可随意设，它在退栈之前会被重设的
			Akm subtask3{ temp.m, temp.n - 1};
			s.Push(subtask2);
			s.Push(subtask3);
		}
	} while (!s.IsEmpty());
	cout << result << endl;
}

int AkmByRecursion(int m, int n) {
	if (m == 0) {
		return n + 1;
	}
	else if (m != 0 && n == 0) {
		return AkmByRecursion(m - 1, 1);
	}
	else if (m != 0 && n != 0) {
		return AkmByRecursion(m - 1, AkmByRecursion(m, n - 1));
	}
	return 0;
}

/* 尾递归的探索：
 * 尾递归意味着有去无回（就计算意义而言），即最终结果在去的时候得到了，回来时只是在把最终结果返回(如斐波那契数列)
 * 这用栈实现意味着分解任务时不需要将已经分解的任务保存在栈中，栈中保留的只有当前正在进行的任务
 * 这是好的特性，可以避免爆栈
 * 还有非尾递归的情况（如计算阶乘），这时每一步都要保存在栈中等待回调，当然这是可以优化为尾递归的；
 * 尾递归和非尾递归同时有（如Akm问题），这导致一部分计算要暂留在栈中等待回调（留的越少越好）；
 */

size_t permutation(string str, size_t k = 0) {
	// 全排列递归实现
	static size_t num;
	if (k == str.size()) {
		cout << str << endl;
		num++;
	}
	else {
		for (size_t i = k; i < str.size(); i++) {
			swap(str[k], str[i]);
			permutation(str, k + 1);
			swap(str[k], str[i]);
		}
	}
	return num;
}

// 组合递归实现，，，，，有点麻烦