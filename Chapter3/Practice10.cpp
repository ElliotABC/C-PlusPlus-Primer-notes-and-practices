#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	string s1, s2, s3, s4;
	string total;
	if (cin >> s1 >> s2 >> s3 >> s4)
		s1 = s1 + " ";
		s2 = s2 + " ";
		s3 = s3 + " ";
		s4 = s4 + " ";
		total = s1 + s2 + s3 + s4;
	cout << total;
}