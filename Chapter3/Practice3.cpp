#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
using std::endl;
//读取未知数量的string对象
int main() {
	string word;
	while (cin >> word)
		cout << word << endl;
	return 0;
}