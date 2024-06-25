#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	string s("Hello World!!!&");
	decltype(s.size()) punct_cnt = 0;//punct_cnt的类型和s.size返回类型相同
	//统计s中标点符号数量
	for (auto c : s)
		if (ispunct(c))
			++punct_cnt;
	cout << punct_cnt << " punctuation characters in " << s << endl;
}