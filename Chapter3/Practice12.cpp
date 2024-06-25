#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
//对于字符串str中的每个字符c，执行输出一个字符并换行的操作
int main() {
	string str("some string");
	//每行输出str中的一个字符
	for (auto c : str)		//c:char
		cout << c << endl;
}