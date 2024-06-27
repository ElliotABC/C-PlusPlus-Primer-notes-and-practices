#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
//			012345678910
/*
string s = "Hello World";
int main() {
	if (!s.empty())
		cout << s[0] << endl;
}
*/

/*
string s("some string");
int main() {
	if (!s.empty())
		s[0] = toupper(s[0]);
	cout << s << endl;
}
*/

/*
string s("some string");
int main() {
	for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index)//�߼��������&&����������������������Ϊ�棬���߼�����Ϊ�棺TRUE TRUE ---->TRUE	TRUE FALSE ---->FALSE	FALSE FLASE ---->FALSE
		s[index] = toupper(s[index]);			//ֻ�дﵽ����s.size()��Ż�ִ���Ҳ�s[index]
	cout << s << endl;
}
*/

int main() {
	const string hexdigits = "0123456789ABCDEF";
	cout << "Enter a series of numbers between 0 and 15"
		<< " separated by spaces. Hit ENTER when finished: "
		<< endl;
	string result;
	string::size_type n;
	while (cin >> n)
		if (n < hexdigits.size())
			result += hexdigits[n];
	cout << "Your hex number is:" << result << endl;
}  