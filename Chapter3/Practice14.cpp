#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	string s("Hello World!!!");
	//转换成大写形式
	for (auto& c : s)		//对于s中每一个字符
		c = toupper(c);
	cout << s << endl;
}