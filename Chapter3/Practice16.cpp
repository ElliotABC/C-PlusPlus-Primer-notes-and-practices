#include <iostream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;
//3.2.3
//3.6
/*
int main() {
	string example = "ABCDEFG";
	string n;
	for (char c : example) {
		n += 'X';
	}
	cout << "Original string:" << example << endl;
	cout << "New string:" << n << endl;
}
*/

//3.7
/*
int main() {
	string example = "ABCDEFG";
	string n;
	for (char c : example) {
		n += 'X';
	}
	cout << "Original string:" << example << endl;
	cout << "New string:" << n << endl;
}
*/

//3.8
/*
int main() {
	string example = "ABCDEFG";
	string::size_type i = 0;
	string replaced;
	while (i<example.size()){
		replaced += 'X';
			++i;
	}
	cout << "Original string:" << example << endl;
	cout << "New string:" << replaced << endl;
	return 0;
}
*/

//3.9
//���Ϸ�������ʹ���±�����ַ���
/*
int main() {
	string s;
	cout << s[0] << endl;
}
*/

//3.10
/*
int main() {
	string example = "Hello,World!%";
	string::size_type i = 0;
	string replaced;

	while (i < example.size()) {
		char c = example[i];
		if (!ispunct(c)) {
			replaced += c;
		}
		++i;
	}
	std::cout << "ȥ�������ŵ��ַ���" << replaced << endl;
	return 0;
}
*/

//3.11
//c��string�������ַ������ã�s�ǳ��������������丳ֵ��cҲ���ǳ���s����Ƿ����෴��������ı�ͺϷ�/����Ϸ���c����Ϊstring
int main() {
	const string s = "Keep out!";
	for (auto& c : s) {
		//
		//
	}
}