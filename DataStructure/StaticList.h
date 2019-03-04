#pragma once
using namespace std;

const int maxSize = 100;

template<class T>
struct SLinkNode{
	T data;
	int link;  //�α�ʵ�ַ�
};

template<class T>
class StaticList
{
	SLinkNode<T> elem[maxSize];
	int avil;  //��ǰ�ɷ���ռ��׵�ַ
public:
	StaticList();
	~StaticList();
	int Length();
	int Search();
	int Locate(int i);
	bool Append(T x);
	bool Insert(int i, T x);
	bool Remove(int i);
	bool IsEmpty();
	void input();
	void output();
};


template<class T>
StaticList<T>::StaticList()
{
	elem[0].link = -1;
	avil = 1;
	for (int i = 1; i < maxSize - 1; i++) {
		elem[i].link = i + 1;
	}
	elem[maxSize - 1].link = -1;
}

template<class T>
StaticList<T>::~StaticList()
{
}

template<class T>
inline int StaticList<T>::Length()
{
	int p = elem[0].link;
	int i = 0;
	while (p != -1) {
		p = elem[p].link;
		i++;
	}
	return i;
}

template<class T>
inline int StaticList<T>::Locate(int i)
{
	if (i < 0) return -1;
	if (i == 0) return 0;
	int j = 1, p = elem[0].link;
	while (p != -1 && j < i) {
		p = elem[j].link;
		j++;
	}

	return p;
}

template<class T>
inline bool StaticList<T>::Append(T x)
{
	if (avil == -1) return false;
	int p = 0;
	while (elem[p].link != -1) {
		p = elem[p].link;	//�Ȳ��ұ�β
	}
	elem[p].link = avil;

	int q = avil;
	avil = elem[avil].link;
	elem[q].data = x;
	elem[q].link = -1;
	
	
	return true;
}

template<class T>
inline bool StaticList<T>::Insert(int i, T x)
{
	int p = Locate(i);
	if (p == -1) return false;
	int q = avil;
	avil = elem[avil].link;
	elem[q].data = x;
	elem[q].link = elem[p].link;
	elem[p].link = q;
	return true;
}

template<class T>
inline bool StaticList<T>::Remove(int i)
{
	int p = Locate(i - 1);
	if (p == -1) return false;
	int q = elem[p].link;
	elem[p].link = elem[q].link;
	elem[q].link = avil;
	avil = q;
	return true;
}

template<class T>
inline bool StaticList<T>::IsEmpty()
{
	if (elem[0].link == -1) return true;
	else return false;
}

template<class T>
inline void StaticList<T>::input()
{
	int length = 0;
	cout << "��ʼ������̬�����������Ԫ�ظ�����";
	while (1) {
		cin >> length;
		if (length <= maxSize-1)break;
		cout << "����Ԫ�ظ������󣬷�Χ���ܳ���" << maxSize - 1 << ":";
	}
	for (int i = 0; i < length; i++) {
		T x;
		cin >> x;
		Append(x);
	}
}

template<class T>
inline void StaticList<T>::output()
{
	int i = 0;
	int p = elem[0].link;
	while(p != -1){
		cout << "#" << ++i << ":" << elem[p].data << endl;
		p = elem[p].link;
	}
}

void StaticListTest() {
	StaticList<int> test;
	for (int i = 0; i < 10; i++) {
		test.Append(i + 1);
	}
	test.output();
	test.Remove(5);
	test.output();
	test.Insert(2, 20);
	test.output();
}
