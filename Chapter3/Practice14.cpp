#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	string s("Hello World!!!");
	//ת���ɴ�д��ʽ
	for (auto& c : s)		//����s��ÿһ���ַ�
		c = toupper(c);
	cout << s << endl;
}