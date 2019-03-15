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
	void Push(const T &x);//��ջ
	T Pop();//��ջ
	bool getTop(T &x);//��ȡջ��Ԫ��
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;//��ջ��Ԫ�ظ���
	void makeEmpty();
	friend ostream& operator<<(ostream& os, LinkedStack<T>& S);
	void output();
private:
	LinkNode<T> * top;
};

template<class T>
inline ostream& operator<<(ostream& os, LinkedStack<T>& S) {
	os << "ջ��Ԫ�ظ���" << S.getSize() << endl;
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
		cerr << "��ջ�޷���ջ";
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
	cout << "��ջ��" << v << endl;
	s.Push(100);
	s.output();
	for (int i = 60; i < 70; i++) {
		s.Push(i);
	}
	s.output();
}

bool pairCheck(string & str) {
	// ������չ�Բ��Ǻܺã����ԸĽ��ģ�����
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
									   * ջ��ʼ��ֻ�зֽ��δִ�У�����ֽ⣩������
									   * �Ѿ��ֽ�����񲻻���ջ�б���
									   */
	s.Push(n);								// �õ����񣨽�ջ��
	do {
		int temp = s.Pop();                 // �ó�����׼��ִ�л�ֽ�
		if (temp == 0 || temp == 1) {       // �޷��ֽ⣬ִ�м���
			sum += 1;
		}
		else {                              // ���Էֽ⣬�ֽ�����ѹջ
			s.Push(temp - 1);               /* �ֽ�������������ֻ�ɸ�����(temp)�ṩ */
			s.Push(temp - 2);
		}
	} while (!s.IsEmpty());               
	return sum;
}

void Hanoi(size_t n) {
	/*
	 * ��ջʵ�ֵݹ���Ҫ���ǵݹ�ʵ�ֵĽṹ����״��
	 * �������ݹ����֮�������������������ջ��ʵ�֣������������⣩
		* ��������ݾ߱������־�������������������ݣ��������������취push��ջ�����ýṹ�壩��д�����ݹ����֮�䣬
		* Ȼ�����ж�����ʱ����������������־�����������
		* �������������־����1����͵ݹ�ֹͣ��־һ�����������ʽ��ͬ���ʿɹ��á�
		* ���ڴ��������Ƿ��и��õĽ��������
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
			s.Push(midtask);  // �м����
			s.Push(subtask1);
		}

	} while (!s.IsEmpty());
	cout << "�ܹ��ƶ�" << step << "��" << endl;
}

void AkmQ(int m, int n) {
	/* ˫�ݹ麯���ķǵݹ�ʵ�֣�����һ��ݹ��ֵ��Ҫ����ݹ�ֵ����˷ֽ�����ʱ�Ͳ��ܰ���Ҫ����ݹ�ֵ������ȡ������ */
	/* 
	 * ��ʼ�汾�����Ż����֣�
		* ��ȡջ��ʱʹ��Pop����Ϊ����������δ�õ�ֵ��Akm
		* �������ó������pop��ջ��ֻ�ᱣ��δ��ȫ��ֵ��Akm
		
	 */

	struct Akm {
		int m;
		int n;
		bool deeper;  // true������Ҫ����ݹ�ֵ������ջ��ͣ������false������Ҫ����������ջ��
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
			while (!t.deeper && !s.IsEmpty()) {  // Ѱ��deeperΪtrue����
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

	/* ���հ� */
	/* �ǵݹ���ռ��� */

	struct Akm {
		int m;
		int n;  // -1������Ҫ����ݹ�ֵ������ջ��ͣ������������Ҫ����������ջ��
	};
	LinkedStack<Akm> s;
	Akm initial{ m, n};
	int result = 0;

	s.Push(initial);
	do {
		Akm temp = s.Pop();
		if (temp.m == 0) {
			result = temp.n + 1;
			if (!s.IsEmpty()) {  // ջδ��˵��������δ��ɣ�����Ҫ��ǰ������εݹ�
				Akm t = s.Pop();
				t = {t.m, result};  // �ڴ�����˶���ݹ��һ��ݹ�Ĵ�ֵ��������Ͷ����ϴ�ֵ
				s.Push(t);
			}
		}
		else if (temp.m != 0 && temp.n == 0) {
			Akm subtask1{ temp.m - 1, 1};
			s.Push(subtask1);
		}
		else if (temp.m != 0 && temp.n != 0) {
			Akm subtask2{ temp.m - 1, -1};  // �ڶ��������������裬������ջ֮ǰ�ᱻ�����
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

/* β�ݹ��̽����
 * β�ݹ���ζ����ȥ�޻أ��ͼ���������ԣ��������ս����ȥ��ʱ��õ��ˣ�����ʱֻ���ڰ����ս������(��쳲���������)
 * ����ջʵ����ζ�ŷֽ�����ʱ����Ҫ���Ѿ��ֽ�����񱣴���ջ�У�ջ�б�����ֻ�е�ǰ���ڽ��е�����
 * ���Ǻõ����ԣ����Ա��ⱬջ
 * ���з�β�ݹ������������׳ˣ�����ʱÿһ����Ҫ������ջ�еȴ��ص�����Ȼ���ǿ����Ż�Ϊβ�ݹ�ģ�
 * β�ݹ�ͷ�β�ݹ�ͬʱ�У���Akm���⣩���⵼��һ���ּ���Ҫ������ջ�еȴ��ص�������Խ��Խ�ã���
 */

size_t permutation(string str, size_t k = 0) {
	// ȫ���еݹ�ʵ��
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

// ��ϵݹ�ʵ�֣����������е��鷳