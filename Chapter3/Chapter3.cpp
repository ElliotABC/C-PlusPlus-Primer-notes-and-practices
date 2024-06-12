// Chapter3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
	cout << "Enter two numbers:" << endl;
	int v1, v2;
	cin >> v1 >> v2;
	cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << endl;
	return 0;
}