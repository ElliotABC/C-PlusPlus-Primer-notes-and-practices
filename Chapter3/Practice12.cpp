#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
//�����ַ���str�е�ÿ���ַ�c��ִ�����һ���ַ������еĲ���
int main() {
	string str("some string");
	//ÿ�����str�е�һ���ַ�
	for (auto c : str)		//c:char
		cout << c << endl;
}