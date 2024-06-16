#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
//3.2.2
//3.2
/*
int main() {
	string readline;
	while (getline(cin, readline))
		cout << readline<<endl;

}
*/

int main() {
	string readline;
	while (cin >> readline) {
		cout << readline << endl;
	}
}

//3.3
/*
string把空格前后分开，一次只读一个字符但是会全部读完，不读入空格
getline直接读取一整行，包含空格，直到遇到换行符结束
*/