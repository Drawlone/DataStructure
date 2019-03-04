#pragma once
const int defaultSize = 100;

template<class T>
class SeqList
{
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);//复制构造函数
	~SeqList() { delete[] data; }
	int Size()const { return maxSize; }
	int Length()const { return length; }
	int Search(T& x)const;//搜索x在表中位置，返回表项序号
	int Locate(int i)const;//定位第i个表项，返回表项序号
	bool getData(int i, T& x)const//取第i个表项值
	{
		if (i > 0 && i <= length) {
			x = data[i - 1];
			return true;
		}
		else return false;
	}
	bool setData(int i, T& x)//用x修改第i个位置值
	{
		if (i >= 1 && i < length) {
			data[i - 1] = x;
			return true;
		}
		else return false;
	}
	bool Insert(int i, T& x);//插入x在第i个表项后
	bool Remove(int i, T& x);//删除第i个表项，返回删除的值
	bool IsFull()const { return length == maxSize ? true : false; }//判满
	bool IsEmpty()const { return length == 0 ? true : false; }//判空
	void Sort() { return; }//排序
	void input();//输入
	void output();//输出
	SeqList<T>& operator=(SeqList<T>& L);
	T delMin();
protected:
	T * data;//存放数组
	int maxSize;//最大可容纳表项的项数	
	int length;//表长度
	void reSize(int newSize);//改变data数组空间大小
};
