#include <iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main() {
	string line;//每次读入一整行，直到文件末尾
	while (getline(cin, line))
		if (!line.empty())			//逻辑非运算符!意思为不等于,即为line不为空的时候(有内容)
			cout << line << endl;
	return 0;
}