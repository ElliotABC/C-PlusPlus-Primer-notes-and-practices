#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	string s("Hello World!!!&");
	decltype(s.size()) punct_cnt = 0;//punct_cnt�����ͺ�s.size����������ͬ
	//ͳ��s�б���������
	for (auto c : s)
		if (ispunct(c))
			++punct_cnt;
	cout << punct_cnt << " punctuation characters in " << s << endl;
}