#include <iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main() {
	string line;//ÿ�ζ���һ���У�ֱ���ļ�ĩβ
	while (getline(cin, line))
		cout << line << endl;
	return 0;
}