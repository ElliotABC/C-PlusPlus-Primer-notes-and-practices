#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	const string hexdigits = "0123456789ABCDEF";
	cout << "Enter a series of numbers between 0 and 15"
		<< " separated by spaces. Hit ENTER when finished:"
		<< endl;
	string result;			//保存十六进制字符串
	string::size_type n;	//保存输入流读取的数
	while (cin>>n)
		if (n<hexdigits.size())
			result += hexdigits[n];
	cout << "Your hex number is:" << result << endl;
}