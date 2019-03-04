#pragma once
const int defaultSize = 100;

template<class T>
class SeqList
{
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);//���ƹ��캯��
	~SeqList() { delete[] data; }
	int Size()const { return maxSize; }
	int Length()const { return length; }
	int Search(T& x)const;//����x�ڱ���λ�ã����ر������
	int Locate(int i)const;//��λ��i��������ر������
	bool getData(int i, T& x)const//ȡ��i������ֵ
	{
		if (i > 0 && i <= length) {
			x = data[i - 1];
			return true;
		}
		else return false;
	}
	bool setData(int i, T& x)//��x�޸ĵ�i��λ��ֵ
	{
		if (i >= 1 && i < length) {
			data[i - 1] = x;
			return true;
		}
		else return false;
	}
	bool Insert(int i, T& x);//����x�ڵ�i�������
	bool Remove(int i, T& x);//ɾ����i���������ɾ����ֵ
	bool IsFull()const { return length == maxSize ? true : false; }//����
	bool IsEmpty()const { return length == 0 ? true : false; }//�п�
	void Sort() { return; }//����
	void input();//����
	void output();//���
	SeqList<T>& operator=(SeqList<T>& L);
	T delMin();
protected:
	T * data;//�������
	int maxSize;//�������ɱ��������	
	int length;//����
	void reSize(int newSize);//�ı�data����ռ��С
};
