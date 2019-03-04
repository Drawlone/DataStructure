// LinearList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include"LinkedQueue.h"
#include"LinkStack.h"
using namespace std;

int main()
{
	string s;
	while (cin >> s) {
		if (pairCheck(s)) {
			cout << "Correct!"<<endl;
		}
		else {
			cout << "Wrong!"<<endl;
		}
	}
	getchar();
}


