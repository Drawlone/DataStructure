#include "pch.h"
#include "SeqList.h"
using namespace std;

template<class T>
SeqList<T>::SeqList(int sz)
{
	if (sz > 0) {
		maxSize = sz;
		length = 0;
		data = new T[maxSize];
		if (data == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}
	}
}

template<class T>
SeqList<T>::SeqList(SeqList<T>& L)
{
	T value;
	maxSize = L.Size();
	length = L.Length();
	data = new T[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
		for (int i = 0; i < length - 1; i++) {
			L.getData(i + 1, value);
			data[i] = value;
		}
	}
}

template<class T>
void SeqList<T>::reSize(int newSize) {
	if (newSize <= 0) {
		cerr << "��Ч�������С" << endl;
		return;
	}
	if (newSize != maxSize) {
		T * newarray = new T[newSize];
		if (newarray == NULL) {
			cerr << "�ڴ�������" << endl;
			exit(1);
		}
		T * srcptr = data;
		T * desptr = newarray;
		while (length--)
			*desptr++ = *srcptr++;
		delete[]data;
		data = newarray;
		maxSize = newSize;
	}

}

template<class T>
int SeqList<T>::Search(T& x)const {
	for (int i = 0; i < length; i++) {
		if (data[i] == x)
			return i + 1;
	}
	return 0;
}

template<class T>
int SeqList<T>::Locate(int i)const {
	if (i > 0 && i <= length)return i;
	return 0;
}

template<class T>
bool SeqList<T>::Insert(int i, T& x) {
	if (length == maxSize)return false;
	if (i<0 || i>length)return false;
	for (int j = length; j > i; j--) {
		data[j] = data[j - 1];
	}
	data[i] = x;
	length++;
	return true;
}

template<class T>
bool SeqList<T>::Remove(int i, T& x) {
	if (length == 0)return false;
	if (i <= 0 || i > length)return false;
	x = data[i - 1];
	for (int j = i - 1; j < length; j++) {
		data[j] = data[j + 1];
	}
	length--;
	return true;
}

template<class T>
void SeqList<T>::input() {
	cout << "��ʼ����˳������������Ԫ�ظ�����";
	while (1) {
		cin >> length;
		if (length <= maxSize)break;
		cout << "����Ԫ�ظ������󣬷�Χ���ܳ���" << length << ":";
	}
	for (int i = 0; i < length; i++) {
		cin >> data[i];
	}
}

template<class T>
void SeqList<T>::output() {
	cout << "˳���ǰ���λ��Ϊ:" << length << endl;
	for (int i = 0; i < length; i++) {
		cout << "#" << i + 1 << ":" << data[i] << endl;
	}
}

template<class T>
SeqList<T>& SeqList<T>::operator=(SeqList<T>& L) {
	T value;
	maxSize = L.Size();
	length = L.Length();
	data = new T[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
		for (int i = 0; i < length - 1; i++) {
			L.getData(i + 1, value);
			data[i] = value;
		}
	}
}

template<class T>
T SeqList<T>::delMin()
{
	int min = INT_MAX, j;
	T x;
	for (int i = 0; i < length; i++) {
		if (data[i] < min) {
			min = data[i];
			j = i;
		}
	}
	Remove(j + 1, x);
	return x;
}


